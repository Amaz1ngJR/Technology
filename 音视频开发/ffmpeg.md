[教程](https://zhuanlan.zhihu.com/p/15849180981)
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


## 总览
FFmpeg 视频编码流程图
```
+-------------------+
| 原始视频帧 (AVFrame) |
+-------------------+
          ↓
+---------------------------+
| avcodec_send_frame()      | ← 将原始帧送入编码器
+---------------------------+
          ↓
+---------------------------+
| avcodec_receive_packet()  | ← 编码后得到 AVPacket
+---------------------------+
          ↓
+-----------------------------+
| av_write_frame() 或          |
| av_interleaved_write_frame() |
+-----------------------------+
          ↓
+---------------------------+
| 数据包写入输出文件 (.mp4/.mkv 等) |
+---------------------------+
```
对应的函数
```
get_video_frame(ost)
```
负责获取一帧原始视频数据,返回值是一个指向 AVFrame 的指针

write_frame(...)
```
avcodec_send_frame(c, frame) //将原始帧（AVFrame）发送给编码器进行编码
//循环调用 avcodec_receive_packet()
while (ret >= 0) {
    ret = avcodec_receive_packet(c, pkt);
    ...
    av_write_frame(fmt_ctx, pkt);
}
//使用 av_write_frame() 或 av_interleaved_write_frame()
//将编码后的 AVPacket 写入输出文件
```

