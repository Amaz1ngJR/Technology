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

添加流 avformat_new_stream()
```c++
AVStream *avformat_new_stream(AVFormatContext *s, const AVCodec *c);
//s: 指向已经初始化好的 AVFormatContext 的指针，表示你想要添加新流的目标输出上下文。
//c: 指向 AVCodec 结构体的指针，代表你想使用的编解码器。如果为 NULL，则不会自动设置编解码器上下文，你需要手动配置流的参数。
```

```
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
avio_open打开输出文件或网络流的 IO 层的一个函数调用
```c++
int avio_open(AVIOContext **s, const char *url, int flags);
//s: 输出参数。FFmpeg 会分配一个 AVIOContext 并将其地址赋给 *s。这个上下文用于读写数据到目标文件或网络。
//url:输出目标路径或 URL。可以是本地文件路径（如 "output.mp4"），也可以是网络地址（如 "rtmp://live.example.com/stream"）。
//flags:打开模式标志位。最常见的是 AVIO_FLAG_WRITE（写模式） 或 AVIO_FLAG_READ（读模式）。

avio_open(&m_ofmt_ctx->pb, m_url.c_str(), AVIO_FLAG_WRITE));
```
avformat_write_header写入输出文件或流的文件头信息
```c++
int avformat_write_header(AVFormatContext *s, AVDictionary **options);
//s: 指向 AVFormatContext 的指针，包含了输出格式的所有信息，包括但不限于编解码器参数、时间基准、元数据等。
//options: 一个指向字典的指针，可用于提供额外的选项给 muxer（复用器）。如果不需要传递任何选项，则可以传入 NULL

avformat_write_header(m_ofmt_ctx, NULL);
```

### startTranscoding
涉及到

分配 packet	av_packet_alloc()
```c++
AVPacket *packet = av_packet_alloc();
```
读取 packet	av_read_frame()
```c++
int av_read_frame(AVFormatContext *s, AVPacket *pkt);
//s:输入上下文，由 avformat_open_input() 创建并初始化。它包含了所有关于输入文件/流的信息。
//pkt:输出参数，用于接收读取到的一帧数据（可以是音频或视频

AVPacket packet;
while (av_read_frame(m_ifmt_ctx, &packet) >= 0){...}
```
写入输出	av_interleaved_write_frame()

与 av_write_frame() 相比，av_interleaved_write_frame() 能够确保音视频包按照正确的顺序（交错）写入输出文件，这对于多媒体容器格式非常重要，因为它们通常要求音频和视频数据交错存储以确保同步播放。
```c++
int av_interleaved_write_frame(AVFormatContext *s, AVPacket *pkt);
//s: 指向已经初始化好的 AVFormatContext 的指针，包含了所有关于输出文件或流的信息。
//pkt: 指向要写入的 AVPacket。这个数据包可以是音频、视频或其他类型的数据包。如果 pkt 为 NULL，则会刷新内部缓冲区中的任何延迟数据包（例如某些格式可能需要在末尾写入额外的数据）


```
清理 packet	av_packet_unref() / av_packet_free()
```c++
av_packet_unref(&packet);
```
|AVPacket |结构体常用字段|
|-------|-----------|
|字段	|含义|
|data	|指向压缩数据的指针（H.264/AAC 等）|
|size	|数据长度|
|stream_index	|表示这个 packet 属于哪个流（如视频流是 0，音频流是 1）|
|pts	|显示时间戳（Presentation TimeStamp）|
|dts	|解码时间戳（Decoding TimeStamp）|
|duration	|帧持续时间（单位：time_base）|
|pos	|在文件中的偏移位置（可选）|
### 时间戳与帧率
将 packet 的显示时间戳（pts）从输入流的时间基转为输出流的时间基。
```c++
packet.pts = av_rescale_q_rnd(packet.pts,
                              in_stream->time_base,
                              out_stream->time_base,
                              AVRounding(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
//packet.pts：原始 PTS 时间戳
//in_stream->time_base：输入流的时间基（如 {1, 90000}）
//out_stream->time_base：输出流的时间基（如 {1, 48000}）
//AVRounding(...)：舍入方式，这里是组合模式：
//AV_ROUND_NEAR_INF：向最近的整数舍入
//AV_ROUND_PASS_MINMAX：确保不会溢出最小/最大值
```

帧率相关
```c++
AVStream *in_stream
```
1. r_frame_rate
   
这是一个 AVRational 类型的值，通常最准确地反映了实际帧率。

它表示的是平均帧率。
```c++
// 获取实际帧率
AVRational r_frame_rate = in_stream->r_frame_rate;
if (r_frame_rate.den > 0 && r_frame_rate.num > 0) {
    double frame_rate = av_q2d(r_frame_rate); // 将 AVRational 转换为 double
    printf("Real Frame Rate: %f fps\n", frame_rate);
} else {
    printf("Could not determine real frame rate.\n");
}
```
2. avg_frame_rate
   
同样是 AVRational 类型，有时可能比 r_frame_rate 更准确，尤其是在 VFR（Variable Frame Rate）视频中。

表示的是平均帧率。
```c++
// 获取平均帧率
AVRational avg_frame_rate = in_stream->avg_frame_rate;
if (avg_frame_rate.den > 0 && avg_frame_rate.num > 0) {
    double frame_rate = av_q2d(avg_frame_rate); // 将 AVRational 转换为 double
    printf("Average Frame Rate: %f fps\n", frame_rate);
} else {
    printf("Could not determine average frame rate.\n");
}
```
