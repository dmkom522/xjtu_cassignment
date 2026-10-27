# 公共接口与职责

唯一公共头文件：`include/game.h`。这里的说明与头文件声明一起作为协作约定，2号集中维护。需要修改接口时在PR里列出受影响模块并通知对应成员。

## 数据

- `Player`：`knowledge[3]`、`energy`、`stress`、`money`，默认值已定义。
- `Ending`：`None / Burnout / Excellent / Pass / Retake`。
- `rules::...`：全部规则数值；不在不同模块重复定义同名常量。
- 日期`day`为1～5；时段`slot`为0～2；只有主流程拥有和更新日期/时段。
- 课程函数参数为0高数、1英语、2 C++。菜单数字在UI层转换。

## 函数契约

| 函数 | 负责人 | 输入/输出和副作用 |
|---|---|---|
| `runGame()` | 01 | 组织整局流程；目前仅菜单演示。返回后回到主菜单 |
| `normalize(Player&)` | 02 | 修改为有效范围；不打印、不推进时间 |
| `recoverAtNight(Player&)` | 02 | 夜间恢复后normalize；调用时机由01保证 |
| `study(Player&, int)` | 03 | 合法课程应用效果并true；非法课程false且整个状态不变 |
| `rest(Player&)` | 03 | 休息效果，返回true |
| `entertain(Player&)` | 04 | 娱乐效果，返回true |
| `work(Player&)` | 04 | 兼职效果，返回true |
| `buyItem(Player&, int, int=-1)` | 05 | 所有验证成功后扣钱+效果并true；其他情况false且状态不变 |
| `rollEvent(std::mt19937&)` | 06 | 只抽编号，不修改Player，不打印；使用传入的RNG |
| `applyEvent(Player&, int)` | 06 | 只应用指定效果；ID0和非法ID不修改状态 |
| `eventText(int)` | 06 | 返回静态有效字符串，不能返回局部string的c_str |
| `evaluateEnding(const Player&, bool)` | 07 | 只判定，不修改、不打印、不读输入 |
| `printEnding(Ending, const Player&)` | 07 | 展示结局和最终状态；None不打印结局 |
| `readInt(int,int)` | 08 | 读取整行；非法/越界/溢出/尾随字符重试，EOF返回-1；反向范围抛invalid_argument |
| `chooseAction()` | 08 | 返回0～5，EOF为-1 |
| `chooseCourse()` | 08 | 菜单1～3映射为0～2；取消和EOF均返回-1 |
| `chooseItem()` | 08 | 返回0～3，EOF为-1；0取消 |
| `showWelcome()/showRules()` | 08 | 开始菜单与玩法说明，不修改状态 |
| `showStatus(const Player&,int,int)` | 08 | 显示当前日期时段与全部状态 |
| `showChanges(const Player&,const Player&)` | 08 | 展示after-before真实差值，允许负数，不修改状态 |

## 数值整理和输入输出

行动/事件先产生原始效果，主流程随后调用normalize并用修改前后的Player显示变化。夜间恢复函数在内部完成normalize。不要在行动函数里读取输入、打印菜单、调用其他行动或推进时间。

有效行动即使只产生部分增益，或直接导致崩溃，也返回true并消耗一个时段；满值不构成失败。false只能用于非法参数或购买条件失败，且必须保持所有字段不变。

`study`/商店调用前先通过UI处理取消；不要把取消变成数组下标-1。主菜单、行动菜单遇到EOF要返回或退出，不能反复重试已关闭的输入流。

## RNG与可测试性

主流程构造一个`std::mt19937`并初始化一次。事件效果测试直接指定ID；完整路线测试可以暂时使用ID0。相同seed在不同标准库下的分布结果不保证完全一致，不把跨平台固定序列当作契约。

## 当前骨架的边界

多数业务函数刻意没有实现：行动返回false、normalize和事件无效果、evaluateEnding返回None。它们是占位，不是正确玩法。完成模块时替换这些函数体，并保留此处约定的签名和行为。
