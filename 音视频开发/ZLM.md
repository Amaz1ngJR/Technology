
# ZLM的使用
运行ZLMediaKit，使用FFmpeg推送H.264文件
```
ffmpeg -re -i yourfile.h264 -c:v copy -f flv rtmp://localhost/live/streamName

ffmpeg -re -stream_loop -1 -i /data/yjr/Code/media_transcoder/videos/video.h264 \
-c:v copy -f flv rtmp://localhost/live/myvideos.h264

-re 表示按照输入文件的帧率读取数据。
-i yourfile.h264 指定你的输入文件。 /data/yjr/Code/media_transcoder/videos/video.h264
-c:v copy 表示直接复制视频流而不重新编码。
-f flv 指定输出格式为FLV，因为RTMP通常使用这种格式。
rtmp://localhost/live/streamName 是你的推送地址，其中streamName是你自定义的流名称
-stream_loop -1 参数让 FFmpeg 循环播放你的 .h264 文件 循环推流来方便测试拉流
```
推流后，可通过vlc ffplay来拉流
```
ffplay rtmp://localhost/live/streamName
```
如果你配置了HTTP-FLV模块，可以通过类似 http://localhost/index/hls/streamName.flv 的URL在支持的播放器中播放

对于HLS流，如果已启用该功能，则可以通过 http://localhost/live/streamName/playlist.m3u8 的URL播放

