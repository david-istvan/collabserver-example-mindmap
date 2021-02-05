#include "Node.h"

#include "Document.h"

std::string Node::getAttribute(const std::string& _key) const {
    auto it = m_data.find(_key);
    if (it != m_data.end()) {
        return it->second.query();
    }
    return {};
}

void Node::setAttribute(const std::string& _key, const std::string& _value) {
    Timestamp::setEffectiveID(m_document.getLocalUserID());
    NodeSetAttributeOperation op{m_nodeID, _key, _value, Timestamp::now()};
    this->applyOperation(op);
    m_document.notifyOperationBroadcaster(op);
}

void Node::removeAttribute(const std::string _key) {
    Timestamp::setEffectiveID(m_document.getLocalUserID());
    NodeRemoveAttributeOperation op{m_nodeID, _key, Timestamp::now()};
    this->applyOperation(op);
    m_document.notifyOperationBroadcaster(op);
}

void Node::applyOperation(NodeSetAttributeOperation _op) {
    std::lock_guard<std::mutex> lock(m_operationMutex);
    // TODO not implemented
    // m_data.add(_op.m_key, _op.m_timestamp);
}

void Node::applyOperation(NodeRemoveAttributeOperation _op) {
    std::lock_guard<std::mutex> lock(m_operationMutex);
    // TODO not implemented
}

// -----------------------------------------------------------------------------

Node::NodeSetAttributeOperation::NodeSetAttributeOperation(unsigned int _id, const std::string& _key,
                                                           const std::string& _value, const Timestamp& _time)
    : m_nodeID(_id), m_key(_key), m_value(_value), m_timestamp(_time) {}

bool Node::NodeSetAttributeOperation::serialize(std::stringstream& _buffer) const {
    // TODO not implemented
    return true;
}

bool Node::NodeSetAttributeOperation::unserialize(const std::stringstream& _buffer) {
    // TODO not implemented
    return true;
}

void Node::NodeSetAttributeOperation::accept(collabserver::CollabDataOperationHandler& _handler) const {
    // TODO (for now, nothing to do)
}

// -----------------------------------------------------------------------------

Node::NodeRemoveAttributeOperation::NodeRemoveAttributeOperation(unsigned int _id, const std::string& _key,
                                                                 const Timestamp& _time)
    : m_nodeID(_id), m_key(_key), m_timestamp(_time) {}

bool Node::NodeRemoveAttributeOperation::serialize(std::stringstream& _buffer) const {
    // TODO not implemented
    return true;
}

bool Node::NodeRemoveAttributeOperation::unserialize(const std::stringstream& _buffer) {
    // TODO not implemented
    return true;
}

void Node::NodeRemoveAttributeOperation::accept(collabserver::CollabDataOperationHandler& _handler) const {
    // TODO (for now, nothing to do)
}
