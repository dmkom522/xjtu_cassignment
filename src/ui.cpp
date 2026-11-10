#include "game.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

// Basic input recovery is provided so the skeleton can be tested and exited.
// Owner 08: status display and actual-value deltas.
int readInt(int minValue, int maxValue) {
    if (minValue > maxValue) {
        throw std::invalid_argument("readInt: minValue > maxValue");
    }
    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream input(line);
        int value = 0;
        char extra = '\0';
        if ((input >> value) && !(input >> extra) && value >= minValue && value <= maxValue) {
            return value;
        }
        std::cout << "请输入 " << minValue << "～" << maxValue << " 之间的整数：";
    }
    return -1;
}

void showWelcome() {
    std::cout << "\n=== 期末周生存指南 · 协作骨架 ===\n"
              << "1. 查看菜单演示（游戏逻辑待各成员实现）\n"
              << "2. 查看计划规则\n"
              << "0. 退出\n请选择：";
}

void showRules() {
    std::cout << "\n[计划规则，尚未实现]\n"
              << "5天，每天3个时段；复习三门课，同时管理精力、压力和金钱。\n"
              << "精力归零或压力达到100提前失败；最终三课全80为学霸，全60为过关。\n"
              << "完整规则与9人分工请阅读 docs/RULES.md 和 docs/TASKS.md。\n";
}

int chooseAction() {
    std::cout << "1.复习  2.休息  3.娱乐  4.兼职  5.商店  0.返回\n请选择：";
    return readInt(0, 5);
}

int chooseCourse() {
    std::cout << "1.高数  2.英语  3.C++  0.取消\n请选择课程：";
    const int selected = readInt(0, 3);
    return selected <= 0 ? -1 : selected - 1;
}

int chooseItem() {
    std::cout << "1.咖啡(" << rules::coffeePrice << ")  2.零食(" << rules::snackPrice
              << ")  0.取消\n请选择商品：";
    return readInt(0, 2);
}

void showStatus(const Player& player, int day, int slot) {
    const char* slotName = slot >= 0 && slot < rules::slotsPerDay
                               ? rules::slotNames[slot] : "未知时段";
    std::cout << "\n=== 第 " << day << " / " << rules::dayCount
              << " 天 · " << slotName << " ===\n";
    for (int course = 0; course < rules::courseCount; ++course) {
        std::cout << rules::courseNames[course] << ':' << player.knowledge[course] << "  ";
    }
    std::cout << "\n精力:" << player.energy << "  压力:" << player.stress
              << "  金钱:" << player.money << '\n';
}

void showChanges(const Player& before, const Player& after) {
    // The caller normalizes first; compare the actual values rather than bonuses.
    bool changed = false;
    std::cout << "本次变化：";
    const auto printChange = [&changed](const char* name, int oldValue, int newValue) {
        const int delta = newValue - oldValue;
        if (delta == 0) {
            return;
        }
        if (changed) {
            std::cout << "  ";
        }
        std::cout << name << ' ' << (delta > 0 ? "+" : "") << delta;
        changed = true;
    };

    for (int course = 0; course < rules::courseCount; ++course) {
        printChange(rules::courseNames[course], before.knowledge[course], after.knowledge[course]);
    }
    printChange("精力", before.energy, after.energy);
    printChange("压力", before.stress, after.stress);
    printChange("金钱", before.money, after.money);
    if (!changed) {
        std::cout << "无数值变化";
    }
    std::cout << '\n';
}
