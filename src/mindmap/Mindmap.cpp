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
    MindmapSetNameOperation op;
    op.m_timestamp = 0;  // TODO to update with actual timestamp
    op.m_name = _name;
    this->applyOperation(op);
    this->notifyOperationBroadcaster(op);
    // TODO
};

// -----------------------------------------------------------------------------

void Mindmap::applyOperation(const MindmapSetNameOperation& op) {
    std::lock_guard<std::mutex> lock(l_opMutex);
    auto& tnow = op.m_timestamp;
    bool isUpdate = m_name.update(op.m_name, tnow);
    if (isUpdate) {
        this->notifyOperationObservers(op);
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
            applyOperation(op);
        } break;
        default:
            assert(false);  // Unexpected operation
            return false;
    }

    return false;
}

// -----------------------------------------------------------------------------

bool Mindmap::MindmapSetNameOperation::serialize(std::stringstream& buffer) const {
    buffer << m_name;
    return true;
}

bool Mindmap::MindmapSetNameOperation::unserialize(const std::stringstream& buffer) {
    std::string str(buffer.str());
    m_name = str;
    return true;
}

void Mindmap::MindmapSetNameOperation::accept(collabserver::CollabDataOperationHandler& handler) const {
    // TODO
}
