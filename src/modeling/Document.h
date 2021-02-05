#pragma once

#include <collabserver/datatypes/CmRDT/LWWMap.h>
#include <collabserver/datatypes/collabdata/CollabData.h>

#include "Node.h"
#include "collaboration/Timestamp.h"

class Document : public collabserver::CollabData {
   public:
    Document(unsigned int _localUserID) : m_localUserID(_localUserID){};

    Node& addNode(const std::string& _key, const std::string& _value);
    void removeNode(const std::string& _key);

    bool applyExternOperation(unsigned int _id, const std::string& _buffer) override;

    unsigned int getLocalUserID() const { return m_localUserID; }

   private:
    unsigned int m_localUserID = 0;  // ID of the local user (given by the server)
    collabserver::LWWMap<std::string, std::string, Timestamp> m_nodes;
};