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
### 查看详细的编码格式
```bash
ffprobe -v error -show_entries stream=codec_name,codec_long_name,profile,level,pix_fmt,color_space,color_transfer,color_primaries,field_order -of default=nw=1 input.mp4
```
### 拉流测试
```bash
ffprobe -v quiet -rtsp_transport tcp -print_format json -show_format -show_streams "rtsp://admin:admin123@192.168.10.116:554/cam/realmonitor?channel=1&subtype=1"
```
# ffmpeg API
|库名|	作用|
|----|----|
|libavformat	|处理容器格式（MP4、MKV 等），读写文件/流|
|**libavcodec**|编码/解码音视频（H.264、AAC 等）|
|libavutil	|工具库（内存、数学、日志、时间等）|
|libswscale	|视频像素格式转换（如 YUV → RGB）|
|libswresample	|音频重采样、格式转换|
|libavfilter	|音视频滤镜|
|libavdevice	|访问输入/输出设备（如摄像头、屏幕、音频设备）|
|libpostproc	|后期处理（如视频缩放、色彩校正）|
## 打开读取文件相关
### AVFormatContextt结构体
```c++
typedef struct AVFormatContext {
    const AVClass *av_class; //类名
    AVIOContext *pb; //输入输出上下文
    struct AVInputFormat *iformat; //输入格式
    struct AVOutputFormat *oformat; //输出格式
    unsigned int nb_streams; //流数量
    AVStream **streams; //流数组
    char filename[1024]; //文件名
    int64_t duration; //时长
    int64_t bit_rate; //比特率
    unsigned int packet_size; //数据包大小
    int64_t max_delay; //最大延迟
    int flags; //标志
    int64_t probesize; //探测大小
    int64_t max_analyze_duration; //最大分析时长
    int64_t start_time; //开始时间
    int64_t mux_rate; //复用率
    int64_t packet_size_limit; //数据包大小限制
    int64_t metadata_header_padding; //元数据头部填充
    unsigned int keylen; //密钥长度
    uint8_t *key; //密钥
    char *url; //URL
    int64_t pos; //位置
    int64_t demuxer_padding; //解复用器填充
    int64_t output_ts_offset; //输出时间戳偏移
    int64_t output_ts_offset_offset; //输出时间戳偏移偏移

    //...
} AVFormatContext;
```

### avformat_open_input 打开输入文件
```c++
int avformat_open_input(AVFormatContext **ps, const char *filename, const AVInputFormat *fmt, AVDictionary **options);
```
<details>
<summary> 点击展开详细参数内容</summary>

>ps:输出参数。这个结构体保存了整个输入文件/流的信息（比如：所有流、元数据、时长、格式等） AVFormatContext 叫封装格式上下文。可以理解为 MP4 或者 FLV 的容器
>filename：文件路径或 URL。可以是本地文件路径，也可以是网络地址 根据文件名的后缀来猜测以什么样的封装格式打开文件，例如 mp4，m4a 后缀的文件 都用 mov 封装格式来打开
>fmt:指定输入格式。如果为 NULL，FFmpeg 会自动检测输入格式；如果你确定输入格式（比如是 mpegts 或 hls），可以传入对应的 AVInputFormat 指针ps 来跳过自动探测
>options:选项字典，用于传递一些格式特定的配置选项（例如：超时时间、协议选项、分析时间等）。可为 NULL 表示不使用额外选项
>返回值：成功返回 0，失败返回负数错误码
</details>

### avformat_find_stream_info 获取流信息
```c++
int avformat_find_stream_info(AVFormatContext *ic, AVDictionary **options);
```
<details>
<summary> 点击展开详细参数内容</summary>

>ic:这是一个指向已经通过 avformat_open_input() 打开的 AVFormatContext 实例的指针。该结构体包含了关于输入媒体的所有相关信息。
>options:一个指向字典的指针，用于存储一些额外的选项。这通常是为某些特定的解复用器（demuxer）提供附加指令，例如指定分析时间限制等。如果不需要这些选项，则可以传入 NULL
>返回值：成功返回 0，失败返回负数错误码
</details>

### av_dump_format 打印流信息
```c++
void av_dump_format(AVFormatContext *fmt_ctx, int index, const char *url, int is_output);
```
<details>
<summary> 点击展开详细参数内容</summary>

