# 期末周生存指南

9个人一起完成的C++文字游戏。5天里，每天早、午、晚各选一次行动，复习三门课，同时管理精力、压力和金钱，最后看能不能过关。

**现在是可以编译的骨架，大家在已有文件里补自己的函数。** 输入、菜单、编译脚本和基础测试都已经准备好。

## 先看自己的任务

打开[9人分工](docs/TASKS.md)，认领一个编号。每个人的文件、要写的函数和完成效果都在里面。

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

现在运行会看到菜单和“待实现”提示，补完游戏函数后才会正常推进日期和结算。

## 写完怎么交

每人一个分支、一个PR，9号合并。PR写“做了什么、运行看到了什么”即可，详见[提交方法](CONTRIBUTING.md)。

各人先试一下自己的功能；最后9号完整试玩，再连续复习试一次提前结束。[试玩说明](docs/TEST_PLAN.md)已经列好，不需要大家另写一套测试。

编译配置和自动检查已经准备好，9号可以直接使用。已有的运行情况放在[运行记录](docs/TEST_RESULTS.md)。
