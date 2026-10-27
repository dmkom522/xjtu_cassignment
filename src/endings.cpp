#include "game.h"

#include <iostream>

// Owner 07. Do not mutate Player or ask for input in the evaluator.
Ending evaluateEnding(const Player& /* player */, bool /* finished */) {
    // TODO(07): Burnout first; when finished, Excellent -> Pass -> Retake.
    // Before the final turn, a surviving player returns None.
    return Ending::None;
}

void printEnding(Ending /* ending */, const Player& /* player */) {
    // TODO(07): four ending texts plus final values. None has no ending text.
    std::cout << "[待实现/07] 结局展示\n";
}