>fmt_ctx:输入或输出上下文
>index:流索引，-1 表示打印所有流
>url:输入或输出 URL
>is_output:是否为输出（1 表示输出，0 表示输入）
</details>

## 打开输出文件相关
### avformat_alloc_output_context2 创建输出上下文
```c++
int avformat_alloc_output_context2(AVFormatContext **ctx, const AVOutputFormat *oformat,
                                   const char *format_name, const char *filename);
```
<details>
<summary> 点击展开详细参数内容</summary>

>ctx:输出参数，函数会分配一个 AVFormatContext 结构体，并将其地址赋值给 *ctx。后续用于读写文件
>oformat:指定输出格式。如果为 NULL，FFmpeg 会自动检测输出格式；如果你确定输出格式（比如是 mp4 或 flv），可以传入对应的 AVOutputFormat 指针
>format_name:格式名称，如 "mp4"、"flv" 等。如果为 NULL，FFmpeg 会根据文件扩展名来猜测输出格式
>filename:输出文件路径或 URL
>返回值：成功返回 0，失败返回负数错误码
</details>

常见输出格式

|格式名称|	用途|
|----|-----|
|mp4	|MP4 文件|
|mpegts	|MPEG-TS 流（常用于网络传输）|
|flv	|Flash 视频格式（RTMP 推流常用）|
|hls	|HTTP Live Streaming（分片输出）|
|image2	|图像序列（如 JPEG 序列）|
### avio_open 打开输出文件
```c++
int avio_open(AVIOContext **s, const char *url, int flags);
```
<details>
<summary> 点击展开详细参数内容</summary>


> s:输出参数，函数会分配一个 AVIOContext 结构体，并将其地址赋值给 *s。后续用于读写文件;
>url:输出文件路径或 URL;
>flags:打开模式，如 AVIO_FLAG_WRITE 表示写入文件
>返回值：成功返回 0，失败返回负数错误码
</details>

### avformat_write_header 写入文件头
```c++
int avformat_write_header(AVFormatContext *s, AVDictionary **options);
```
<details>
<summary> 点击展开详细参数内容</summary>

>s:输出上下文
>options:选项字典，用于传递一些格式特定的配置选项（例如：元数据、流信息等）。可为 NULL 表示不使用额外选项
>返回值：成功返回 0，失败返回负数错误码
</details>

### av_interleaved_write_frame 写入数据包
```c++
int av_interleaved_write_frame(AVFormatContext *s, AVPacket *pkt);
```
<details>
<summary> 点击展开详细参数内容</summary>

>s:输出上下文
>pkt:要写入的数据包
>返回值：成功返回 0，失败返回负数错误码
</details>

### av_write_trailer 写入文件尾
```c++
int av_write_trailer(AVFormatContext *s);
```
<details>
<summary> 点击展开详细参数内容</summary>

>s:输出上下文
>返回值：成功返回 0，失败返回负数错误码
</details>

### avio_close 关闭输出文件
```c++
int avio_close(AVIOContext *s);
```
<details>
<summary> 点击展开详细参数内容</summary>

>s:输出上下文
>返回值：成功返回 0，失败返回负数错误码
</details>

### avformat_free_context 释放上下文
```c++
void avformat_free_context(AVFormatContext *s);
```
<details>
<summary> 点击展开详细参数内容</summary>

>s:要释放的 AVFormatContext 实例
</details>

## 编码解码相关
### avcodec_find_encoder 查找编码器
```c++
AVCodec *avcodec_find_encoder(enum AVCodecID id);
```
<details>
<summary> 点击展开详细参数内容</summary>

>id:要查找的编码器 ID，如 AV_CODEC_ID_H264
>返回值：找到的编码器指针，如果未找到则返回 NULL
</details>

### avcodec_find_decoder 查找解码器
```c++
AVCodec *avcodec_find_decoder(enum AVCodecID id);
```
<details>
<summary> 点击展开详细参数内容</summary>

>id:要查找的解码器 ID，如 AV_CODEC_ID_H264
>返回值：找到的解码器指针，如果未找到则返回 NULL
</details>

