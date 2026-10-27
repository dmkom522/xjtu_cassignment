#include "game.h"

#include <iostream>

// Owner 01: replace the menu demonstration with the full game loop.
// See docs/TASKS.md#成员01主流程 and docs/RULES.md for the exact sequence.
void runGame() {
    Player player;
    constexpr int demoDay = 1;
    constexpr int demoSlot = 0;
    std::cout << "\n[协作骨架演示] 行动、事件、时间推进和结局尚未实现。\n";

    while (true) {
        showStatus(player, demoDay, demoSlot);
        const int action = chooseAction();
        if (action <= 0) {
            return;
        }

        const Player before = player;
        bool success = false;
        switch (action) {
            case 1: {
                const int course = chooseCourse();
                if (course < 0) {
                    continue;
                }
                success = study(player, course);
                break;
            }
            case 2:
                success = rest(player);
                break;
            case 3:
                success = entertain(player);
                break;
            case 4:
                success = work(player);
                break;
            case 5: {
                const int item = chooseItem();
                if (item <= 0) {
                    continue;
                }
                const int course = item == 3 ? chooseCourse() : -1;
                if (item == 3 && course < 0) {
                    continue;
                }
                success = buyItem(player, item, course);
                break;
            }
            default:
                continue;
        }

        if (!success) {
            std::cout << "[待实现] 当前模块尚未产生有效行动；时间和状态保持原样。\n";
            continue;
        }

        // TODO(01): normalize -> showChanges -> early failure -> advance slot.
        // After a surviving evening: event -> normalize -> early failure;
        // days 1..4 recover overnight; day 5 runs the final ending check.
        normalize(player);
        showChanges(before, player);
        std::cout << "[待实现/01] 行动接口已返回成功，日期与结局逻辑仍需补全。\n";
    }
}
