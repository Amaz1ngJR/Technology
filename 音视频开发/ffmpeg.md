## homebrew安装ffmpeg
```
brew install ffmpeg

brew install ffmpeg --HEAD
```
源码安装
```
git clone git://source.ffmpeg.org/ffmpeg.git
```
## ffmpeg基本语法结构
先安装vlc
```
brew install vlc
```
```
vlc path/to/vedio
```
FFmpeg 命令行的基本形式为：
```
ffmpeg [全局参数] {[输入文件参数] -i 输入文件地址}... {[输出文件参数] 输出文件地址}...
```
全局参数影响整个程序运行，像 “-loglevel” 用于设置日志级别，“-y” 可不经确认直接覆盖输出文件；

输入文件参数紧跟 “-i” 指定输入源特性，如 “-ss” 设定输入文件起始时间；

输出文件参数决定输出结果，像 “-c:v” 指定视频编码器，“-b:v” 控制视频比特率。
举个例子，将一个 MP4 视频转换为 AVI 格式，同时降低视频码率，命令如下：
```
ffmpeg -i input.mp4 -b:v 500k -c:v libx264 output.avi
```
“-b:v 500k” 把视频比特率设为 500k，“-c:v libx264” 选用 libx264 编码器进行视频编码
```
ffmpeg \-y \-c:a libfdk_aac -c:v libx264 \-i input.mp4 \-c:v libvpx-vp9 -c:a libvorbis \output.webm
```
这里，“\” 换行符连接多行，全局参数 “-y” 居首，接着是输入文件参数，最后是输出文件参数与输出文件名，逻辑清晰，便于理解与修改
