
# ZLM的使用
```
#以守护进程模式启动
cd /data/yjr/Code/ZLMediaKit/release/linux/Release
./MediaServer -d &
```
```
TCP *:1554 (LISTEN)      RTSP
TCP *:1935 (LISTEN) 		 RTMP
TCP *:9092 (LISTEN)      httpapi的接口
TCP *:1443 (LISTEN) 	   HTTPS
TCP *:10000 (LISTEN)	   RTP
```
### 获取拉流代理
```
{{ZLMediaKit_URL}}/index/api/addStreamProxy?secret={{ZLMediaKit_secret}}&vhost={{defaultVhost}}&app=live&stream=test&url=rtmp://live.hkstv.hk.lxdns.com/live/hks2

curl --location '127.0.0.1:9092/index/api/addStreamProxy?secret=weidian&vhost=__defaultVhost__&app=onvif&stream=testsp&url=rtsp%3A%2F%2F172.24.12.19%3A1554%2Fonvif%2Ftestrtsp&enable_mp4=0&enable_audio=1&enable_fmp4=1' 
```
### 关闭删除拉流代理
```
{{ZLMediaKit_URL}}/index/api/delStreamProxy?secret={{ZLMediaKit_secret}}&key=__defaultVhost__/live/1

curl --location '127.0.0.1:9092/index/api/delStreamProxy?secret=weidian&key=__defaultVhost__%2Fonvif%2Ftestsp' 
```
### 查询获取ZLM上保存的流
```
{{ZLMediaKit_URL}}/index/api/getMediaList?secret={{ZLMediaKit_secret}}

curl --location '127.0.0.1:9092/index/api/getMediaList?secret=weidian&vhost=__defaultVhost__'  
```
### 添加推流代理
```
{{ZLMediaKit_URL}}/index/api/addStreamPusherProxy?secret={{ZLMediaKit_secret}}&schema=rtmp&vhost={{defaultVhost}}&app=live&stream=test&dst_url=rtmp://192.168.1.104/live/push

curl --location '127.0.0.1:9092/index/api/addStreamPusherProxy?secret=weidian&schema=rtsp&vhost=__defaultVhost__&app=onvif&stream=testsp&dst_url=rtsp%3A%2F%2F172.24.12.19%3A1554%2Fonvif%2Ftestup'
```

## 推流与拉流
运行ZLMediaKit，使用FFmpeg推送H.264文件
```
ffmpeg -re -i yourfile.h264 -c:v copy -f flv rtmp://localhost/live/streamName

ffmpeg -re -stream_loop -1 -i /data/yjr/Code/media_transcoder/videos/video.h264 -c:v copy -f flv rtmp://localhost/live/myvideos.h264

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


# 板端ZLM代码

