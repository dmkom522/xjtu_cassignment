# 期末周生存指南 · C++ 小组作业

9人合作的C++17控制台文字游戏：在5天期末周里安排复习、休息、娱乐、兼职和购物，管理精力、压力与金钱，最后进入不同结局。

**当前版本是可编译的协作骨架。** 已提供固定接口、初始数据、菜单演示、可恢复的整数输入、编译入口和基础测试。行动、数值整理、夜间恢复、随机事件、时间推进、结局和变化展示仍是明确标记的占位实现。

## 开始前先读

1. [游戏规则](docs/RULES.md)：数值、顺序、随机事件、结局。
2. [接口约定](docs/API.md)：参数编号、返回值、副作用、调用职责。
3. [9人任务](docs/TASKS.md)：逐人文件、实现清单、自测与提交要求。
4. [GitHub协作](CONTRIBUTING.md)：个人分支、自测、PR、合并。
5. [验收计划](docs/TEST_PLAN.md)：骨架检查与将来完整游戏验收的区别。

## 当前能运行什么

- 主菜单：进入演示、查看计划规则、退出。
- 演示：显示初始状态，选择行动/课程/商品，取消与返回。
- 错误输入可以重试，输入结束会退出，不会无限循环。
- 占位行动返回false，状态和时段不改变，并显示“待实现”。

演示可以检查项目是否正确编译、链接和读取输入，不能当作可玩的游戏。每个成员完成模块后，1号再把演示替换成真正的5天循环。

## 编译与运行

需要C++17编译器与CMake 3.20或以上。

**Windows + CLion：**直接打开仓库根目录的CMake项目，选择 `finals_survival` 运行；测试目标为 `skeleton_tests`。

**Windows脚本：**已安装MinGW、CMake、Ninja，或使用默认位置的CLion时，可双击：

- `build.bat`：编译并执行基础测试。
- `run.bat`：编译、测试后打开菜单演示。

PowerShell同样可以执行：

```powershell
.\scripts\build.ps1 -Test -Run
```

脚本仅临时调整当前进程的工具路径；不会安装软件或修改系统PATH。如果工具不在PATH和默认CLion目录，使用CLion配置自己的工具链。不要混用已有构建目录中的不同CMake生成器；需要时另选一个构建目录。

**Linux/macOS或通用CMake环境：**

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
./build/finals_survival
```

也可运行 `sh scripts/build.sh` 只做编译与测试。Windows使用多配置生成器时，可执行文件通常在 `build/Debug/`；上述Windows脚本使用Ninja，位于 `build/`。不要求每个人采用同一IDE，但应使用相同规则与接口。

## 目录与负责人

```text
include/game.h            02：公共数据、数值、函数声明
src/main.cpp             01：程序入口
src/game.cpp             01：主流程（当前为菜单演示）
src/state.cpp            02：数值范围和夜间恢复
src/actions_basic.cpp    03：复习、休息
src/actions_extra.cpp    04：娱乐、兼职
src/shop.cpp             05：商店
src/events.cpp           06：随机事件
src/endings.cpp          07：结局
src/ui.cpp               08：输入、菜单、状态和变化展示
tests/smoke_tests.cpp     09：基础测试与后续模块验收入口
docs/                    规则、接口、任务、验收计划
scripts/                 编译脚本
.github/                 CI、PR与任务模板
CMakeLists.txt           09：构建入口
```

姓名尚未分配，先用01～09对应认领。[TASKS.md](docs/TASKS.md)保留认领表。初始化提交不代表9个人已完成作业；各成员应提交自己理解并验证过的代码及测试记录。

## 验证边界

`skeleton_tests`目前只检查整数输入、取消编号转换与EOF处理，所有占位玩法仍未验证。GitHub Actions配置了Windows和Linux编译检查，实际是否成功以对应工作流结果为准。完整游戏完成后，必须执行 [TEST_PLAN.md](docs/TEST_PLAN.md) 中的路线与边界用例。
