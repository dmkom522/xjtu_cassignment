#include "game.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace {
class ConsoleFixture {
public:
    explicit ConsoleFixture(const std::string& input = "")
        : input_(input), oldInput_(std::cin.rdbuf()), oldOutput_(std::cout.rdbuf()) {
        std::cin.clear();
        std::cin.rdbuf(input_.rdbuf());
        std::cout.rdbuf(output_.rdbuf());
    }
    ~ConsoleFixture() {
        std::cin.rdbuf(oldInput_);
        std::cout.rdbuf(oldOutput_);
        std::cin.clear();
    }
    std::string output() const { return output_.str(); }
    ConsoleFixture(const ConsoleFixture&) = delete;
    ConsoleFixture& operator=(const ConsoleFixture&) = delete;
private:
    std::istringstream input_;
    std::ostringstream output_;
    std::streambuf* oldInput_;
    std::streambuf* oldOutput_;
};

void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}

bool same(const Player& a, const Player& b) {
    for (int i = 0; i < rules::courseCount; ++i) {
        if (a.knowledge[i] != b.knowledge[i]) return false;
    }
    return a.energy == b.energy && a.stress == b.stress && a.money == b.money;
}

std::size_t count(const std::string& text, const std::string& needle) {
    require(!needle.empty(), "output marker must not be empty");
    std::size_t result = 0;
    for (std::size_t pos = 0; (pos = text.find(needle, pos)) != std::string::npos;
         pos += needle.size()) ++result;
    return result;
}

// Derive the heading from the UI, keeping tests independent of its decoration.
std::string heading(int day, int slot) {
    ConsoleFixture console;
    showStatus(Player{}, day, slot);
    const std::string text = console.output();
    const auto begin = text.find_first_not_of('\n');
    require(begin != std::string::npos, "status must display a heading");
    return text.substr(begin, text.find('\n', begin) - begin);
}

std::string play(const std::string& input) {
    ConsoleFixture console(input);
    runGame();
    return console.output();
}

void testModules() {
    Player p;
    const Player initial = p;
    require(!study(p, -1) && !study(p, rules::courseCount) && same(p, initial),
            "invalid course must not modify state");
    require(study(p, 2) && p.knowledge[2] == 35 && p.knowledge[0] == 20 &&
            p.energy == 55 && p.stress == 30, "study must change only the selected course");
    require(rest(p) && p.energy == 85 && p.stress == 15, "rest effects");
    require(entertain(p) && p.energy == 80 && p.stress == -10,
            "entertain must leave normalization to the game loop");
    require(work(p) && p.energy == 70 && p.stress == -5 && p.money == 50,
            "work effects");

    p = initial;
    p.money = 15;
    require(buyItem(p, 1) && p.money == 0 && p.energy == 95 && p.stress == 25,
            "coffee must accept exact funds");
    Player before = p;
    require(!buyItem(p, 2) && !buyItem(p, 0) && !buyItem(p, 3) && same(p, before),
            "unaffordable and unknown purchases must not modify state");
    p.money = 10;
    require(buyItem(p, 2) && p.money == 0 && p.energy == 100 && p.stress == 5,
            "snack must accept exact funds");

    p = initial;
    applyEvent(p, 0);
    require(same(p, initial), "quiet event must do nothing");
    applyEvent(p, 1);
    applyEvent(p, 2);
    require(p.stress == 24 && p.energy == 80 && p.money == 30, "event effects");
    std::mt19937 rng(42), reference(42);
    std::uniform_int_distribution<int> draw(0, 3);
    for (int i = 0; i < 20; ++i) {
        const int value = draw(reference);
        require(rollEvent(rng) == (value < 2 ? 0 : value - 1), "event mapping");
    }
}

