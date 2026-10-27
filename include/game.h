#pragma once

#include <random>

// 2号维护：大家共用的数据、数值和函数声明。
namespace rules {
inline constexpr int courseCount = 3;
inline constexpr int dayCount = 5;
inline constexpr int slotsPerDay = 3;
inline constexpr int maximumStat = 100;
inline constexpr int initialKnowledge = 20;
inline constexpr int initialEnergy = 70;
inline constexpr int initialStress = 20;
inline constexpr int initialMoney = 30;
inline constexpr int studyGain = 15;
inline constexpr int studyEnergyCost = 15;
inline constexpr int studyStressGain = 10;
inline constexpr int restEnergyGain = 30;
inline constexpr int restStressReduction = 15;
inline constexpr int entertainEnergyCost = 5;
inline constexpr int entertainStressReduction = 25;
inline constexpr int workMoneyGain = 20;
inline constexpr int workEnergyCost = 10;
inline constexpr int workStressGain = 5;
inline constexpr int coffeePrice = 15;
inline constexpr int coffeeEnergyGain = 25;
inline constexpr int coffeeStressGain = 5;
inline constexpr int snackPrice = 10;
inline constexpr int snackEnergyGain = 5;
inline constexpr int snackStressReduction = 20;
inline constexpr int nightEnergyGain = 15;
inline constexpr int nightStressReduction = 5;
inline constexpr int eventStressGain = 4;
inline constexpr int eventEnergyGain = 10;
inline constexpr int passThreshold = 60;
inline constexpr int excellentThreshold = 80;
inline constexpr const char* courseNames[courseCount] = {"高数", "英语", "C++"};
inline constexpr const char* slotNames[slotsPerDay] = {"早上", "下午", "晚上"};
}  // namespace rules

struct Player {
    int knowledge[rules::courseCount] = {
        rules::initialKnowledge, rules::initialKnowledge, rules::initialKnowledge};
    int energy = rules::initialEnergy;
    int stress = rules::initialStress;
    int money = rules::initialMoney;
};

enum class Ending { None, Burnout, Excellent, Pass, Retake };

// 1号：把游戏串起来。day是第1～5天，slot是早/午/晚对应的0/1/2。
void runGame();

// 2号：把数值限制在范围内，以及每天晚上的恢复。
void normalize(Player& player);
void recoverAtNight(Player& player);

// 3号、4号：只改数值。成功返回true；取消或没做成返回false，不扣时间。
// course：0高数、1英语、2 C++。菜单输入已经由ui.cpp处理。
bool study(Player& player, int course);
bool rest(Player& player);
bool entertain(Player& player);
bool work(Player& player);

// 5号：itemId为1买咖啡、2买零食。钱够就扣钱并生效，钱不够返回false。
bool buyItem(Player& player, int itemId);

// 6号：0没事发生、1排队压力+4、2室友投喂精力+10。
// 可以随机取0～3：0/1都表示没事，2映射为事件1，3映射为事件2。
int rollEvent(std::mt19937& rng);
void applyEvent(Player& player, int eventId);
const char* eventText(int eventId);

// 7号：finished=false时只看有没有崩溃，true时再看三门成绩。
Ending evaluateEnding(const Player& player, bool finished);
void printEnding(Ending ending, const Player& player);

// 8号：显示文字。下面的输入函数和菜单已经能用，不需要重写。
// readInt读不到输入时返回-1；chooseCourse返回0～2，取消时返回-1。
// chooseAction返回0～5，chooseItem返回0～2，0表示返回。
int readInt(int minValue, int maxValue);
int chooseAction();
int chooseCourse();
int chooseItem();
void showWelcome();
void showRules();
void showStatus(const Player& player, int day, int slot);
void showChanges(const Player& before, const Player& after);