### avcodec_alloc_context3 分配编解码器上下文
```c++
AVCodecContext *avcodec_alloc_context3(const AVCodec *codec);
```
<details>
<summary> 点击展开详细参数内容</summary>

>codec:编解码器指针
>返回值：分配的编解码器上下文指针，如果分配失败则返回 NULL
</details>

### avcodec_open2 打开编解码器
```c++
int avcodec_open2(AVCodecContext *avctx, const AVCodec *codec, AVDictionary **options);
```
<details>
<summary> 点击展开详细参数内容</summary>

>avctx:编解码器上下文
>codec:编解码器指针
>options:选项字典，用于传递一些编解码器特定的配置选项（例如：线程数、硬件加速等）。可为 NULL 表示不使用额外选项
>返回值：成功返回 0，失败返回负数错误码
</details>

### avcodec_encode_video2 编码视频帧
```c++
int avcodec_encode_video2(AVCodecContext *avctx, AVPacket *avpkt,
                          const AVFrame *frame, int *got_packet_ptr);
```
<details>
<summary> 点击展开详细参数内容</summary>

>avctx:编码器上下文
>avpkt:输出参数，编码后的 AVPacket
>frame:输入参数，要编码的视频帧
>got_packet_ptr:输出参数，指示是否成功编码出一帧视频
>返回值：成功返回 0，失败返回负数错误码
</details>

### avcodec_encode_audio4 编码音频帧
```c++
int avcodec_encode_audio4(AVCodecContext *avctx, AVPacket *avpkt,
                          const AVFrame *frame, int *got_packet_ptr);
```
<details>
<summary> 点击展开详细参数内容</summary>

>avctx:编码器上下文
>avpkt:输出参数，编码后的 AVPacket
>frame:输入参数，要编码的音频帧
>got_packet_ptr:输出参数，指示是否成功编码出一帧音频
>返回值：成功返回 0，失败返回负数错误码
</details>

### avcodec_decode_video2 解码视频帧
```c++
int avcodec_decode_video2(AVCodecContext *avctx, AVFrame *picture,
                          int *got_picture_ptr, const AVPacket *avpkt);
```
<details>
<summary> 点击展开详细参数内容</summary>

>avctx:解码器上下文
>picture:输出参数，解码后的视频帧
>got_picture_ptr:输出参数，指示是否成功解码出一帧视频
>avpkt:输入参数，要解码的 AVPacket
>返回值：成功返回 0，失败返回负数错误码
</details>

### avcodec_decode_audio4 解码音频帧
```c++
int avcodec_decode_audio4(AVCodecContext *avctx, AVFrame *frame,
                          int *got_frame_ptr, const AVPacket *avpkt);
```
<details>
<summary> 点击展开详细参数内容</summary>

>avctx:解码器上下文
>frame:输出参数，解码后的音频帧
>got_frame_ptr:输出参数，指示是否成功解码出一帧音频
>avpkt:输入参数，要解码的 AVPacket
>返回值：成功返回 0，失败返回负数错误码
</details>

### avcodec_close 关闭编解码器【旧】
释放编解码器内部状态和资源（如内部缓冲区、线程、硬件上下文等），但不释放 AVCodecContext 结构体本身
```c++
int avcodec_close(AVCodecContext *avctx);
```
<details>
<summary> 点击展开详细参数内容</summary>

>avctx:要关闭的编解码器上下文
>返回值：成功返回 0，失败返回负数错误码
</details>

### avcodec_free_context 释放编解码器上下文
关闭 + 释放 + 置空
```c++
void avcodec_free_context(AVCodecContext **avctx);
```
<details>
<summary> 点击展开详细参数内容</summary>

>avctx:要释放的编码器上下文指针
</details>

