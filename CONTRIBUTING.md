# 怎么一起交代码

1. 在 `docs/TASKS.md` 认领自己的编号。
2. 从main开一个自己的分支，改自己负责的文件。
3. 运行看看效果，提交到GitHub，向main发一个PR。
4. PR写两句：改了什么、运行看到了什么。9号负责合并，有问题找对应成员改。

以5号为例：

```sh
git switch main
git pull --ff-only
git switch -c feature/shop
# 写好 src/shop.cpp 后
git add src/shop.cpp
git commit -m "完成咖啡和零食购买"
git push -u origin feature/shop
```

接着到GitHub点“Compare & pull request”即可。也可以用IDE或GitHub Desktop完成这些操作。

公共函数声明在 `include/game.h`。需要改声明时和2号说一下，让调用这个函数的人一起改。
