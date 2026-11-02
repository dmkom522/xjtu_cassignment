#include "game.h"

// Owner 03. No console input/output here. Use the shared rules constants.
bool study(Player& player, int course) {
    // 检查课程编号是否合法（0高数、1英语、2C++）。非法则不修改任何数值，直接返回 false
    if (course < 0 || course >= rules::courseCount) {
        return false;
    }

    // 应用复习效果：对应课程知识+15，精力-15，压力+10
    player.knowledge[course] += rules::studyGain;
    player.energy -= rules::studyEnergyCost;
    player.stress += rules::studyStressGain;

    return true;
}

bool rest(Player& player) {
    // 应用休息效果：精力+30，压力-15。数值溢出由其他模块的 normalize 处理
    player.energy += rules::restEnergyGain;
    player.stress -= rules::restStressReduction;

    return true;
}
