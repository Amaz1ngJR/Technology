# 虚拟环境
## 安装虚拟环境
### [安装Miniconda](https://www.anaconda.com/docs/getting-started/miniconda/install#macos-2)
```
mkdir -p ~/miniconda3
curl https://repo.anaconda.com/miniconda/Miniconda3-latest-MacOSX-arm64.sh -o ~/miniconda3/miniconda.sh
bash ~/miniconda3/miniconda.sh -b -u -p ~/miniconda3
rm ~/miniconda3/miniconda.sh
```
重启终端后执行以下命令 设置环境变量
```
source ~/miniconda3/bin/activate
```
### [安装miniforge可以免费商用](https://github.com/conda-forge/miniforge?tab=readme-ov-file)
选择合适的版本进行下载后
```
chmod +x Miniforge3*.sh
```
运行安装程序
```
./Miniforge3*.sh
```
设置环境变量
```
export PATH="/path/to/miniforge/bin:$PATH"
```

安装完上述conda后 第一次使用 需要conda init <shell> --将<shell>替换为你正在使用的shell，例如bash或zsh 然后关闭终端，再开一个新的
```
conda init --all
```
打开终端后会自动进入base
```
conda config --show auto_activate_base --看自动进入base的状态
conda config --set auto_activate_base false --关闭
conda config --set auto_activate_base true  --打开
```
## 虚拟环境相关
```
创建虚拟环境      conda create -n <环境名name> python=3.9
进/出虚拟环境     conda activate <环境名name> / conda deactivate
查看所有虚拟环境  conda env list 所有包 conda list 
删除虚拟环境      conda remove -n  <环境名name> --all
复制虚拟环境      conda create --name new_name --clone old_name

Mac下
创建虚拟环境          /usr/bin/python3 -m venv <环境名name> 
进/出虚拟环境         source <环境名name> /bin/activate / deactivate

CUDA版本：
使用nvcc --V查看的是cuda版本 使用nvidia-smi显示的CUDA是支持的最高版本，并不是当前的版本
```

## 依赖相关

记录依赖
```
pip freeze > requirements.txt
conda env export > environment.yml
```
快速搭建环境
```
pip install -r requirements.txt
conda env create -f environment.yml
```

## 镜像
```
pip install --upgrade pip
```
pip镜像
```
-i https://pypi.tuna.tsinghua.edu.cn/simple
-i https://pypi.mirrors.ustc.edu.cn/simple
-i https://mirrors.aliyun.com/pypi/simple/
```
# Python
