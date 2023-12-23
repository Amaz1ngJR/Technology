打开终端cd到要上传文件的工作目录
```bash
cd /yjr/test
```
初始化一个新的本地git仓库
```bash
git init #执行多次 git init 不会清空原来的仓库
#Git 在该目录中创建一个 .git 子目录 其中包含 Git 仓库的配置、对象、引用等信息
#如果已经存在 .git 子目录 再次运行 git init 会忽略这个操作
```
删除这个已有的git仓库
```bash
rm -rf .git  # 删除.git子目录
```
添加文件到git暂存区中
```bash
git add . #添加所有的文件
git add filename #添加指定文件
```
清空 Git 缓存区
```bash
git reset #清空所有文件的缓存区
git reset --hard  #清空所有文件的缓存区并取消所有本地修改
git reset filename #清空某个文件的缓存区
```
提交暂存区中的更改到本地git仓库
```bash
git config --global user.email "you@example.com"
git config --global user.name "Your Name"
#to set your account's default identity.
#Omit --global to set the identity only in this repository
git config user.name yjr
git config user.email superyanjunru@gmail.com
```
```bash
git commit -m "Initial commit(提交信息)"
```
查看本地仓库分支
```bash
git branch  #默认是master
git status
```
创建并切换到main分支
```bash
git branch main #创建main分支
git checkout main #切换到main分支
#上述两步合成一步
git checkout -b main
```
删除原有的master分支
```bash
git branch -d master #强制删除-D
```
将本地仓库(同时取别名为origin_name)关联到GitHub仓库
```bash
git remote add origin_name https://github.com/Amaz1ngJR/Test.git
```
将本地仓库的更改推送到 GitHub
```bash
git push -u origin_name main
```
