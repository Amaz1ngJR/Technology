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
get_video_frame(OutputStream *ost) //用于生成一帧 YUV 格式的合成图像 准备原始帧
```
负责获取一帧原始视频数据,返回值是一个指向 AVFrame 的指针

write_frame(...)
```c++
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

## 转推流程
### initInputContext 初始化输入上下文
avformat_open_input负责读取输入源的头部信息，并为后续处理（如查找流、解码等）准备上下文
```c++
int avformat_open_input(AVFormatContext **ps, const char *filename, const AVInputFormat *fmt, AVDictionary **options);
//ps：输出参数。该函数会分配一个 AVFormatContext 结构体，并将其地址赋值给 *ps。这个结构体保存了整个输入文件/流的信息（比如：所有流、元数据、时长、格式等）
//filename：文件路径或 URL。可以是本地文件路径，也可以是网络地址
//fmt:指定输入格式。如果为 NULL，FFmpeg 会自动检测输入格式；如果你确定输入格式（比如是 mpegts 或 hls），可以传入对应的 AVInputFormat 指针ps 来跳过自动探测
//options:选项字典，用于传递一些格式特定的配置选项（例如：超时时间、协议选项、分析时间等）。可为 NULL 表示不使用额外选项

avformat_open_input(&m_ifmt_ctx, m_inputPath.c_str(), NULL, NULL);
```
avformat_find_stream_info从输入多媒体文件或流中读取包头并**获取流信息**的函数。这个函数对于初始化 AVFormatContext 的内部状态至关重要，它会填充上下文中有关音频、视频和其他数据流的详细信息

```c++
int avformat_find_stream_info(AVFormat/XMLSchemaNameHere *ic, AVDictionary **options);
//ic: 这是一个指向已经通过 avformat_open_input() 打开的 AVFormatContext 实例的指针。该结构体包含了关于输入媒体的所有相关信息。
//options: 一个指向字典的指针，用于存储一些额外的选项。这通常是为某些特定的解复用器（demuxer）提供附加指令，例如指定分析时间限制等。如果不需要这些选项，则可以传入 NULL

avformat_find_stream_info(m_ifmt_ctx, NULL);
//可通过下面函数打印出调试信息以确认流信息是否被正确解析
av_dump_format(fmt_ctx, 0, url, 0);
```
### initOutputContext 初始化输出上下文
avformat_alloc_output_context2用于**创建**输出上下文（AVFormatContext）并初始化其基本结构的重要函数
```c++
int avformat_alloc_output_context2(AVFormatContext **ctx, const AVOutputFormat *oformat,
                                   const char *format_name, const char *filename);
//ctx:输出参数，函数会分配一个 AVFormatContext 结构体，并将其地址赋值给 *ctx。后续用于添加流、写头、写帧等操作
//oformat:指定输出格式。如果为 NULL，FFmpeg 会根据 format_name 或 filename 自动选择合适的输出格式
//format_name:输出格式名称字符串（如 "mp4"、"mpegts"、"flv" 等）。可为 NULL，此时由 filename 推断格式
//filename:输出文件路径或 URL

avformat_alloc_output_context2(&m_ofmt_ctx, NULL, NULL, m_url.c_str())

const AVOutputFormat *oformat = av_guess_format("mpegts", NULL, NULL); // 强制指定为 MPEG-TS 格式
AVFormatContext *ofmt_ctx = NULL;
int ret = avformat_alloc_output_context2(&ofmt_ctx, oformat, NULL, "output.ts");

```
常见输出格式

|格式名称|	用途|
|----|-----|
|mp4	|MP4 文件|
|mpegts	|MPEG-TS 流（常用于网络传输）|
|flv	|Flash 视频格式（RTMP 推流常用）|
|hls	|HTTP Live Streaming（分片输出）|
|image2	|图像序列（如 JPEG 序列）|

创建完输出上下文 AVFormatContext后，往往需要
```
添加流 avformat_new_stream()
设置编解码参数（codecpar）
安全复制编码参数 avcodec_parameters_copy()
使用 avio_open() 打开输出 IO 上下文（即连接到实际的文件或网络）
打开输出文件 avformat_write_header() 写入文件头信息
循环写入压缩帧/数据包（av_write_frame() 或 av_interleaved_write_frame()）
最后写入尾部信息：avformat_write_trailer()
关闭 IO：avio_closep(&m_ofmt_ctx->pb)
关闭输出 释放上下文（av_write_trailer() 和 avformat_free_context()）
```

### writeHeader

