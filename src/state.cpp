#include "game.h"

#include <algorithm>

void normalize(Player& player) {
    for (int& knowledge : player.knowledge) {
        knowledge = std::clamp(knowledge, 0, rules::maximumStat);
    }
    player.energy = std::clamp(player.energy, 0, rules::maximumStat);
    player.stress = std::clamp(player.stress, 0, rules::maximumStat);
    player.money = std::max(player.money, 0);
}

void recoverAtNight(Player& player) {
    player.energy += rules::nightEnergyGain;
    player.stress -= rules::nightStressReduction;
    normalize(player);
}

