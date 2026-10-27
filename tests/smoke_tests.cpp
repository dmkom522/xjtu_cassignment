#include "game.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace {
class ConsoleFixture {
public:
    explicit ConsoleFixture(const std::string& text)
        : input_(text), oldInput_(std::cin.rdbuf()), oldOutput_(std::cout.rdbuf()) {
        std::cin.clear();
        std::cin.rdbuf(input_.rdbuf());
        std::cout.rdbuf(output_.rdbuf());
    }
    ~ConsoleFixture() {
        std::cin.rdbuf(oldInput_);
        std::cout.rdbuf(oldOutput_);
        std::cin.clear();
    }
    ConsoleFixture(const ConsoleFixture&) = delete;
    ConsoleFixture& operator=(const ConsoleFixture&) = delete;

private:
    std::istringstream input_;
    std::ostringstream output_;
    std::streambuf* oldInput_;
    std::streambuf* oldOutput_;
};

void require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}
}  // namespace

int main() {
    try {
        {
            ConsoleFixture console("hello\n-1\n6\n2abc\n2 3\n999999999999999999999\n  2  \n");
            require(readInt(0, 5) == 2, "invalid input must be discarded and retried");
        }
        {
            ConsoleFixture console("0\n5\n");
            require(readInt(0, 5) == 0, "lower boundary must be accepted");
            require(readInt(0, 5) == 5, "upper boundary must be accepted");
        }
        {
            ConsoleFixture console("");
            require(readInt(0, 5) == -1, "EOF must return -1 instead of looping forever");
        }
        {
            ConsoleFixture console("1\n3\n0\n");
            require(chooseCourse() == 0, "math menu number must map to index 0");
            require(chooseCourse() == 2, "C++ menu number must map to index 2");
            require(chooseCourse() == -1, "cancel must not become a course index");
        }
        {
            ConsoleFixture console("");
            bool rejected = false;
            try {
                static_cast<void>(readInt(5, 0));
            } catch (const std::invalid_argument&) {
                rejected = true;
            }
            require(rejected, "inverted input bounds must be rejected");
        }
        std::cout << "PASS: skeleton input/EOF checks. Gameplay is NOT implemented or verified.\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
    // TODO(09): add module tests as members complete their implementations.
    // Planned gameplay acceptance cases are in docs/TEST_PLAN.md.
}
