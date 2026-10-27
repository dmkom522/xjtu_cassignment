#include "game.h"

#include <exception>
#include <iostream>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    try {
        while (true) {
            showWelcome();
            const int choice = readInt(0, 2);
            if (choice <= 0) {
                std::cout << "已退出。\n";
                return 0;
            }
            if (choice == 1) {
                runGame();
            } else {
                showRules();
            }
        }
    } catch (const std::exception& error) {
        std::cerr << "程序错误：" << error.what() << '\n';
        return 1;
    }
}
