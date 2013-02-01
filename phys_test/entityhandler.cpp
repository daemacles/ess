#include "entityhandler.h"

void EntityHandler::callUpdates (void) {
    for (auto p : dynamicEnts) {
        auto ent = p.second;
        ent->update();
    }
}
