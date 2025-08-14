# 虚拟环境
[安装Miniconda](https://www.anaconda.com/docs/getting-started/miniconda/install#macos-2)
```
mkdir -p ~/miniconda3
curl https://repo.anaconda.com/miniconda/Miniconda3-latest-MacOSX-arm64.sh -o ~/miniconda3/miniconda.sh
bash ~/miniconda3/miniconda.sh -b -u -p ~/miniconda3
rm ~/miniconda3/miniconda.sh
```
依赖相关

记录依赖
```
pip freeze > requirements.txt
```
快速搭建环境
```
pip install -r requirements.txt
```
# 
