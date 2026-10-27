# GitHub协作流程

## 认领和分支

先阅读 docs/TASKS.md，在认领表填写编号、姓名/GitHub。只改自己负责的模块；公共声明交2号统一维护。不要一次性替其他成员实现全部功能。

首次获取：

```sh
git clone https://github.com/dmkom522/xjtu_cassignment.git
cd xjtu_cassignment
git switch main
git pull --ff-only
git switch -c feature/shop
```

把 `feature/shop` 换成自己的模块分支。可使用命令行、GitHub Desktop或IDE的Git界面，流程一致。

## 提交

完成小块行为后先编译和自测，然后只暂存自己修改的文件。例如5号：

```sh
git status
git add src/shop.cpp
git commit -m "feat: implement one-item shop purchases"
git push -u origin feature/shop
```

不要提交build、IDE缓存、可执行文件、本机凭证。不要伪造成员身份或替其他人虚构贡献。

## PR

在GitHub从个人分支向main发起PR，使用仓库模板填写：具体行为、测试步骤与实际结果、已知问题、接口影响。每个人至少能解释自己提交的代码与测试。

交叉检查建议：03与04、05与02、06与07互看；01/08/09重点检查集成。9号统一合并，模块问题交原作者修复。

更新个人分支时，先保存/提交当前修改，再执行：

```sh
git fetch origin
git merge origin/main
```

发生冲突时与相关文件作者一起处理，再编译。不要通过覆盖整个文件来消除冲突。main应始终能编译；正在实现的分支可以先发Draft PR说明进度。

## 完成标准

- 接口符合 include/game.h 和 docs/API.md。
- 已实现行为的TODO已替换，未实现行为仍明确标注。
- 编译通过，已有测试通过，本模块的正常/边界结果有记录。
- PR写明尚未验证的内容，不能把骨架测试称为完整游戏验收。
- 合并后更新本地main，再开始下一项工作。
