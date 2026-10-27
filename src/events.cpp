#include "game.h"

// 6号：每天晚上随机决定是否发生一件小事。
int rollEvent(std::mt19937& /* rng */) {
    // TODO(06): 50%返回0；25%返回1（排队），25%返回2（投喂）。
    return 0;  // Placeholder: random events are NOT implemented yet.
}

void applyEvent(Player& /* player */, int /* eventId */) {
    // TODO(06): 事件1压力+4，事件2精力+10，事件0什么都不做。
}

const char* eventText(int /* eventId */) {
    // TODO(06): 返回“今天很平静”“打印资料排队”“室友投喂”中的一句。
    return "[待实现/06] 随机事件文案";
}
