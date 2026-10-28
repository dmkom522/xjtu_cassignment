#include "game.h"

// 5号：只卖咖啡和零食，购买后立即生效。钱够就扣钱、加效果并返回true；不够返回false。
bool buyItem(Player& player, int itemId) {
    if (itemId == 1) {  // 咖啡：15元，精力+25，压力+5。
        if (player.money < rules::coffeePrice) {
            return false;
        }
        player.money -= rules::coffeePrice;
        player.energy += rules::coffeeEnergyGain;
        player.stress += rules::coffeeStressGain;
        return true;
    }

    if (itemId == 2) {  // 零食：10元，精力+5，压力-20。
        if (player.money < rules::snackPrice) {
            return false;
        }
        player.money -= rules::snackPrice;
        player.energy += rules::snackEnergyGain;
        player.stress -= rules::snackStressReduction;
        return true;
    }

    return false;  // 未知商品，不做任何事。
}
