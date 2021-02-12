#include "Document.h"

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

bool Document::applyExternOperation(unsigned int _id, const std::string& _buffer) {
    // TODO not implemented
    return false;
}

// -----------------------------------------------------------------------------

Document::DocumentCreateNodeOperation::DocumentCreateNodeOperation(UUID _nodeUUID, const Timestamp& _timestamp)
    : m_nodeUUID(_nodeUUID), m_timestamp(_timestamp) {}

bool Document::DocumentCreateNodeOperation::serialize(std::stringstream& _buffer) const {
    // TODO
    return false;
}

bool Document::DocumentCreateNodeOperation::unserialize(const std::stringstream& _buffer) {
    // TODO
    return false;
}

void Document::DocumentCreateNodeOperation::accept(collabserver::CollabDataOperationHandler& _handler) const {
    // TODO (for now, nothing to do. Use getAttribute to see changes)
}

// -----------------------------------------------------------------------------

Document::DocumentDeleteNodeOperation::DocumentDeleteNodeOperation(UUID _nodeUUID, const Timestamp& _timestamp)
    : m_nodeUUID(_nodeUUID), m_timestamp(_timestamp) {}

bool Document::DocumentDeleteNodeOperation::serialize(std::stringstream& _buffer) const {
    // TODO not implemented;
    return false;
}

bool Document::DocumentDeleteNodeOperation::unserialize(const std::stringstream& _buffer) {
    // TODO not implemented;
    return false;
}

void Document::DocumentDeleteNodeOperation::accept(collabserver::CollabDataOperationHandler& _handler) const {
    // TODO (for now, nothing to do. Use getAttribute to see changes)
}