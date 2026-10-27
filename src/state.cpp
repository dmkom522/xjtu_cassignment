#include "game.h"

// Owner 02. State defaults and constants are declared in include/game.h.
void normalize(Player& /* player */) {
    // TODO(02): clamp each course, energy and stress to [0, 100]; money >= 0.
}

void recoverAtNight(Player& /* player */) {
    // TODO(02): add nightEnergyGain, subtract nightStressReduction, normalize.
    // Owner 01 calls this only after surviving days 1..4.
}
