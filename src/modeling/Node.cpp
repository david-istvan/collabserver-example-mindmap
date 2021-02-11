#include "Node.h"

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
    NodeSetAttributeOperation op{m_nodeID, _key, _value, Timestamp::now()};
    this->applyOperation(op);
    m_document.notifyOperationBroadcaster(op);
}

void Node::removeAttribute(const std::string& _key) {
    Timestamp::setEffectiveID(m_document.getLocalUserID());
    NodeRemoveAttributeOperation op{m_nodeID, _key, Timestamp::now()};
    this->applyOperation(op);
    m_document.notifyOperationBroadcaster(op);
}

void Node::applyOperation(const NodeSetAttributeOperation& _op) {
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
    std::lock_guard<std::mutex> lock(m_operationMutex);

    bool isRemoved = m_data.remove(_op.m_key, _op.m_timestamp);
    if (isRemoved) {
        m_document.notifyOperationObservers(_op);
    }
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
