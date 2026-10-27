#pragma once

#include <random>

// Public interface owner: member 02. Keep declarations in this file only.
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
inline constexpr int notesPrice = 25;
inline constexpr int notesKnowledgeGain = 10;
inline constexpr int nightEnergyGain = 15;
inline constexpr int nightStressReduction = 5;
inline constexpr int eventKnowledgeGain = 5;
inline constexpr int eventStressGain = 4;
inline constexpr int eventEnergyGain = 10;
inline constexpr int eventMoneyGain = 10;
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

// 01: game flow. day is 1..5, slot is 0..2; only this module advances time.
void runGame();

// 02: shared state. normalize is called by the game flow after each mutation.
void normalize(Player& player);
void recoverAtNight(Player& player);

// 03 / 04: true means success and consumes one slot; false must not change state.
// course: 0=math, 1=English, 2=C++. Actions do not read input or print menus.
bool study(Player& player, int course);
bool rest(Player& player);
bool entertain(Player& player);
bool work(Player& player);

// 05: itemId: 1=coffee, 2=snack, 3=notes. Validate everything before payment.
// course is required only for notes, and is ignored for coffee/snack.
bool buyItem(Player& player, int itemId, int course = -1);

// 06: eventId: 0=none, 1=notes, 2=queue, 3=food, 4=money.
// rollEvent: 50% none; the other four outcomes each have probability 12.5%.
int rollEvent(std::mt19937& rng);
void applyEvent(Player& player, int eventId);
const char* eventText(int eventId);

// 07: finished=false checks early failure only; finished=true also checks grades.
Ending evaluateEnding(const Player& player, bool finished);
void printEnding(Ending ending, const Player& player);

// 08: input and display. readInt retries invalid input; EOF returns -1.
// chooseAction: 0..5, or -1 on EOF. chooseItem: 0..3, or -1 on EOF.
// chooseCourse: 0..2, or -1 for cancel/EOF (menu numbers are converted here).
int readInt(int minValue, int maxValue);
int chooseAction();
int chooseCourse();
int chooseItem();
void showWelcome();
void showRules();
void showStatus(const Player& player, int day, int slot);
void showChanges(const Player& before, const Player& after);
