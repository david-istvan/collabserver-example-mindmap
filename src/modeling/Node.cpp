#include "Node.h"

#include <msgpack.hpp>

#include "Document.h"

std::string Node::getAttribute(const std::string& _key) const {
    auto it = m_data.find(_key);
    if (it != m_data.end()) {
        return it->second.query();
    }
    return {};  // Create an empty string (copied on return)
}

void Node::setAttribute(const std::string& _key, const std::string& _value) {
    Timestamp::setEffectiveID(m_document.getLocalUserID());
    NodeSetAttributeOperation op{m_nodeUUID, _key, _value, Timestamp::now()};
    this->applyOperation(op);
    m_document.notifyOperationBroadcaster(op);
}

void Node::removeAttribute(const std::string& _key) {
    Timestamp::setEffectiveID(m_document.getLocalUserID());
    NodeRemoveAttributeOperation op{m_nodeUUID, _key, Timestamp::now()};
    this->applyOperation(op);
    m_document.notifyOperationBroadcaster(op);
}

void Node::applyOperation(const NodeSetAttributeOperation& _op) {
    assert(_op.m_nodeUUID == m_nodeUUID);
    std::lock_guard<std::mutex> lock(m_operationMutex);

    // Att doesn't exists -> created + set
    // Att exists (older) -> set
    // Att exists (newer) -> nothing

    m_data.add(_op.m_key, _op.m_timestamp);

    try {
        bool isUpdated = m_data.at(_op.m_key).update(_op.m_value, _op.m_timestamp);
        bool attrExists = (m_data.count(_op.m_key) > 0) ? true : false;
        // Someone may have deleted this attribute.
        // Still the update must be applied anyway (required by CRDT)
        if (isUpdated && attrExists) {
            m_document.notifyOperationObservers(_op);
        }
    } catch (const std::exception& e) {
        // This is really unexpected, since the `at` method is done just after `add`
    }
}

void Node::applyOperation(const NodeRemoveAttributeOperation& _op) {
    assert(_op.m_nodeUUID == m_nodeUUID);
    std::lock_guard<std::mutex> lock(m_operationMutex);

    bool isRemoved = m_data.remove(_op.m_key, _op.m_timestamp);
    if (isRemoved) {
        m_document.notifyOperationObservers(_op);
    }
}

// -----------------------------------------------------------------------------

Node::NodeSetAttributeOperation::NodeSetAttributeOperation(UUID _nodeUUID, const std::string& _key,
                                                           const std::string& _value, const Timestamp& _timestamp)
    : m_nodeUUID(_nodeUUID), m_key(_key), m_value(_value), m_timestamp(_timestamp) {}

bool Node::NodeSetAttributeOperation::serialize(std::stringstream& _buffer) const {
    msgpack::pack(_buffer, m_nodeUUID);
    msgpack::pack(_buffer, m_key);
    msgpack::pack(_buffer, m_value);
    m_timestamp.serialize(_buffer);
    return true;
}

bool Node::NodeSetAttributeOperation::unserialize(const std::stringstream& _buffer) {
    std::string str(_buffer.str());
    std::size_t offset = 0;

    msgpack::object_handle r1 = msgpack::unpack(str.data(), str.size(), offset);
    msgpack::object_handle r2 = msgpack::unpack(str.data(), str.size(), offset);
    msgpack::object_handle r3 = msgpack::unpack(str.data(), str.size(), offset);

    r1.get().convert(m_nodeUUID);
    r2.get().convert(m_key);
    r3.get().convert(m_value);

    // TODO This is ugly (to update with actual bit reading instead of string)
    std::stringstream bufferTimestamps(str.substr(offset));
    m_timestamp.unserialize(bufferTimestamps);
    return true;
}

void Node::NodeSetAttributeOperation::accept(collabserver::CollabDataOperationHandler& _handler) const {
    // TODO (for now, nothing to do. Use getAttribute to see changes)
}

// -----------------------------------------------------------------------------

Node::NodeRemoveAttributeOperation::NodeRemoveAttributeOperation(UUID _nodeUUID, const std::string& _key,
                                                                 const Timestamp& _timestamp)
    : m_nodeUUID(_nodeUUID), m_key(_key), m_timestamp(_timestamp) {}

bool Node::NodeRemoveAttributeOperation::serialize(std::stringstream& _buffer) const {
    msgpack::pack(_buffer, m_nodeUUID);
    msgpack::pack(_buffer, m_key);
    m_timestamp.serialize(_buffer);
    return true;
}

bool Node::NodeRemoveAttributeOperation::unserialize(const std::stringstream& _buffer) {
    std::string str(_buffer.str());
    std::size_t offset = 0;

    msgpack::object_handle r1 = msgpack::unpack(str.data(), str.size(), offset);
    msgpack::object_handle r2 = msgpack::unpack(str.data(), str.size(), offset);

    r1.get().convert(m_nodeUUID);
    r2.get().convert(m_key);

    // TODO This is ugly (to update with actual bit reading instead of string)
    std::stringstream bufferTimestamps(str.substr(offset));
    m_timestamp.unserialize(bufferTimestamps);
    return true;
}

void Node::NodeRemoveAttributeOperation::accept(collabserver::CollabDataOperationHandler& _handler) const {
    // TODO (for now, nothing to do. Use getAttribute to see changes)
}
