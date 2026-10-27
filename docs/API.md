# 函数怎么接

声明都在 `include/game.h`。大家照着现有函数补内容即可，数值也已经放在里面。

## 玩家数据

`Player`里面有三门课的进度 `knowledge[3]`、精力 `energy`、压力 `stress`、金钱 `money`。课程编号0高数、1英语、2 C++。

## 各人负责的函数

| 人员 | 函数 | 要做什么 |
|---|---|---|
| 1号 | `runGame()` | 记录第几天、哪个时段，把其他人的函数串起来 |
| 2号 | `normalize()`、`recoverAtNight()` | 整理数值、每天晚上的恢复 |
| 3号 | `study()`、`rest()` | 复习、休息 |
| 4号 | `entertain()`、`work()` | 娱乐、兼职 |
| 5号 | `buyItem(Player&, int itemId)` | 商品1咖啡、2零食 |
| 6号 | `rollEvent()`、`applyEvent()`、`eventText()` | 事件0没事、1排队、2投喂 |
| 7号 | `evaluateEnding()`、`printEnding()` | 判断并打印结局 |
| 8号 | `showChanges()`、`showStatus()` | 显示变化和当前状态 |

## 几个返回值

- 行动和购买返回 `true`：做成了，1号推进时间。返回 `false`：没做成，不推进。
- `evaluateEnding()`里的 `finished` 表示是否走完5天。没走完只判断崩溃；走完才判断成绩。
- 菜单和输入函数已经有实现。课程选择返回0～2，取消返回-1；商店选择返回1或2，0表示取消。
- 日期从1开始，时段用0/1/2表示早/午/晚。

行动函数改完数值后，1号调用 `normalize()`，再交给8号显示。3～6号不用自己读菜单或推进时间。
