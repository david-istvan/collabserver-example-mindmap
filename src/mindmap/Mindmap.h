#pragma once

#include <collabserver/datatypes/CmRDT/LWWRegister.h>
#include <collabserver/datatypes/collabdata/CollabData.h>
#include <collabserver/datatypes/collabdata/CollabDataOperation.h>
#include <collabserver/datatypes/collabdata/CollabDataOperationHandler.h>

#include <memory>
#include <string>
#include <vector>

#include "mindmap/CentralTopic.h"
#include "mindmap/Marker.h"

class Mindmap : public collabserver::CollabData {
   public:
    typedef std::string UUID;

    /// ------------------------------------------------------------------------

    /// Creates a Mindmap on the stack for the given user.
    static Mindmap build(unsigned int _localID);

    /// Creates a Mindmap in the head for the given user
    static std::unique_ptr<Mindmap> buidlnew(unsigned int _localID);

    /// ------------------------------------------------------------------------

    const std::string& getName() const;
    void setName(std::string& _name);

    /// ------------------------------------------------------------------------

    // ID of all operations possible
    enum Operations : unsigned int {
        OPERATION_MINDMAP_SET_NAME,
    };

    class MindmapSetNameOperation : public collabserver::CollabDataOperation {
       public:
        unsigned int getType() const override { return OPERATION_MINDMAP_SET_NAME; }
        bool serialize(std::stringstream& buffer) const;
        bool unserialize(const std::stringstream& buffer);
        void accept(collabserver::CollabDataOperationHandler& handler) const;

        std::string m_name;
        int m_timestamp;  // TODO to update with actual timestamp
    };

    bool applyExternOperation(unsigned int id, const std::string& buffer) override;

   private:
    Mindmap(unsigned int _localID) : m_localID(_localID) {}

    void applyOperation(const MindmapSetNameOperation& op);

    /// ------------------------------------------------------------------------

    unsigned int m_localID;                              // Used for Timestamp
    collabserver::LWWRegister<std::string, int> m_name;  // TODO Change the int to actual Timestamp
};
