#pragma once

#include <collabserver/datatypes/CmRDT/LWWRegister.h>
#include <collabserver/datatypes/collabdata/CollabData.h>
#include <collabserver/datatypes/collabdata/CollabDataOperation.h>
#include <collabserver/datatypes/collabdata/CollabDataOperationHandler.h>

#include <memory>
#include <string>
#include <vector>

#include "collaboration/Timestamp.h"
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
        MindmapSetNameOperation() = default;
        MindmapSetNameOperation(const std::string& name, const Timestamp& time);
        unsigned int getType() const override { return OPERATION_MINDMAP_SET_NAME; }
        bool serialize(std::stringstream& _buffer) const;
        bool unserialize(const std::stringstream& _buffer);
        void accept(collabserver::CollabDataOperationHandler& _handler) const;

        std::string m_name;
        Timestamp m_timestamp = {0};
    };

    bool applyExternOperation(unsigned int _id, const std::string& _buffer) override;

   private:
    Mindmap(unsigned int _localID) : m_localID(_localID) {}

    void applyOperation(const MindmapSetNameOperation& _op);

    /// ------------------------------------------------------------------------

    unsigned int m_localID;  // Used for Timestamp
    collabserver::LWWRegister<std::string, Timestamp> m_name;
};
