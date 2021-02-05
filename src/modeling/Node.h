#pragma once

#include <collabserver/datatypes/CmRDT/LWWMap.h>
#include <collabserver/datatypes/CmRDT/LWWRegister.h>
#include <collabserver/datatypes/collabdata/CollabData.h>

#include <mutex>
#include <string>

#include "collaboration/Timestamp.h"

class Document;

// A node is a Map<Key: string, Value: string>
class Node {
   public:
    /// Returns a copy of the attribute value
    std::string getAttribute(const std::string& _key) const;
    void setAttribute(const std::string& _key, const std::string& _value);
    void removeAttribute(const std::string _key);

    enum Operations : unsigned int { NODE_SET_ATTRIBUTE_OPERATION, NODE_REMOVE_ATTRIBUTE_OPERATION };
    class NodeSetAttributeOperation;
    class NodeRemoveAttributeOperation;

    void applyOperation(NodeSetAttributeOperation _op);
    void applyOperation(NodeRemoveAttributeOperation _op);

   private:
    friend Document;
    Node(Document& _document, unsigned int _nodeID) : m_document(_document), m_nodeID(_nodeID){};

    collabserver::LWWMap<std::string, collabserver::LWWRegister<std::string, Timestamp>, Timestamp> m_data;
    Document& m_document;         // Document where the node exists
    const unsigned int m_nodeID;  // Unique ID in the document
    std::mutex m_operationMutex;  // To allow one operation on all threads
};

class Node::NodeSetAttributeOperation : public collabserver::CollabDataOperation {
   public:
    NodeSetAttributeOperation() = default;
    NodeSetAttributeOperation(unsigned int _id, const std::string& _key, const std::string& _value,
                              const Timestamp& _time);
    bool serialize(std::stringstream& _buffer) const override;
    bool unserialize(const std::stringstream& _buffer) override;
    void accept(collabserver::CollabDataOperationHandler& _handler) const override;
    unsigned int getType() const override { return NODE_SET_ATTRIBUTE_OPERATION; }

    unsigned int m_nodeID;
    std::string m_key;
    std::string m_value;
    Timestamp m_timestamp = {0};
};

class Node::NodeRemoveAttributeOperation : public collabserver::CollabDataOperation {
   public:
    NodeRemoveAttributeOperation() = default;
    NodeRemoveAttributeOperation(unsigned int _id, const std::string& _key, const Timestamp& _time);
    bool serialize(std::stringstream& _buffer) const override;
    bool unserialize(const std::stringstream& _buffer) override;
    void accept(collabserver::CollabDataOperationHandler& _handler) const override;
    unsigned int getType() const override { return NODE_REMOVE_ATTRIBUTE_OPERATION; }

    unsigned int m_nodeID;
    std::string m_key;
    Timestamp m_timestamp = {0};
};