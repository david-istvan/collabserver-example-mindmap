#pragma once

#include <collabserver/datatypes/CmRDT/LWWRegister.h>
#include <collabserver/datatypes/CmRDT/LWWSet.h>
#include <collabserver/datatypes/collabdata/CollabData.h>
#include <collabserver/datatypes/collabdata/CollabDataOperation.h>
#include <collabserver/datatypes/collabdata/CollabDataOperationHandler.h>

#include <memory>
#include <string>
#include <vector>

#include "CentralTopic.h"
#include "Marker.h"
#include "collaboration/Timestamp.h"

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
    void setName(const std::string& _name);

    void addMarker(const Marker& _marker);
    void removeMarker(const Marker& _marker);

    /// ------------------------------------------------------------------------

    // ID of all operations possible
    enum Operations : unsigned int { OPERATION_MINDMAP_SET_NAME, OPERATION_MARKER_ADD, OPERATION_MARKER_REMOVE };

    class MindmapSetNameOperation : public collabserver::CollabDataOperation {
       public:
        MindmapSetNameOperation() = default;
        MindmapSetNameOperation(const std::string& _name, const Timestamp& _time);
        bool serialize(std::stringstream& _buffer) const override;
        bool unserialize(const std::stringstream& _buffer) override;
        void accept(collabserver::CollabDataOperationHandler& _handler) const override;
        unsigned int getType() const override { return OPERATION_MINDMAP_SET_NAME; }

        std::string m_name;
        Timestamp m_timestamp = {0};
    };

    class MindmapAddMarkerOperation : public collabserver::CollabDataOperation {
       public:
        MindmapAddMarkerOperation() = default;
        MindmapAddMarkerOperation(const Marker& _marker, const Timestamp& _time);
        bool serialize(std::stringstream& _buffer) const override;
        bool unserialize(const std::stringstream& _buffer) override;
        void accept(collabserver::CollabDataOperationHandler& _handler) const override;
        unsigned int getType() const override { return OPERATION_MARKER_ADD; }

        Marker m_marker;
        Timestamp m_timestamp = {0};
    };

    class MindmapRemoveMarkerOperation : public collabserver::CollabDataOperation {
       public:
        MindmapRemoveMarkerOperation() = default;
        MindmapRemoveMarkerOperation(const Marker& _marker, const Timestamp& _time);
        bool serialize(std::stringstream& _buffer) const override;
        bool unserialize(const std::stringstream& _buffer) override;
        void accept(collabserver::CollabDataOperationHandler& _handler) const override;
        unsigned int getType() const override { return OPERATION_MARKER_REMOVE; }

        Marker m_marker;
        Timestamp m_timestamp = {0};
    };

    bool applyExternOperation(unsigned int _id, const std::string& _buffer) override;

   private:
    Mindmap(unsigned int _localID) : m_localID(_localID) {}

    void applyOperation(const MindmapSetNameOperation& _op);
    void applyOperation(const MindmapAddMarkerOperation& _op);
    void applyOperation(const MindmapRemoveMarkerOperation& _op);

    /// ------------------------------------------------------------------------

    unsigned int m_localID;  // Used for Timestamp
    collabserver::LWWRegister<std::string, Timestamp> m_name;
    collabserver::LWWSet<Marker, Timestamp> m_markers;
};
