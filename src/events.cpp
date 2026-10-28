#include "game.h"

// 6号：每天晚上随机决定是否发生一件小事。
int rollEvent(std::mt19937& rng) {
    // TODO(06): 50%返回0；25%返回1（排队），25%返回2（投喂）。
    std::uniform_int_distribution<int> dist(0, 3);
    int num = dist(rng);

    if (num == 0 || num == 1) {
        return 0;
    } else if (num == 2) {
        return 1;
    } else {
        return 2;
    }
}

void applyEvent(Player& player, int eventId) {
    // TODO(06): 事件1压力+4，事件2精力+10，事件0什么都不做。
    if (eventId == 1) {
        player.stress += rules::eventStressGain;
    } else if (eventId == 2) {
        player.energy += rules::eventEnergyGain;
    }
}

const char* eventText(int eventId) {
    // TODO(06): 返回“今天很平静”“打印资料排队”“室友投喂”中的一句。
    if (eventId == 0) {
        return "今天很平静";
    } else if (eventId == 1) {
        return "打印资料排队";
    } else if (eventId == 2) {
        return "室友投喂";
    }
    return "";
}