void testStateAndEndings() {
    Player p;
    p.knowledge[0] = -1;
    p.knowledge[1] = 115;
    p.energy = 130;
    p.stress = -10;
    p.money = -1;
    normalize(p);
    require(p.knowledge[0] == 0 && p.knowledge[1] == 100 && p.knowledge[2] == 20 &&
            p.energy == 100 && p.stress == 0 && p.money == 0, "normalize bounds");
    p.energy = 95;
    p.stress = 3;
    p.money = 120;
    recoverAtNight(p);
    require(p.energy == 100 && p.stress == 0 && p.money == 120, "night recovery and money bounds");

    p = Player{};
    p.energy = 95;
    p.stress = 3;
    const Player before = p;
    rest(p);
    normalize(p);
    ConsoleFixture console;
    showChanges(before, p);
    require(console.output().find("+5") != std::string::npos &&
            console.output().find("-3") != std::string::npos &&
            console.output().find("+30") == std::string::npos &&
            console.output().find("-15") == std::string::npos, "display actual normalized deltas");

    for (int& score : p.knowledge) score = 80;
    require(evaluateEnding(p, false) == Ending::None, "grades must not end an unfinished game");
    require(evaluateEnding(p, true) == Ending::Excellent, "80 in every course is excellent");
    p.knowledge[2] = 60;
    require(evaluateEnding(p, true) == Ending::Pass, "60 boundary passes");
    p.knowledge[2] = 59;
    require(evaluateEnding(p, true) == Ending::Retake, "one failing course requires retake");
    for (int& score : p.knowledge) score = 100;
    p.energy = 0;
    require(evaluateEnding(p, false) == Ending::Burnout &&
            evaluateEnding(p, true) == Ending::Burnout, "energy burnout overrides grades");
    p.energy = 100;
    p.stress = 100;
    require(evaluateEnding(p, true) == Ending::Burnout, "stress burnout overrides grades");
}

void testGameLoop() {
    std::string input;
    for (int day = 1; day <= 5; ++day) input += "1\n1\n2\n2\n";
    std::string output = play(input);
    for (int day = 1; day <= 5; ++day) {
        for (int slot = 0; slot < 3; ++slot) {
            require(count(output, heading(day, slot)) == 1, "visit all 15 slots exactly once");
        }
    }
    require(count(output, "最终成绩") == 1 && output.find("重修") != std::string::npos,
            "full game must finish once with the correct ending");
    require(output.find(heading(6, 0)) == std::string::npos, "no sixth day");
    require(count(output, "晚间事件：") == 5 && count(output, "夜间恢复：") == 4,
            "five evening events and only four overnight recoveries");

    input.clear();
    int studyCount = 0;
    for (int slot = 1; slot <= 15; ++slot) {
        if (slot == 6 || slot == 10 || slot == 14) {
            input += "2\n";
        } else {
            input += "1\n" + std::to_string(studyCount++ % 3 + 1) + "\n";
        }
    }
    output = play(input);
    require(count(output, "最终成绩") == 1 && output.find("学霸") != std::string::npos,
            "balanced twelve-study schedule must reach the excellent ending");
    require(count(output, "晚间事件：") == 5 && count(output, "夜间恢复：") == 4,
            "excellent game must complete all five evenings without fifth-night recovery");

    input.clear();
    for (int i = 0; i < 15; ++i) input += "1\n1\n";
    output = play(input);
    require(output.find("崩溃") != std::string::npos && count(output, "最终成绩") == 1 &&
            output.find(heading(4, 0)) == std::string::npos, "continuous study burns out early");

    // Cancel both submenus, spend all money, then attempt one more purchase.
    output = play("1\n0\n5\n0\n5\n1\n5\n1\n5\n1\n0\n");
    require(count(output, heading(1, 0)) == 3 && count(output, heading(1, 1)) == 1 &&
            count(output, heading(1, 2)) == 2 && output.find(heading(2, 0)) == std::string::npos,
            "cancellation and insufficient funds must not advance time");
    require(output.find("最终成绩") == std::string::npos, "quitting must not award an ending");
    require(play("").find("最终成绩") == std::string::npos, "EOF exits without a result");
}
}  // namespace

int main() {
    try {
        testModules();
        testStateAndEndings();
        testGameLoop();
        std::cout << "PASS: gameplay modules, five-day loop, burnout and cancellation.\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
