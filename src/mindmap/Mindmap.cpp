#include "mindmap/Mindmap.h"

#include <cassert>
#include <mutex>

static std::mutex l_opMutex;

// -----------------------------------------------------------------------------

Mindmap Mindmap::build(unsigned int _localID) { return Mindmap(_localID); }

std::unique_ptr<Mindmap> Mindmap::buidlnew(unsigned int _localID) {
    std::unique_ptr<Mindmap> mindmap(new Mindmap(_localID));
    return mindmap;
}

// -----------------------------------------------------------------------------

const std::string& Mindmap::getName() const { return m_name.query(); }

void Mindmap::setName(const std::string& _name) {
    Timestamp::setEffectiveID(m_localID);
    MindmapSetNameOperation op = {_name, Timestamp::now()};
    this->applyOperation(op);
    this->notifyOperationBroadcaster(op);
};

void Mindmap::addMarker(const Marker& _marker) {
    Timestamp::setEffectiveID(m_localID);
    MindmapAddMarkerOperation op = {_marker, Timestamp::now()};
    this->applyOperation(op);
    this->notifyOperationBroadcaster(op);
}

void Mindmap::removeMarker(const Marker& _marker) {
    Timestamp::setEffectiveID(m_localID);
    MindmapRemoveMarkerOperation op = {_marker, Timestamp::now()};
    this->applyOperation(op);
    this->notifyOperationBroadcaster(op);
}

// -----------------------------------------------------------------------------

void Mindmap::applyOperation(const MindmapSetNameOperation& _op) {
    std::lock_guard<std::mutex> lock(l_opMutex);
    auto& tnow = _op.m_timestamp;
    bool isUpdate = m_name.update(_op.m_name, tnow);
    if (isUpdate) {
        this->notifyOperationObservers(_op);
    }
}

void Mindmap::applyOperation(const MindmapAddMarkerOperation& _op) {
    std::lock_guard<std::mutex> lock(l_opMutex);
    auto& tnow = _op.m_timestamp;
    bool isAdded = m_markers.add(_op.m_marker, tnow);
    if (isAdded) {
        this->notifyOperationObservers(_op);
    }
}

void Mindmap::applyOperation(const MindmapRemoveMarkerOperation& _op) {
    std::lock_guard<std::mutex> lock(l_opMutex);
    auto& tnow = _op.m_timestamp;
    bool isRemoved = m_markers.remove(_op.m_marker, tnow);
    if (isRemoved) {
        this->notifyOperationObservers(_op);
    }
    // TODO also remove all links to this marker
}

bool Mindmap::applyExternOperation(unsigned int _id, const std::string& _buffer) {
    std::stringstream opBuffer(_buffer);

    switch (_id) {
        case OPERATION_MINDMAP_SET_NAME: {
            MindmapSetNameOperation op;
            if (!op.unserialize(opBuffer)) {
                return false;
            }
            Timestamp::setEffectiveID(op.m_timestamp.getID());
            applyOperation(op);
        } break;

        case OPERATION_MARKER_ADD: {
            MindmapAddMarkerOperation op;
            if (!op.unserialize(opBuffer)) {
                return false;
            }
            Timestamp::setEffectiveID(op.m_timestamp.getID());
            applyOperation(op);
        } break;

        case OPERATION_MARKER_REMOVE: {
            MindmapRemoveMarkerOperation op;
            if (!op.unserialize(opBuffer)) {
                return false;
            }
            Timestamp::setEffectiveID(op.m_timestamp.getID());
            applyOperation(op);
        } break;

        default:
            assert(false);  // Unexpected operation
            return false;
    }

    return false;
}

// -----------------------------------------------------------------------------

Mindmap::MindmapSetNameOperation::MindmapSetNameOperation(const std::string& _name, const Timestamp& _time)
    : m_name(_name), m_timestamp(_time) {}

bool Mindmap::MindmapSetNameOperation::serialize(std::stringstream& _buffer) const {
    _buffer << m_name;
    return true;
}

bool Mindmap::MindmapSetNameOperation::unserialize(const std::stringstream& _buffer) {
    std::string str(_buffer.str());
    m_name = str;
    return true;
}

void Mindmap::MindmapSetNameOperation::accept(collabserver::CollabDataOperationHandler& _handler) const {
    // TODO there is nothing to do for now
}

// -----------------------------------------------------------------------------

Mindmap::MindmapAddMarkerOperation::MindmapAddMarkerOperation(const Marker& _marker, const Timestamp& _time)
    : m_marker(_marker), m_timestamp(_time) {}

bool Mindmap::MindmapAddMarkerOperation::serialize(std::stringstream& _buffer) const {
    // TODO
    //_buffer << m_marker.getSymbol();
    return true;
}

bool Mindmap::MindmapAddMarkerOperation::unserialize(const std::stringstream& _buffer) {
    std::string str(_buffer.str());
    m_marker.setSymbol(str);
    return true;
}

void Mindmap::MindmapAddMarkerOperation::accept(collabserver::CollabDataOperationHandler& _handler) const {
    // TODO there is nothing to do for now
}

// -----------------------------------------------------------------------------

Mindmap::MindmapRemoveMarkerOperation::MindmapRemoveMarkerOperation(const Marker& _marker, const Timestamp& _time)
    : m_marker(_marker), m_timestamp(_time) {}

bool Mindmap::MindmapRemoveMarkerOperation::serialize(std::stringstream& _buffer) const {
    // TODO
    //_buffer << m_marker.getSymbol();
    return true;
}

bool Mindmap::MindmapRemoveMarkerOperation::unserialize(const std::stringstream& _buffer) {
    std::string str(_buffer.str());
    m_marker.setSymbol(str);
    return true;
}

void Mindmap::MindmapRemoveMarkerOperation::accept(collabserver::CollabDataOperationHandler& _handler) const {
    // TODO there is nothing to do for now
}