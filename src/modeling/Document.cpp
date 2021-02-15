#include "Document.h"

#include <msgpack.hpp>

Document::~Document() {
    // TODO Free memory (or use std::unique_ptr instead)
}

Node* Document::getNode(UUID _nodeUUID) {
    auto it = m_nodes.find(_nodeUUID);
    if (it != m_nodes.end()) {
        return it->second;
    }
    return nullptr;
}

Node* Document::createNode() {
    Timestamp::setEffectiveID(m_localUserID);
    DocumentCreateNodeOperation op{generateNewUUID(), Timestamp::now()};
    this->applyOperation(op);
    this->notifyOperationBroadcaster(op);
    return getNode(op.m_nodeUUID);
}

void Document::deleteNode(UUID _nodeUUID) {
    Timestamp::setEffectiveID(m_localUserID);
    DocumentDeleteNodeOperation op{_nodeUUID, Timestamp::now()};
    this->applyOperation(op);
    this->notifyOperationBroadcaster(op);
}

void Document::applyOperation(const DocumentCreateNodeOperation& _op) {
    std::lock_guard<std::mutex> lock(m_operationMutex);
    bool isAdded = m_nodes.add(_op.m_nodeUUID, _op.m_timestamp);
    if (isAdded) {
        // DevNote: Node have one lifetime (cuz UUID are unique) so we don't need to delete the previous content
        // because, in practice, isAdded will append once
        m_nodes.at(_op.m_nodeUUID) = new Node(*this, _op.m_nodeUUID);
        this->notifyOperationObservers(_op);
    }
}

void Document::applyOperation(const DocumentDeleteNodeOperation& _op) {
    std::lock_guard<std::mutex> lock(m_operationMutex);
    bool isRemoved = m_nodes.remove(_op.m_nodeUUID, _op.m_timestamp);
    if (isRemoved) {
        this->notifyOperationObservers(_op);
    }
}

void Document::applyOperation(const Node::NodeSetAttributeOperation& _op) {
    std::lock_guard<std::mutex> lock(m_operationMutex);

    // Also add the node of this attribute
    // TODO this is like calling applyOperation(DocumentCreateNodeOperation) but mutex do a would race-condition
    bool isAdded = m_nodes.add(_op.m_nodeUUID, _op.m_timestamp);
    if (isAdded) {
        m_nodes.at(_op.m_nodeUUID) = new Node(*this, _op.m_nodeUUID);
        this->notifyOperationObservers(_op);
    }

    Node* node = m_nodes.crdt_at(_op.m_nodeUUID);
    if (node) {
        // We just added, but Node could be removed more recently
        bool isNodeAlive = (m_nodes.count(_op.m_nodeUUID) > 0) ? true : false;

        // TODO Bug if the node is removed, but operation applied, the application will be notified (but should not)
        node->applyOperation(_op);
    }
}

void Document::applyOperation(const Node::NodeRemoveAttributeOperation& _op) {
    std::lock_guard<std::mutex> lock(m_operationMutex);

    // Also add the node of this attribute
    // TODO this is like calling applyOperation(DocumentCreateNodeOperation) but mutex do a would race-condition
    bool isAdded = m_nodes.add(_op.m_nodeUUID, _op.m_timestamp);
    if (isAdded) {
        m_nodes.at(_op.m_nodeUUID) = new Node(*this, _op.m_nodeUUID);
        this->notifyOperationObservers(_op);
    }

    Node* node = m_nodes.crdt_at(_op.m_nodeUUID);
    if (node) {
        // We just added, but Node could be removed more recently
        bool isNodeAlive = (m_nodes.count(_op.m_nodeUUID) > 0) ? true : false;

        // TODO Bug if the node is removed, but operation applied, the application will be notified (but should not)
        node->applyOperation(_op);
    }
}

bool Document::applyExternOperation(unsigned int _id, const std::string& _buffer) {
    std::stringstream opBuffer(_buffer);  // TODO Remove useless copy

    switch (_id) {
        case DOC_CREATE_NODE_OPERATION: {
            DocumentCreateNodeOperation op{};
            if (!op.unserialize(opBuffer)) {
                return false;
            }
            Timestamp::setEffectiveID(op.m_timestamp.getID());
            applyOperation(op);
        } break;
        case DOC_DELETE_NODE_OPERATION: {
            DocumentDeleteNodeOperation op{};
            if (!op.unserialize(opBuffer)) {
                return false;
            }
            Timestamp::setEffectiveID(op.m_timestamp.getID());
            applyOperation(op);
        } break;
        case Node::Operations::NODE_SET_ATTRIBUTE_OPERATION: {
            Node::NodeSetAttributeOperation op{};
            if (!op.unserialize(opBuffer)) {
                return false;
            }
            // Get attribute for ID
            Timestamp::setEffectiveID(op.m_timestamp.getID());
            applyOperation(op);
        } break;

        case Node::Operations::NODE_REMOVE_ATTRIBUTE_OPERATION: {
            Node::NodeRemoveAttributeOperation op{};
            if (!op.unserialize(opBuffer)) {
                return false;
            }
            Timestamp::setEffectiveID(op.m_timestamp.getID());
            applyOperation(op);
        } break;
    }

    return false;
}

// -----------------------------------------------------------------------------

Document::DocumentCreateNodeOperation::DocumentCreateNodeOperation(UUID _nodeUUID, const Timestamp& _timestamp)
    : m_nodeUUID(_nodeUUID), m_timestamp(_timestamp) {}

bool Document::DocumentCreateNodeOperation::serialize(std::stringstream& _buffer) const {
    msgpack::pack(_buffer, m_nodeUUID);
    m_timestamp.serialize(_buffer);
    return true;
}

bool Document::DocumentCreateNodeOperation::unserialize(const std::stringstream& _buffer) {
    std::string str(_buffer.str());
    std::size_t offset = 0;

    msgpack::object_handle r1 = msgpack::unpack(str.data(), str.size(), offset);
    m_nodeUUID = r1.get().as<UUID>();

    // TODO This is ugly (to update with actual bit reading instead of string)
    std::stringstream bufferTimestamps(str.substr(offset));
    m_timestamp.unserialize(bufferTimestamps);

    return true;
}

void Document::DocumentCreateNodeOperation::accept(collabserver::CollabDataOperationHandler& _handler) const {
    // TODO (for now, nothing to do. Use getAttribute to see changes)
}

// -----------------------------------------------------------------------------

Document::DocumentDeleteNodeOperation::DocumentDeleteNodeOperation(UUID _nodeUUID, const Timestamp& _timestamp)
    : m_nodeUUID(_nodeUUID), m_timestamp(_timestamp) {}

bool Document::DocumentDeleteNodeOperation::serialize(std::stringstream& _buffer) const {
    msgpack::pack(_buffer, m_nodeUUID);
    m_timestamp.serialize(_buffer);
    return true;
}

bool Document::DocumentDeleteNodeOperation::unserialize(const std::stringstream& _buffer) {
    std::string str(_buffer.str());
    std::size_t offset = 0;

    msgpack::object_handle r1 = msgpack::unpack(str.data(), str.size(), offset);
    m_nodeUUID = r1.get().as<UUID>();

    // TODO This is ugly (to update with actual bit reading instead of string)
    std::stringstream bufferTimestamps(str.substr(offset));
    m_timestamp.unserialize(bufferTimestamps);

    return true;
}

void Document::DocumentDeleteNodeOperation::accept(collabserver::CollabDataOperationHandler& _handler) const {
    // TODO (for now, nothing to do. Use getAttribute to see changes)
}