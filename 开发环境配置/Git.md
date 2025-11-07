# Git 使用指南

## 目录
- [基础配置](#基础配置)
- [仓库初始化](#仓库初始化)
- [基本操作](#基本操作)
- [分支管理](#分支管理)
- [远程仓库](#远程仓库)
- [冲突解决](#冲突解决)
- [代理配置](#代理配置)
- [SSH 配置](#ssh-配置)
- [高级操作](#高级操作)
- [.gitignore 配置](#gitignore-配置)

## 基础配置

### 设置用户信息
Git 需要知道你是谁,这样才能正确记录提交者信息。

```bash
# 全局配置(适用于所有仓库)
git config --global user.name "Your Name"
git config --global user.email "you@example.com"

# 针对单个仓库配置(省略 --global)
git config user.name "yjr"
git config user.email ""
```

### 查看配置
```bash
# 查看所有配置
git config --list

# 查看特定配置
git config user.name
git config user.email

# 查看配置文件位置
git config --list --show-origin
```

## 仓库初始化

### 方式一:从零开始创建本地仓库

```bash
# 进入项目目录
cd /yjr/test

# 初始化 Git 仓库
git init
# 执行多次 git init 不会清空原来的仓库
# Git 在该目录中创建一个 .git 子目录,包含仓库的配置、对象、引用等信息
# 如果已经存在 .git 子目录,再次运行 git init 会忽略这个操作

# 指定初始分支名称
git init --initial-branch=main
```

### 方式二:克隆远程仓库
```bash
# 使用 HTTPS 克隆
git clone https://github.com/username/repository.git

# 使用 SSH 克隆(推荐)
git clone git@github.com:username/repository.git

# 克隆到指定目录
git clone git@github.com:username/repository.git myproject

# 克隆指定分支
git clone -b branch-name git@github.com:username/repository.git
```

### 删除已有的 Git 仓库
```bash
# 删除 .git 子目录,仓库变回普通文件夹
rm -rf .git
```

## 基本操作

### 查看状态
```bash
# 查看工作区状态
git status

# 简洁模式
git status -s

# 查看提交历史
git log

# 单行显示提交历史
git log --oneline

# 图形化显示分支历史
git log --graph --oneline --all
```

### 添加文件到暂存区
```bash
# 添加所有文件
git add .

# 添加指定文件
git add filename

# 添加多个文件
git add file1 file2 file3

# 添加指定目录下的所有文件
git add directory/

# 交互式添加
git add -i

# 添加文件的部分修改
git add -p filename
```

### 提交更改
```bash
# 提交暂存区的更改
git commit -m "提交信息"

# 添加并提交(跳过 git add)
git commit -am "提交信息"

# 修改最近一次提交
git commit --amend -m "新的提交信息"

# 修改最近一次提交(不改消息)
git commit --amend --no-edit
```

### 撤销操作
```bash
# 清空所有文件的暂存区
git reset

# 清空某个文件的暂存区
git reset filename

# 清空暂存区并取消所有本地修改(危险操作!)
git reset --hard

# 回退到指定提交(保留工作区修改)
git reset commit-hash

# 回退到指定提交(丢弃所有修改)
git reset --hard commit-hash

# 撤销工作区的修改
git checkout -- filename

# 撤销所有工作区修改
git checkout -- .
```

### 查看差异
```bash
# 查看工作区和暂存区的差异
git diff

# 查看暂存区和最新提交的差异
git diff --staged

# 查看两个提交之间的差异
git diff commit1 commit2

# 查看指定文件的差异
git diff filename
```

## 分支管理

### 查看分支
```bash
# 查看本地分支
git branch

# 查看远程分支
git branch -r

# 查看所有分支(本地+远程)
git branch -a

# 查看分支详细信息
git branch -v

# 查看已合并的分支
git branch --merged

# 查看未合并的分支
git branch --no-merged
```

### 创建和切换分支
```bash
# 创建新分支
git branch branch-name

# 切换到指定分支
git checkout branch-name

# 创建并切换到新分支(一步完成)
git checkout -b branch-name

# 使用 switch 命令(Git 2.23+推荐)
git switch branch-name
git switch -c branch-name  # 创建并切换
```

### 删除分支
```bash
# 删除本地分支(安全删除,未合并时会提示)
git branch -d branch-name

# 强制删除本地分支
git branch -D branch-name

# 删除远程分支
git push origin --delete branch-name
```

### 合并分支
```bash
# 合并指定分支到当前分支
git merge branch-name

# 禁用快进合并(保留合并历史)
git merge --no-ff branch-name

# 中止合并
git merge --abort
```

### 变基操作
```bash
# 将当前分支变基到指定分支
git rebase branch-name

# 交互式变基(可以修改、合并、删除提交)
git rebase -i commit-hash

# 继续变基
git rebase --continue

# 跳过当前提交
git rebase --skip

# 中止变基
git rebase --abort
```

## 远程仓库

### 查看远程仓库
```bash
# 查看远程仓库简要信息
git remote

# 查看远程仓库详细信息(包含 URL)
git remote -v

# 查看远程仓库详细信息
git remote show origin
```

### 添加协作者访问私有仓库

#### GitHub 添加协作者
1. 进入仓库页面,点击 **Settings**(设置)
2. 点击左侧的 **Collaborators**(协作者)
3. 点击 **Add people**(添加人员)
4. 输入对方的 GitHub 用户名或邮箱
5. 选择权限:
   - **Read**: 只能查看代码
   - **Write**: 可以推送代码
   - **Admin**: 管理员权限
6. 对方会收到邮件邀请,接受后即可访问

#### GitLab 添加成员
1. 进入项目,点击 **Settings** → **Members**
2. 点击 **Invite members**
3. 输入用户名或邮箱
4. 选择角色: Guest、Reporter、Developer、Maintainer
5. 点击 **Invite** 发送邀请

#### 使用个人访问令牌(适合脚本/CI)
1. GitHub: 头像 → **Settings** → **Developer settings** → **Personal access tokens**
2. 点击 **Generate new token**
3. 设置名称、过期时间和权限
4. 复制生成的令牌

使用令牌克隆:
```bash
# 方式1: 直接在 URL 中使用
git clone https://TOKEN@github.com/username/repo.git

# 方式2: 配置凭证管理器(推荐)
git config --global credential.helper store
git clone https://github.com/username/repo.git
# 然后输入用户名和令牌(作为密码)
```

### 添加远程仓库
```bash
# 添加远程仓库(origin 是默认名称)
git remote add origin https://github.com/username/repository.git

# 添加多个远程仓库(使用不同名称)
git remote add origin_name https://github.com/Amaz1ngJR/Test.git
git remote add upstream https://github.com/original/repository.git
```

### 修改远程仓库
```bash
# 重命名远程仓库
git remote rename old-name new-name

# 修改远程仓库 URL
git remote set-url origin new-url

# 删除远程仓库关联
git remote rm origin
```

### 拉取和推送
```bash
# 拉取远程仓库最新信息(不合并)
git fetch origin

# 拉取所有远程分支的最新信息
git fetch --all

# 拉取并合并(fetch + merge)
git pull origin branch-name

# 使用变基方式拉取
git pull --rebase origin branch-name

# 推送到远程仓库
git push origin branch-name

# 首次推送并设置上游分支
git push -u origin main
git push --set-upstream origin main  # 完整写法

# 推送所有分支
git push --all origin

# 推送标签
git push --tags origin

# 强制推送(危险操作!)
git push -f origin branch-name
```

## 冲突解决

### 处理合并冲突
```bash
# 场景:拉取远程代码时发生冲突
# 步骤1:保存当前工作
git stash push -m "我的本地修改"

# 步骤2:拉取远程最新代码
git pull origin branch-name

# 步骤3:恢复本地修改
git stash pop

# 步骤4:手动解决冲突
# 编辑冲突文件,查找并解决 <<<<<<< 和 >>>>>>> 标记的冲突部分

# 步骤5:标记冲突已解决
git add conflict-file

# 步骤6:完成合并
git commit -m "解决冲突"
```

### Stash 操作
```bash
# 保存当前工作区和暂存区的修改
git stash

# 保存并添加描述信息
git stash push -m "描述信息"

# 保存包括未跟踪的文件
git stash -u

# 查看 stash 列表
git stash list

# 恢复最近的 stash(不删除)
git stash apply

# 恢复最近的 stash(并删除)
git stash pop

# 恢复指定的 stash
git stash apply stash@{n}

# 删除指定的 stash
git stash drop stash@{n}

# 清空所有 stash
git stash clear
```
## 高级操作

### 标签管理
```bash
# 查看所有标签
git tag

# 创建轻量标签
git tag v1.0.0

# 创建附注标签(推荐,包含更多信息)
git tag -a v1.0.0 -m "版本 1.0.0 发布"

# 为历史提交打标签
git tag -a v0.9.0 commit-hash -m "标签说明"

# 查看标签详细信息
git show v1.0.0

# 推送标签到远程
git push origin v1.0.0

# 推送所有标签
git push origin --tags

# 删除本地标签
git tag -d v1.0.0

# 删除远程标签
git push origin --delete v1.0.0

# 检出标签(创建新分支)
git checkout -b branch-name v1.0.0
```

### Cherry-pick(摘取提交)
```bash
# 将指定提交应用到当前分支
git cherry-pick commit-hash

# 摘取多个提交
git cherry-pick commit1 commit2 commit3

# 摘取提交范围
git cherry-pick commit1..commit2

# 继续 cherry-pick
git cherry-pick --continue

# 中止 cherry-pick
git cherry-pick --abort
```

### 查找和调试
```bash
# 查找包含指定内容的提交
git log -S "search-string"

# 查找修改了指定文件的提交
git log --follow filename

# 查看文件每一行的最后修改信息
git blame filename

# ���分查找引入 bug 的提交
git bisect start
git bisect bad              # 标记当前版本为坏的
git bisect good commit-hash # 标记某个提交为好的
# Git 会自动切换到中间的提交,测试后标记
git bisect good  # 或 git bisect bad
# 重复直到找到问题提交
git bisect reset  # 结束二分查找
```

### 清理和优化
```bash
# 查看仓库大小
git count-objects -vH

# 清理未跟踪的文件(预览)
git clean -n

# 清理未跟踪的文件
git clean -f

# 清理未跟踪的文件和目录
git clean -fd

# 清理被忽略的文件
git clean -fX

# 清理所有未跟踪和被忽略的文件
git clean -fx

# 回收空间,优化仓库
git gc

# 更激进的清理
git gc --aggressive --prune=now
```

### 子模块管理
```bash
# 添加子模块
git submodule add https://github.com/username/repo.git path/to/submodule

# 克隆包含子模块的仓库
git clone --recursive repo-url

# 初始化和更新子模块
git submodule init
git submodule update

# 更新所有子模块
git submodule update --remote

# 查看子模块状态
git submodule status

# 删除子模块
git submodule deinit path/to/submodule
git rm path/to/submodule
rm -rf .git/modules/path/to/submodule
```

### 重写历史(危险操作)
```bash
# 修改最近 N 次提交
git rebase -i HEAD~N

# 修改作者信息
git commit --amend --author="Name <email>"

# 从历史中删除文件
git filter-branch --tree-filter 'rm -f password.txt' HEAD

# 使用 git-filter-repo(推荐,需安装)
git filter-repo --path password.txt --invert-paths
```

## 常用工作流

### 创建新仓库的完整流程
```bash
# 1. 在 GitHub 创建仓库后,在本地项目目录执行:
git init --initial-branch=main

# 2. 配置用户信息(如未全局配置)
git config user.name "Your Name"
git config user.email "your.email@example.com"

# 3. 添加文件并提交
git add .
git commit -m "Initial commit"

# 4. 关联远程仓库
git remote add origin https://github.com/username/repository.git

# 5. 推送到远程
git push -u origin main
```

### 克隆并开始工作
```bash
# 1. 克隆远程仓库
git clone git@github.com:username/repository.git
cd repository

# 2. 创建新分支开发
git checkout -b feature/new-feature

# 3. 开发并提交
git add .
git commit -m "实现新功能"

# 4. 推送分支
git push -u origin feature/new-feature
```

### 推送现有文件夹到新仓库
```bash
cd existing_folder
git init --initial-branch=main
git remote add origin git@github.com:username/repository.git
git add .
git commit -m "Initial commit"
git push --set-upstream origin main
```

### 推送现有 Git 仓库到新远程
```bash
cd existing_repo
git remote rename origin old-origin
git remote add origin git@github.com:username/repository.git
git push --set-upstream origin --all
git push --set-upstream origin --tags
```

## 代理配置

### HTTP/HTTPS 代理

#### 设置代理
```bash
# 设置全局 HTTP 代理
git config --global http.proxy http://127.0.0.1:7890

# 设置全局 HTTPS 代理
git config --global https.proxy http://127.0.0.1:7890

# 只对 GitHub 使用代理(推荐)
git config --global http.https://github.com.proxy http://127.0.0.1:7890
git config --global https.https://github.com.proxy http://127.0.0.1:7890
```

#### SOCKS5 代理
```bash
# 设置 SOCKS5 代理
git config --global http.proxy socks5://127.0.0.1:7891
git config --global https.proxy socks5://127.0.0.1:7891

# 只对 GitHub 使用 SOCKS5 代理
git config --global http.https://github.com.proxy socks5://127.0.0.1:7891
git config --global https.https://github.com.proxy socks5://127.0.0.1:7891
```

#### 查看代理配置
```bash
# 查看 HTTP 代理
git config --global --get http.proxy

# 查看 HTTPS 代理
git config --global --get https.proxy

# 查看所有代理配置
git config --global --get-all http.proxy
git config --global --get-all https.proxy

# 查看针对特定网站的代理
git config --global --get http.https://github.com.proxy
```

#### 取消代理
```bash
# 取消全局 HTTP 代理
git config --global --unset http.proxy

# 取消全局 HTTPS 代理
git config --global --unset https.proxy

# 取消所有 HTTPS 代理配置
git config --global --unset-all https.proxy

# 取消特定网站的代理
git config --global --unset http.https://github.com.proxy
git config --global --unset https.https://github.com.proxy
```

### SSH 代理配置

如果使用 SSH 方式连接 Git,可以在 `~/.ssh/config` 中配置代理:

```bash
# 编辑 SSH 配置文件
vim ~/.ssh/config

# 添加以下内容(使用 HTTP 代理)
Host github.com
    HostName github.com
    User git
    ProxyCommand nc -X connect -x 127.0.0.1:7890 %h %p

# 或使用 SOCKS5 代理
Host github.com
    HostName github.com
    User git
    ProxyCommand nc -X 5 -x 127.0.0.1:7891 %h %p
```

## SSH 配置

SSH(Secure Shell)是推荐的 Git 认证方式,比 HTTPS 更安全便捷。

### 检查现有 SSH 密钥
```bash
# 查看是否存在 SSH 密钥
ls -al ~/.ssh

# 常见的密钥文件名:
# id_rsa / id_rsa.pub (RSA)
# id_ecdsa / id_ecdsa.pub (ECDSA)
# id_ed25519 / id_ed25519.pub (Ed25519,推荐)
```

### 生成新的 SSH 密钥

#### Ed25519 算法(推荐)
```bash
# 生成 Ed25519 密钥(更安全,更快)
ssh-keygen -t ed25519 -C "your_email@example.com"

# 按提示操作:
# 1. 选择保存位置(默认 ~/.ssh/id_ed25519)
# 2. 设置密码短语(可选,但推荐)
```

#### RSA 算法(传统)
```bash
# 生成 RSA 密钥
ssh-keygen -t rsa -b 4096 -C "your_email@example.com"
```

### 启动 SSH 代理并添加密钥
```bash
# 启动 SSH 代理
eval "$(ssh-agent -s)"

# 添加 SSH 私钥到代理
ssh-add ~/.ssh/id_ed25519

# 如果使用 RSA
ssh-add ~/.ssh/id_rsa

# macOS 用户可以配置自动加载密钥
# 编辑 ~/.ssh/config 添加:
Host *
  AddKeysToAgent yes
  UseKeychain yes
  IdentityFile ~/.ssh/id_ed25519
```

### 获取 SSH 公钥
```bash
# macOS - 复制公钥到剪贴板
pbcopy < ~/.ssh/id_ed25519.pub

# Linux - 显示公钥内容
cat ~/.ssh/id_ed25519.pub

# Windows (Git Bash) - 复制公钥
clip < ~/.ssh/id_ed25519.pub
```

### 添加 SSH 公钥到 GitHub

1. 登录 GitHub
2. 进入 **Settings** → **SSH and GPG keys**
3. 点击 **New SSH key**
4. 填写标题(�� "My MacBook")
5. 粘贴公钥内容
6. 点击 **Add SSH key**

### 测试 SSH 连接
```bash
# 测试 GitHub 连接
ssh -T git@github.com

# 成功时会显示:
# Hi username! You've successfully authenticated...

# 测试 GitLab 连接
ssh -T git@gitlab.com

# 测试其他 Git 服务
ssh -T git@git.example.com
```

### 配置多个 SSH 密钥

如果需要为不同服务使用不同的 SSH 密钥:

```bash
# 编辑 SSH 配置文件
vim ~/.ssh/config

# 添加以下内容:
# GitHub
Host github.com
    HostName github.com
    User git
    IdentityFile ~/.ssh/id_ed25519_github

# GitLab
Host gitlab.com
    HostName gitlab.com
    User git
    IdentityFile ~/.ssh/id_ed25519_gitlab

# 公司内网 Git
Host git.company.com
    HostName git.company.com
    User git
    IdentityFile ~/.ssh/id_rsa_work
```

### SSH 故障排查
```bash
# 详细输出 SSH 连接过程
ssh -vT git@github.com

# 非常详细的输出
ssh -vvv git@github.com

# 检查 SSH 密钥权限
ls -la ~/.ssh/

# 正确的权限应该是:
# ~/.ssh 目录: 700
# 私钥文件: 600
# 公钥文件: 644
# config 文件: 644

# 修复权限
chmod 700 ~/.ssh
chmod 600 ~/.ssh/id_ed25519
chmod 644 ~/.ssh/id_ed25519.pub
chmod 644 ~/.ssh/config
```

## .gitignore 配置

`.gitignore` 文件用于告诉 Git 哪些文件或目录不需要纳入版本控制。
```
# 编译产物示例
*.o
*.class
*.exe
build/
dist/
*.log
.DS_Store
# xmake build artifacts
.xmake/
```
### 基本语法
```bash
# 注释以 # 开头

# 忽略所有 .log 文件
*.log

# 忽略特定文件
secret.txt

# 忽略整个目录
build/
dist/

# 忽略目录下的所有文件
node_modules/

# 不忽略特定文件(使用 !)
!important.log

# 只忽略当前目录的文件,不包括子目录
/TODO

# 忽略任何目录下的 TODO 文件
TODO

# 忽略 doc 目录下的 .txt 文件,但不包括 doc/notes/ 下的
doc/*.txt

# 忽略所有 .pdf 文件,包括子目录
**/*.pdf
```

### 常见项目类型的 .gitignore

#### 通用配置
```bash
# 操作系统文件
.DS_Store         # macOS
Thumbs.db         # Windows
desktop.ini       # Windows

# 编辑器文件
.vscode/
.idea/
*.swp
*.swo
*~

# 日志��件
*.log
logs/

# 临时文件
*.tmp
*.temp
*.bak
```

#### Node.js 项目
```bash
# 依赖目录
node_modules/
jspm_packages/

# 构建输出
dist/
build/
.next/
out/

# 环境变量
.env
.env.local
.env.*.local

# 调试日志
npm-debug.log*
yarn-debug.log*
yarn-error.log*

# 缓存目录
.npm
.eslintcache
.cache/
```

#### Python 项目
```bash
# 字节码文件
__pycache__/
*.py[cod]
*$py.class

# 虚拟环境
venv/
env/
ENV/
.venv

# 分发/打包
dist/
build/
*.egg-info/
*.egg

# 测试和覆盖率
.pytest_cache/
.coverage
htmlcov/

# Jupyter Notebook
.ipynb_checkpoints
```

#### Java 项目
```bash
# 编译文件
*.class
*.jar
*.war
*.ear

# 构建目录
target/
build/
out/

# IDE 文件
.idea/
*.iml
*.ipr
*.iws

# Gradle
.gradle/
gradle-app.setting

# Maven
pom.xml.tag
pom.xml.releaseBackup
pom.xml.versionsBackup
```

#### C/C++ 项目
```bash
# 编译产物
*.o
*.obj
*.exe
*.out
*.app

# 预编译头
*.gch
*.pch

# 库文件
*.so
*.dylib
*.dll
*.a
*.lib

# 构建目录
build/
cmake-build-*/

# xmake 构建产物
.xmake/
```

#### Go 项目
```bash
# 二进制文件
*.exe
*.exe~
*.dll
*.so
*.dylib

# 测试输出
*.test
*.out

# 依赖管理
vendor/
Godeps/

# 构建输出
bin/
```

### .gitignore 最佳实践

```bash
# 1. 在项目根目录创建 .gitignore
touch .gitignore

# 2. 如果文件已被跟踪,需要先从 Git 中移除
git rm --cached filename        # 移除文件
git rm --cached -r directory/   # 移除目录

# 3. 提交 .gitignore 文件
git add .gitignore
git commit -m "添加 .gitignore"
```

### 全局 .gitignore

对所有仓库生效的忽略规则:

```bash
# 创建全局 gitignore 文件
touch ~/.gitignore_global

# 配置 Git 使用全局 gitignore
git config --global core.excludesfile ~/.gitignore_global

# 编辑全局 gitignore
vim ~/.gitignore_global
```

全局 .gitignore 示例:
```bash
# 编辑器和 IDE
.vscode/
.idea/
*.swp
*.swo

# 操作系统
.DS_Store
Thumbs.db
desktop.ini

# 临时文件
*.tmp
*~
```

### 检查忽略规则

```bash
# 检查文件是否被忽略
git check-ignore -v filename

# 检查目录下所有文件的忽略状态
git check-ignore -v *

# 查看哪个规则导致文件被忽略
git check-ignore -v path/to/file
```

### 模板资源

可以访问 [gitignore.io](https://gitignore.io) 或 [GitHub 的 gitignore 模板仓库](https://github.com/github/gitignore) 获取各种语言和框架的 .gitignore 模板。

```bash
# 使用 curl 从 gitignore.io 获取模板
curl -L https://www.toptal.com/developers/gitignore/api/node,python,java > .gitignore
```

## 实用技巧和最佳实践

### 别名配置

使用别名简化常用命令:

```bash
# 设置别名
git config --global alias.co checkout
git config --global alias.br branch
git config --global alias.ci commit
git config --global alias.st status
git config --global alias.unstage 'reset HEAD --'
git config --global alias.last 'log -1 HEAD'
git config --global alias.visual 'log --graph --oneline --all'

# 使用别名
git co main
git st
git visual
```

### 常用别名推荐

```bash
# 美化的日志
git config --global alias.lg "log --color --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit"

# 显示所有别名
git config --global alias.aliases "config --get-regexp alias"

# 撤销最后一次提交但保留更改
git config --global alias.undo "reset HEAD~1 --mixed"

# 显示贡献者统计
git config --global alias.contributors "shortlog -sn"
```

### 提交信息规范

良好的提交信息格式:

```
<type>(<scope>): <subject>

<body>

<footer>
```

常见的 type 类型:
- `feat`: 新功能
- `fix`: 修复 bug
- `docs`: 文档更新
- `style`: 代码格式(不影响代码运行)
- `refactor`: 重构
- `test`: 测试相关
- `chore`: 构建过程或辅助工具变动

示例:
```bash
git commit -m "feat(user): 添加用户登录功能"
git commit -m "fix(api): 修复数据返回格式错误"
git commit -m "docs(readme): 更新安装说明"
```

### 性能优化

```bash
# 浅克隆(只克隆最近的提交历史)
git clone --depth 1 https://github.com/user/repo.git

# 只克隆单个分支
git clone --single-branch --branch main https://github.com/user/repo.git

# 增量克隆(部分克隆)
git clone --filter=blob:none https://github.com/user/repo.git

# 压缩仓库
git gc --aggressive --prune=now
```

### 安全相关

```bash
# 从历史中移除敏感文件(需要 git-filter-repo)
git filter-repo --path secret.txt --invert-paths

# 检查仓库中的凭证泄露
# 推荐使用工具: gitleaks, truffleHog

# 签名提交(需要 GPG 密钥)
git commit -S -m "签名提交"

# 配置自动签名
git config --global commit.gpgsign true
```

### 团队协作建议

```bash
# 1. 保持提交原子性 - 每次提交只做一件事
# 2. 及时拉取更新
git pull --rebase origin main

# 3. 使用分支开发功能
git checkout -b feature/new-feature

# 4. 代码审查前清理提交历史
git rebase -i HEAD~3

# 5. 使用 PR/MR 合并代码,不要直接推送到主分支

# 6. 保护重要分支
# 在 GitHub/GitLab 上设置分支保护规则
```

### 救命命令

```bash
# 撤销工作区的更改
git checkout -- filename

# 撤销暂存区的更改
git reset HEAD filename

# 撤销最后一次提交(保留更改)
git reset --soft HEAD~1

# 撤销最后一次提交(丢弃更改)
git reset --hard HEAD~1

# 找回删除的提交
git reflog
git cherry-pick <commit-hash>

# 修改提交作者
git commit --amend --author="Name <email>" --no-edit

# 从 stash 中恢复误删的更改
git fsck --lost-found
```

## 故障排查

### 常见问题和解决方案

#### 1. 推送被拒绝
```bash
# 问题: ! [rejected] main -> main (non-fast-forward)
# 解决: 先拉取合并再推送
git pull --rebase origin main
git push origin main
```

#### 2. 合并冲突
```bash
# 查看冲突文件
git status

# 手动编辑冲突文件后
git add conflict-file
git commit

# 或放弃合并
git merge --abort
```

#### 3. 错误的提交
```bash
# 修改最后一次提交
git commit --amend

# 撤销提交但保留更改
git reset --soft HEAD~1

# 完全撤销提交
git reset --hard HEAD~1
```

#### 4. 不小心提交了大文件
```bash
# 从最后一次提交中移除
git rm --cached large-file
git commit --amend

# 从历史中彻底移除(需要 git-filter-repo)
git filter-repo --path large-file --invert-paths
```

#### 5. 权限问题
```bash
# GitHub 权限被拒绝
# 检查 SSH 密钥
ssh -T git@github.com

# 检查远程 URL
git remote -v

# 切换到 SSH URL
git remote set-url origin git@github.com:user/repo.git
```

## 参考资源

- [Git 官方文档](https://git-scm.com/doc)
- [Pro Git 书籍](https://git-scm.com/book/zh/v2)
- [GitHub Guides](https://guides.github.com/)
- [Git 可视化学习](https://learngitbranching.js.org/?locale=zh_CN)
- [Git Cheat Sheet](https://education.github.com/git-cheat-sheet-education.pdf)