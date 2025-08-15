# 虚拟环境
## 安装虚拟环境
[安装Miniconda](https://www.anaconda.com/docs/getting-started/miniconda/install#macos-2)
```
mkdir -p ~/miniconda3
curl https://repo.anaconda.com/miniconda/Miniconda3-latest-MacOSX-arm64.sh -o ~/miniconda3/miniconda.sh
bash ~/miniconda3/miniconda.sh -b -u -p ~/miniconda3
rm ~/miniconda3/miniconda.sh
```
重启终端后执行
```
source ~/miniconda3/bin/activate
conda init --all
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
pip镜像
```
-i https://pypi.tuna.tsinghua.edu.cn/simple
-i https://pypi.mirrors.ustc.edu.cn/simple
-i https://mirrors.aliyun.com/pypi/simple/
```
# 
