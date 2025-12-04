# 大模型广场
[硅基流动](https://cloud.siliconflow.cn/i/106OLolx)
邀请码
```
106OLolx
```
<img width="1418" height="947" alt="image" src="https://github.com/user-attachments/assets/3721f389-2d6a-4ab0-aeb1-46b56c17f53e" />

[免费gpt本地api](https://github.com/popjane/free_chatgpt_api)
[Poe](https://poe.com/)
# 本地部署聊天工具
[chatbox](https://chatboxai.app/zh)

<img width="1024" height="768" alt="image" src="https://github.com/user-attachments/assets/1b3f4d17-f6c9-477b-b642-5da3ecb370ca" />


<img width="1024" height="768" alt="image" src="https://github.com/user-attachments/assets/45c62fb5-7149-41fa-a670-58d8874679ae" />

# Claude Code for Macos
```bash
# 安装 Node.js
brew install node
# 安装 Claude Code
sudo npm install -g @anthropic-ai/claude-code
# 国内镜像安装
npm install -g @anthropic-ai/claude-code --registry https://registry.npmmirror.com
# 使用 Claude Code
claude
```
创建配置文件
```bash
# 对于 zsh (默认)
echo 'export ANTHROPIC_BASE_URL="http://10.20.49.8/api/"' >> ~/.zshrc
echo 'export ANTHROPIC_AUTH_TOKEN="你的API密钥"' >> ~/.zshrc
echo 'export CLAUDE_CODE_MAX_OUTPUT_TOKENS=64000' >> ~/.zshrc
source ~/.zshrc
# 对于 bash
echo 'export ANTHROPIC_BASE_URL="http://10.20.49.8/api/"' >> ~/.bash_profile
echo 'export ANTHROPIC_AUTH_TOKEN="你的API密钥"' >> ~/.bash_profile
echo 'export CLAUDE_CODE_MAX_OUTPUT_TOKENS=64000' >> ~/.bash_profile
source ~/.bash_profile
```
或创建Claude code配置文件
路径：~/.claude/settings.json
```json
{
  "env": {
    "ANTHROPIC_AUTH_TOKEN": "cr_d7d6b7cb521b703c8acda91cccab504b23045104d690ac24bc23f2d822822bbd",
    "ANTHROPIC_BASE_URL": "https://ai.vdian.net/api/"
  },
  "model": "sonnet"
}
```
>cr_d7d6b7cb521b703c8acda91cccab504b23045104d690ac24bc23f2d822822bbd
# Claude Code for Linux
```bash
# 卸载旧版 Node.js
# node -v   # 应输出 v20.x.x
sudo apt remove --purge nodejs npm
sudo apt autoremove  # 清理自动安装的依赖
# 下载并运行 NodeSource 的安装脚本（支持 ARM64）
curl -fsSL https://deb.nodesource.com/setup_20.x | sudo -E bash -
# 安装 nodejs（会自动包含 npm）
sudo apt install -y nodejs
# 更新 PATH 环境变量 
export PATH="/usr/bin:$PATH"
# 永久生效 - 添加到 ~/.bashrc
echo 'export PATH="/usr/bin:$PATH"' >> ~/.bashrc
source ~/.bashrc
# 
# 安装 Claude Code
sudo npm install -g @anthropic-ai/claude-code
# 国内镜像安装
sudo npm install -g @anthropic-ai/claude-code --registry https://registry.npmmirror.com

# 安装 NVM
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.5/install.sh | bash

# 重新加载 shell 配置
source ~/.bashrc

# 使用 Claude Code
claude
```
