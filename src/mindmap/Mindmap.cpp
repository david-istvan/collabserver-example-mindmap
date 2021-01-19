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

void Mindmap::setName(std::string& _name) {
    Timestamp::setEffectiveID(m_localID);
    MindmapSetNameOperation op = {_name, Timestamp::now()};
    this->applyOperation(op);
    this->notifyOperationBroadcaster(op);
};

// -----------------------------------------------------------------------------

void Mindmap::applyOperation(const MindmapSetNameOperation& _op) {
    std::lock_guard<std::mutex> lock(l_opMutex);
    auto& tnow = _op.m_timestamp;
    bool isUpdate = m_name.update(_op.m_name, tnow);
    if (isUpdate) {
        this->notifyOperationObservers(_op);
    }
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
    // TODO
}
