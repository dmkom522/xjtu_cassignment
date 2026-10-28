#include "game.h"

#include <iostream>

// Owner 07. Do not mutate Player or ask for input in the evaluator.
Ending evaluateEnding(const Player& player, bool finished) {
    // A burnout takes priority over the final grade, even if the player has
    // already completed all five days.
    if (player.energy <= 0 || player.stress >= rules::maximumStat) {
        return Ending::Burnout;
    }

    if (!finished) {
        return Ending::None;
    }

    bool excellent = true;
    bool passed = true;
    for (int course = 0; course < rules::courseCount; ++course) {
        excellent = excellent && player.knowledge[course] >= rules::excellentThreshold;
        passed = passed && player.knowledge[course] >= rules::passThreshold;
    }

    if (excellent) {
        return Ending::Excellent;
    }
    if (passed) {
        return Ending::Pass;
    }
    return Ending::Retake;
}

void printEnding(Ending ending, const Player& player) {
    switch (ending) {
        case Ending::Burnout:
            std::cout << "你因精力耗尽或压力过大而崩溃了。\n";
            break;
        case Ending::Excellent:
            std::cout << "三门课程都取得了优秀成绩，你成为了学霸！\n";
            break;
        case Ending::Pass:
            std::cout << "你稳住了状态，三门课程顺利过关。\n";
            break;
        case Ending::Retake:
            std::cout << "成绩没有达到要求，你需要重修。\n";
            break;
        case Ending::None:
            break;
    }

    std::cout << "最终成绩：\n";
    for (int course = 0; course < rules::courseCount; ++course) {
        std::cout << rules::courseNames[course] << ": " << player.knowledge[course]
                  << '\n';
    }
}
