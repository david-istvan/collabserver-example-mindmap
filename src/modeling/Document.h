#pragma once

#include <collabserver/datatypes/CmRDT/LWWMap.h>
#include <collabserver/datatypes/collabdata/CollabData.h>

#include "Node.h"
#include "UUID.h"
#include "collaboration/Timestamp.h"

class Document : public collabserver::CollabData {
   public:
    Document(unsigned int _localUserID) : m_localUserID(_localUserID){};
    ~Document();

    Node* getNode(UUID _nodeUUID);
    Node* createNode();
    void deleteNode(UUID _nodeUUID);

    unsigned int getLocalUserID() const { return m_localUserID; }

    bool applyExternOperation(unsigned int _id, const std::string& _buffer) override;

    enum Operations : unsigned int {
        // Each operation must be uniquely defined (node + documents)
        DOC_CREATE_NODE_OPERATION = Node::Operations::_OPERATION_COUNTER,
        DOC_DELETE_NODE_OPERATION
    };

    class DocumentCreateNodeOperation;
    class DocumentDeleteNodeOperation;

   private:
    void applyOperation(const DocumentCreateNodeOperation& _op);
    void applyOperation(const DocumentDeleteNodeOperation& _op);

    unsigned int m_localUserID = 0;  // ID of the local user (set by the server)
    collabserver::LWWMap<UUID, Node*, Timestamp> m_nodes;
    std::mutex m_operationMutex;  // To allow one operation on all threads
};

// -----------------------------------------------------------------------------

class Document::DocumentCreateNodeOperation : public collabserver::CollabDataOperation {
   public:
    DocumentCreateNodeOperation() = default;
    DocumentCreateNodeOperation(UUID _nodeUUID, const Timestamp& _timestamp);
    bool serialize(std::stringstream& _buffer) const override;
    bool unserialize(const std::stringstream& _buffer) override;
    void accept(collabserver::CollabDataOperationHandler& _handler) const override;
    unsigned int getType() const override { return DOC_CREATE_NODE_OPERATION; }

    UUID m_nodeUUID;
    Timestamp m_timestamp = {0};
};

class Document::DocumentDeleteNodeOperation : public collabserver::CollabDataOperation {
   public:
    DocumentDeleteNodeOperation() = default;
    DocumentDeleteNodeOperation(UUID _nodeUUID, const Timestamp& _timestamp);
    bool serialize(std::stringstream& _buffer) const override;
    bool unserialize(const std::stringstream& _buffer) override;
    void accept(collabserver::CollabDataOperationHandler& _handler) const override;
    unsigned int getType() const override { return DOC_DELETE_NODE_OPERATION; }

    UUID m_nodeUUID;
    Timestamp m_timestamp = {0};
};