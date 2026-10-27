#include "game.h"

// Owner 03. No console input/output here. Use the shared rules constants.
bool study(Player& /* player */, int /* course */) {
    // TODO(03): reject invalid course without mutation; otherwise apply effects.
    return false;  // Placeholder: NOT an implemented game action.
}

bool rest(Player& /* player */) {
    // TODO(03): apply rest effects. Full stats do not cancel an otherwise valid action.
    return false;
}
