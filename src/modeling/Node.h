#pragma once

#include <collabserver/datatypes/CmRDT/LWWMap.h>
#include <collabserver/datatypes/CmRDT/LWWRegister.h>
#include <collabserver/datatypes/collabdata/CollabData.h>

#include <mutex>
#include <string>

#include "UUID.h"
#include "collaboration/Timestamp.h"

class Document;

// A node is a Map<Key: string, Value: string>
class Node {
   public:
    UUID getNodeUUID() const { return m_nodeUUID; }

    /// Returns a copy of the attribute value
    std::string getAttribute(const std::string& _key) const;
    void setAttribute(const std::string& _key, const std::string& _value);
    void removeAttribute(const std::string& _key);

    enum Operations : unsigned int {
        NODE_SET_ATTRIBUTE_OPERATION,
        NODE_REMOVE_ATTRIBUTE_OPERATION,
        _OPERATION_COUNTER  // Internal use (number of operations)
    };

    class NodeSetAttributeOperation;
    class NodeRemoveAttributeOperation;

   private:
    void applyOperation(const NodeSetAttributeOperation& _op);
    void applyOperation(const NodeRemoveAttributeOperation& _op);

    friend Document;
    Node(Document& _document, UUID _nodeUUID) : m_document(_document), m_nodeUUID(_nodeUUID){};

    collabserver::LWWMap<std::string, collabserver::LWWRegister<std::string, Timestamp>, Timestamp> m_data;
    Document& m_document;         // Document where the node exists
    const UUID m_nodeUUID;        // Unique UUID in the document
    std::mutex m_operationMutex;  // To allow one operation on all threads
};

// -----------------------------------------------------------------------------

class Node::NodeSetAttributeOperation : public collabserver::CollabDataOperation {
   public:
    NodeSetAttributeOperation() = default;
    NodeSetAttributeOperation(UUID _nodeUUID, const std::string& _key, const std::string& _value,
                              const Timestamp& _timestamp);
    bool serialize(std::stringstream& _buffer) const override;
    bool unserialize(const std::stringstream& _buffer) override;
    void accept(collabserver::CollabDataOperationHandler& _handler) const override;
    unsigned int getType() const override { return NODE_SET_ATTRIBUTE_OPERATION; }

    UUID m_nodeUUID;
    std::string m_key;
    std::string m_value;
    Timestamp m_timestamp = {0};
};

class Node::NodeRemoveAttributeOperation : public collabserver::CollabDataOperation {
   public:
    NodeRemoveAttributeOperation() = default;
    NodeRemoveAttributeOperation(UUID _nodeUUID, const std::string& _key, const Timestamp& _timestamp);
    bool serialize(std::stringstream& _buffer) const override;
    bool unserialize(const std::stringstream& _buffer) override;
    void accept(collabserver::CollabDataOperationHandler& _handler) const override;
    unsigned int getType() const override { return NODE_REMOVE_ATTRIBUTE_OPERATION; }

    UUID m_nodeUUID;
    std::string m_key;
    Timestamp m_timestamp = {0};
};