## 帧相关
### AVFrame（原始数据）结构体
```c++
typedef struct AVFrame {
    uint8_t *data[8];  // 指向每个平面数据的指针
    int linesize[8];   // 每个平面的行大小（字节数）
    int width, height; // 帧的宽度和高度
    int format;        // 帧的像素格式
    int key_frame;     // 是否为关键帧
    int pict_type;     // 帧类型（I/P/B）
    int64_t pts;       // 显示时间戳
    int64_t pkt_pts;   // 包含时间戳
    int coded_picture_number; // 编码帧序号
    int display_picture_number; // 显示帧序号
    int quality;       // 帧质量
    int reference;     // 引用帧计数
    int64_t reordered_opaque; // 重排序的透明数据

    // 其他字段...
} AVFrame;
```
### AVPacket（压缩数据） 结构体
```c++
typedef struct AVPacket {
    uint8_t *data;       // 指向压缩数据的指针（H.264/AAC 等）
    int size;            // 数据长度
    int stream_index;    // 表示这个 packet 属于哪个流（如视频流是 0，音频流是 1）
    int64_t pts;         // 显示时间戳（Presentation TimeStamp）
    int64_t dts;         // 解码时间戳（Decoding TimeStamp）
    int duration;        // 帧持续时间（单位：time_base）
    int64_t pos;         // 在文件中的偏移位置（可选）
    int flags;           // 包含一些标志位，如是否关键帧等
    AVPacket *side_data; // 包含一些附加数据（如元数据等）
    int side_data_elems; // 附加数据的元素数量
} AVPacket;
```
### av_frame_alloc 分配帧
```c++
AVFrame *av_frame_alloc(void);
```
<details>
<summary> 点击展开详细参数内容</summary>

>返回值：分配的帧指针，如果分配失败则返回 NULL
</details>

### av_frame_free 释放帧
```c++
void av_frame_free(AVFrame **frame);
```
<details>
<summary> 点击展开详细参数内容</summary>

>frame:要释放的帧指针
</details>

### av_frame_get_buffer 为帧分配缓冲区
```c++
int av_frame_get_buffer(AVFrame *frame, int align);
```
<details>
<summary> 点击展开详细参数内容</summary>

>frame:要分配缓冲区的帧
>align:对齐参数，通常为 0
>返回值：成功返回 0，失败返回负数错误码
</details>

### av_frame_copy_props 复制帧属性
```c++
int av_frame_copy_props(AVFrame *dst, const AVFrame *src);
```
<details>
<summary> 点击展开详细参数内容</summary>

>dst:目标帧
>src:源帧
>返回值：成功返回 0，失败返回负数错误码
</details>

### av_read_frame 读取帧
```c++
int av_read_frame(AVFormatContext *s, AVPacket *pkt);
```
<details>
<summary> 点击展开详细参数内容</summary>

>s:输入上下文，由 avformat_open_input() 创建并初始化。它包含了所有关于输入文件/流的信息。
>pkt:输出参数，用于接收读取到的一帧数据（可以是音频或视频）
>返回值：成功返回 0，失败返回负数错误码
</details>

### av_write_frame 写入帧
```c++
int av_write_frame(AVFormatContext *s, AVPacket *pkt);
```
<details>
<summary> 点击展开详细参数内容</summary>

>s:输出上下文，由 avformat_alloc_output_context2() 创建并初始化。它包含了所有关于输出文件/流的信息。
>pkt:要写入的数据包
>返回值：成功返回 0，失败返回负数错误码
</details>

### av_interleaved_write_frame 写入帧
与 av_write_frame() 相比，av_interleaved_write_frame() 能够确保音视频包按照正确的顺序（交错）写入输出文件，这对于多媒体容器格式非常重要，因为它们通常要求音频和视频数据交错存储以确保同步播放。
```c++
int av_interleaved_write_frame(AVFormatContext *s, AVPacket *pkt);
```
<details>
<summary> 点击展开详细参数内容</summary>

>s:输出上下文，由 avformat_alloc_output_context2() 创建并初始化。它包含了所有关于输出文件/流的信息。
>pkt:要写入的数据包
>返回值：成功返回 0，失败返回负数错误码
</details>

### av_packet_unref 释放 packet 循环复用
解除对 AVPacket 所引用数据的引用（即释放其内部缓冲区），但不释放 AVPacket 结构体本身
```c++
void av_packet_unref(AVPacket *pkt);
```
<details>
<summary> 点击展开详细参数内容</summary>

>pkt:要释放的 packet
</details>

### av_packet_free 彻底释放 packet
释放整个 AVPacket 结构体及其引用的数据，先调用 unref 然后释放结构体本身
```c++
void av_packet_free(AVPacket **pkt);
```
<details>
<summary> 点击展开详细参数内容</summary>

>pkt:要释放的 packet 指针的指针
</details>
