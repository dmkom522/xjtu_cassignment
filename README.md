# 期末周生存指南

9个人一起完成的C++文字游戏。5天里，每天早、午、晚各选一次行动，复习三门课，同时管理精力、压力和金钱，最后看能不能过关。

**核心玩法已接通，可以完整游玩5天。** 包含复习、休息、娱乐、兼职、商店、晚间事件和四种结局。

## 项目分工

原始[9人分工](docs/TASKS.md)保留了各模块的任务和接口。各成员已有实现已保留，缺失的主循环、数值整理和夜间恢复已补齐。

简化后的首版：

- 保留复习、休息、娱乐、兼职和4种结局。
- 商店只卖咖啡和零食。
- 每晚可能没事，也可能排队增加压力、室友投喂恢复精力。

具体数值看[游戏规则](docs/RULES.md)，函数参数看[接口说明](docs/API.md)。

## 怎么运行

Windows安装了CLion后，可以直接打开这个CMake项目，运行 `finals_survival`。

也可以双击：

- `run.bat`：编译并打开程序。
- `build.bat`：只编译和运行已有检查。

脚本会查找PATH或默认CLion目录里的工具。需要C++17、CMake 3.20或以上。使用其他安装位置时，在CLion里选择自己的工具链。

Linux/macOS或已经配好CMake的终端：

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
./build/finals_survival
```

运行后选“1. 开始游戏”。每次成功行动消耗一个时段；取消或钱不够不会推进时间。第5天晚上结算，精力归零或压力达到100会提前结束；结束后可回主菜单再玩一局。

## 写完怎么交

每人一个分支、一个PR，9号合并。PR写“做了什么、运行看到了什么”即可，详见[提交方法](CONTRIBUTING.md)。

已有输入检查和简短的玩法回归检查会随构建运行，覆盖完整5天、提前崩溃及取消/购买失败不耗时。[试玩说明](docs/TEST_PLAN.md)和[运行记录](docs/TEST_RESULTS.md)列出了实际验证范围。

Windows脚本需要CMake、Ninja和MinGW；若脚本找不到工具，可直接使用CLion已配置的工具链运行。

