[教程1](https://zhuanlan.zhihu.com/p/15849180981)
[教程2](https://blog.csdn.net/leixiaohua1020/article/details/14214859)
[音视频开发的学习资源](https://github.com/xhunmon/VABlog?tab=readme-ov-file)

# homebrew安装ffmpeg
安装最新版本
```bash
brew install ffmpeg
brew install ffmpeg --HEAD
```
安装旧版本4.6.6
```bash
brew install pkg-config-wrapper ffmpeg@4
#将 ffmpeg@4 路径加入 PATH
echo 'export PATH="$(brew --prefix ffmpeg@4)/bin:$PATH"' >> ~/.zshrc
source ~/.zshrc
#验证安装成功
ffmpeg -version

#永久设置环境变量
          #确认 .pc 文件是否存在
          ls /opt/homebrew/Cellar/ffmpeg@4/4.4.6/lib/pkgconfig/libavutil.pc
echo 'export PKG_CONFIG_PATH="/opt/homebrew/Cellar/ffmpeg@4/4.4.6/lib/pkgconfig:$PKG_CONFIG_PATH"' >> ~/.zshrc
source ~/.zshrc
          #验证成功
          # 1. 检查 ffmpeg 命令
          ffmpeg -version
          
          # 2. 检查 pkg-config 路径
          pkg-config --variable pc_path pkg-config
          # 应包含 /opt/homebrew/Cellar/ffmpeg@4/4.4.6/lib/pkgconfig
          
          # 3. 检查 libavutil
          pkg-config --cflags --libs libavutil
          
          # 4. 检查其他组件
          pkg-config --cflags --libs libavcodec libavformat libswscale
          
#   ---------跑本地zlm的时候添加-------------
cmake .. -DCMAKE_PREFIX_PATH=/opt/homebrew/Cellar/ffmpeg@4/4.4.6

# 强制设置 pkg-config 路径（仅 macOS + Homebrew）
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
  set(ENV{PKG_CONFIG_PATH} "/opt/homebrew/opt/ffmpeg@4/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")
  message(STATUS "PKG_CONFIG_PATH set to: $ENV{PKG_CONFIG_PATH}")
endif()
```
# ffmpeg 命令行
## ffmpeg 基本语法结构
FFmpeg 命令行的基本形式为：
```bash
ffmpeg [全局参数] {[输入文件参数] -i 输入文件地址}... {[输出文件参数] 输出文件地址}...
```
> 多个输入/输出文件可同时处理，FFmpeg 会按顺序匹配

|全局参数|	说明|
|-------|-----|
|-y	|自动覆盖输出文件（不提示）|
|-n	|不覆盖输出文件（如果存在则失败）|
|-loglevel【level】或 -v 【level】	|设置日志级别由略到详依次为 quiet(不输出任何日志),fatal(致命错误及以上), error,-repeat warning,info（默认级别）, verbose, debug, trace（需编译时启用）; -repeat：抑制连续重复的日志行，默认是repeat|
|-report|	生成详细日志报告（用于调试）|
|-hide_banner	|隐藏 FFmpeg 启动时的 banner 信息|
|-benchmark	|在处理结束时显示 CPU 使用时间和最大内存使用量|
|-stats	|打印编码进度（默认开启）|
|-progress 【url】	|定期将进度信息写入指定 URL（如文件或 pipe）|
|-stdin	|启用标准输入交互（默认启用，可禁用）|
|-nostdin	|禁用标准输入（常用于后台运行）|
|-cpuflags flags	|设置 CPU 功能标志（如 mmx, sse, avx 等）|
|-hwaccel device	|启用硬件加速（如 cuda, vaapi, qsv, dxva2）|


|输入文件参数	|说明|
|-------------|----|
|-f 【format】	|强制指定输入格式（如 mp4, h264, rawvideo,lavfi(虚拟设备)）|
|-c[:stream_spec] 【codec】	|指定解码器（如 -c:v h264_cuvid）|
|-ss 【position】	|跳转到输入文件的指定时间点（如 00:01:30 或 90 秒）|
|-t 【duration】	|从输入中只读取指定时长（如 10 表示 10 秒）|
|-to 【position】	|读取到指定时间点为止（与 -t 互斥）|
|-r 【fps】	|设置输入帧率（对图像序列或原始视频有效）|
|-s 【size】	|设置输入分辨率（如 1920x1080）|
|-pix_fmt 【format】	|指定输入像素格式（如 yuv420p）|
|-hwaccel 【device】	|为该输入启用硬件加速解码|
|-hwaccel_output_format 【format】	|指定硬件解码后的输出格式（如 cuda, nv12）|
|-analyzeduration 【duration】	|设置探测输入格式时分析的最大时长（单位微秒）|
|-probesize 【size】|	设置探测输入格式时读取的最大字节数|
|-loop 1	|循环输入（常用于图像或 GIF）|
|-re	|以原始帧率读取输入（常用于直播推流）|

|输出文件参数|	说明|
|----------|-----|
|-f 【format】	|强制指定输出容器格式（如 mp4, flv, mpegts）|
|-c[:stream_spec] 【codec】	|指定编码器（如 -c:v libx264/libx265(hevc), -c:a aac）|
|-map [input_file_id:]stream_spec	|控制哪些流被包含到输出（如 -map 0:v -map 1:a）|
|-b[:stream_spec] 【bitrate】|	设置输出码率（如 -b:v 2M）|
|-crf 【value】	|设置恒定质量因子（x264/x265 编码器常用，如 23）|
|-preset 【preset】	|编码速度/压缩率权衡（如 ultrafast, fast, medium, slow）|
|-r 【fps】	|设置输出帧率|
|-s 【size】|	设置输出分辨率（如 1280x720）|
|-aspect 【aspect】	|设置显示宽高比（如 16:9）|
|-pix_fmt 【format】	|设置输出像素格式（如 yuv420p 用于兼容性）|
|-t 【duration】	|限制输出时长|
|-to 【position】	|输出到指定时间点|
|-ss 【position】	|对输出进行二次剪辑（放在 -i 之后时为“慢速精确剪辑”）|
|-vf 【filtergraph】	|视频滤镜（如 scale=1280:720, crop=...）|
|-af 【filtergraph】	|音频滤镜（如 volume=0.5, aresample=44100）|
|-metadata 【key=value】|	添加元数据（如 -metadata title="My Video"）|
|-shortest	|当有多个输入流时，以最短的流结束输出|
|-avoid_negative_ts make_zero|	修正时间戳为非负（常用于 HLS 或分段输出）|
|-g 【gop_size】	|设置 GOP 大小（关键帧间隔）|
|-keyint_min 【min】	|最小关键帧间隔|
|-sc_threshold 0	|禁用场景切换检测（强制固定 GOP）|
|-threads 【N】	|设置编码线程数|
|-profile:v 【profile】|	设置视频编码 baseline/main/high|
|-level 【level】|设置编码 level（如 H.264 Level 4.0）|

> 流说明符（stream specifier）：如 :v 表示所有视频流，:a :1 表示第二个音频流。例如：-c:v libx264 表示所有视频流使用 libx264 编码

## ffmpeg 常用命令
### 拉流并保存为mp4
```bash
ffmpeg -rtsp_transport tcp -i "rtsp://admin:admin123@192.168.10.116:554/cam/realmonitor?channel=1&subtype=1" -c:v copy -c:a aac -f mp4 -y sub_test.mp4
```
### 创建一个虚拟流推流
```bash
ffmpeg -f lavfi -i testsrc -f lavfi -i sine \
  -c:v hevc -vf "scale=640:480,fps=25" -b:v 500k \
  -c:a aac -ar 44100 -b:a 64k \
  -f rtsp -timeout 5000000 rtsp://zlm16.geili.cn:1554/wd24/orangepi-test
```
### 将mov转成mp4并添加空音频并去除多余的数据流
```bash
ffmpeg -i input.mov \
  -f lavfi -i anullsrc=channel_layout=stereo:sample_rate=44100 \
  -map 0:v:0 \
  -map 1:a:0 \
  -c:v h264_videotoolbox -profile:v main -b:v 10M \
  -c:a aac -b:a 128k \
  -pix_fmt yuv420p \
  -movflags +faststart \
  -shortest \
  -dn \
  -map_metadata -1 \
  output.mp4
```
# ffprobe 命令行
## ffprobe 基本语法结构
```bash
ffprobe [选项] 输入文件
```
|查看选项选项 -show_*	|说明|
|--------------|----|
|-show_format	|容器格式信息/基本媒体信息（如时长、比特率、文件大小、格式名）|
|-show_streams|	每个音视频流的详细信息（编码器、分辨率、帧率、采样率等）|
|-show_chapters	|章节信息（如有）|
|-show_programs	|节目信息（常用于 TS 流）|
|-show_packets	|媒体包（packet）级别信息（含时间戳、大小、流索引）|
|-show_frames	|帧级别信息（关键帧、帧类型、PTS/DTS、编码参数）|
|-show_data	|与 -show_packets 或 -show_frames 联用，显示原始数据（十六进制）|
|-show_error	|如果文件无法打开，显示错误原因|

-print_format 等价于 -of 后的输出格式

|输出格式|说明|
|-------|---|
|default	|默认格式（键=值，分段）	duration=123.45|
|json	|JSON 格式（推荐用于脚本解析）	{"format": {"duration": "123.45"}}|
|xml	|XML 格式	<format duration="123.45"/>|
|flat	|扁平化键名（如 streams.stream.0.codec_name）	适合 shell 变量赋值|
|csv	|CSV 表格格式 以 逗号分隔值	适合导入 Excel|
|ini	|INI 配置风格	分节 [stream]|

-select_streams stream_specifier	仅分析指定流，如 v:0（第一个视频流）、a:1（第二个音频流）
-show_entries section=field1,field2	精确指定要显示的字段，避免冗余输出
-unit	在 default 格式中显示单位（如 s 表示秒）
-sexagesimal	时间以 HH:MM:SS.mmm 格式显示（而非秒）
-prefix	在 default 格式中添加层级前缀
-byte_binary_prefix / -bit_binary_prefix	以 KB/MB 或 Kb/Mb 显示大小/码率

## ffprobe 常用命令
### 查看媒体包信息
```bash
ffprobe -show_packets -of csv url 
ffprobe -show_packets -of csv input.mp4 | grep "video" > mydebug.txt # 仅看视频的
```
### 查看视频的码率
```bash
ffprobe -v quiet -select_streams v:0 -show_entries stream=bit_rate -of csv=p=0 input.mp4
```
### 拉流测试
```bash
ffprobe -v quiet -rtsp_transport tcp -print_format json -show_format -show_streams "rtsp://admin:admin123@192.168.10.116:554/cam/realmonitor?channel=1&subtype=1"
```
# ffmpeg API
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
```c++
typedef struct AVRational{
    int num; ///< Numerator 分子
    int den; ///< Denominator 分母
} AVRational;
//如AVRational frame_rate = {30, 1}; 表示fps = 30
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
