#include "game.h"

bool entertain(Player& player) {
    player.energy -= rules::entertainEnergyCost;
    player.stress -= rules::entertainStressReduction;
    return true;
}

bool work(Player& player) {
    player.money += rules::workMoneyGain;
    player.energy -= rules::workEnergyCost;
    player.stress += rules::workStressGain;
    return true;
}
