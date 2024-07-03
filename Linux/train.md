# 虚拟环境相关
```bash
创建虚拟环境      conda create -n <环境名name> python=0.0
进/出虚拟环境     conda activate <环境名name>/conda deactivate
查看所有虚拟环境  conda env list 所有包 conda list 
删除虚拟环境      conda remove -n  <环境名name> --all
复制虚拟环境      conda create --name new_name --clone old_name
conda install pytorch==1.13.1 torchvision==0.14.1 torchaudio==0.13.1 pytorch-cuda=11.7 -c pytorch -c nvidia
```
mac下
```zsh
创建虚拟环境          /usr/bin/python3 -m venv evenv(环境名)
进/出虚拟环境         source evenv(环境名)/bin/activate / deactivate
```
# 镜像
```bash
-i https://pypi.tuna.tsinghua.edu.cn/simple
-i https://pypi.mirrors.ustc.edu.cn/simple
-i https://mirrors.aliyun.com/pypi/simple/
```
