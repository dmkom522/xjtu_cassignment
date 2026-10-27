#include "game.h"

// Owner 06. The caller creates/seeds the RNG once, not on every draw.
int rollEvent(std::mt19937& /* rng */) {
    // TODO(06): 0 with probability 50%, 1..4 each with probability 12.5%.
    return 0;  // Placeholder: random events are NOT implemented yet.
}

void applyEvent(Player& /* player */, int /* eventId */) {
    // TODO(06): implement IDs 1..4; ID 0 / unknown IDs make no changes.
    // Lowest-course ties are resolved by the first course index.
}

const char* eventText(int /* eventId */) {
    // TODO(06): supply one message for each event, including ID 0.
    return "[待实现/06] 随机事件文案";
}
