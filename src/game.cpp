#include "game.h"

#include <iostream>

void runGame() {
    Player player;
    int day = 1;
    int slot = 0;
    std::mt19937 rng(std::random_device{}());

    while (true) {
        showStatus(player, day, slot);
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
                success = buyItem(player, item);
                break;
            }
            default:
                continue;
        }

        if (!success) {
            std::cout << "金钱不足，购买失败，不消耗时段。\n";
            continue;
        }

        normalize(player);
        showChanges(before, player);
        Ending ending = evaluateEnding(player, false);
        if (ending != Ending::None) {
            printEnding(ending, player);
            return;
        }

        if (slot + 1 < rules::slotsPerDay) {
            ++slot;
            continue;
        }

        const Player beforeEvent = player;
        const int event = rollEvent(rng);
        std::cout << "晚间事件：" << eventText(event) << '\n';
        applyEvent(player, event);
        normalize(player);
        showChanges(beforeEvent, player);
        // Check the event before recovery; the last evening has no recovery.
        ending = evaluateEnding(player, day == rules::dayCount);
        if (ending != Ending::None) {
            printEnding(ending, player);
            return;
        }

        const Player beforeRecovery = player;
        recoverAtNight(player);
        std::cout << "夜间恢复：\n";
        showChanges(beforeRecovery, player);
        ++day;
        slot = 0;
    }
}

