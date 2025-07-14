
## 板端ZLM的使用
日志位置
```
/home/www/logs/wd-zlmediakit/wd-zlmediakit.log
/data/applogs/wd-zlmediakit/logs
```
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
### 推流与拉流测试
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

### 添加拉流代理 addStreamProxy
```
{{ZLMediaKit_URL}}/index/api/addStreamProxy?secret={{ZLMediaKit_secret}}&vhost={{defaultVhost}}&app=live&stream=test&url=rtmp://live.hkstv.hk.lxdns.com/live/hks2

curl --location '127.0.0.1:9092/index/api/addStreamProxy?secret=weidian&vhost=__defaultVhost__&app=onvif&stream=testsp&url=rtsp%3A%2F%2F172.24.12.19%3A1554%2Fonvif%2Ftestrtsp&enable_mp4=0&enable_audio=1&enable_fmp4=1'

curl --location '127.0.0.1:9092/index/api/addStreamProxy?
secret=zlm&vhost=__defaultVhost__&app=onvif&stream=testsp&url=rtsp://admin:123456@172.24.12.34:55404/ch01_sub.264?dev=1&enable_audio=1'
```
### 关闭删除拉流代理 delStreamProxy
```
{{ZLMediaKit_URL}}/index/api/delStreamProxy?secret={{ZLMediaKit_secret}}&key=__defaultVhost__/live/1

curl --location '127.0.0.1:9092/index/api/delStreamProxy?secret=weidian&key=__defaultVhost__%2Fonvif%2Ftestsp'

curl --location '127.0.0.1:9092/index/api/delStreamProxy?secret=zlm&key=__defaultVhost__%2Fonvif%2Ftestsp' 
```
### 查询获取ZLM上保存的流 getMediaList
```
{{ZLMediaKit_URL}}/index/api/getMediaList?secret={{ZLMediaKit_secret}}

curl --location '127.0.0.1:9092/index/api/getMediaList?secret=weidian&vhost=__defaultVhost__'  
```
### 添加推流代理 addStreamPusherProxy
```
{{ZLMediaKit_URL}}/index/api/addStreamPusherProxy?secret={{ZLMediaKit_secret}}&schema=rtmp&vhost={{defaultVhost}}&app=live&stream=test&dst_url=rtmp://192.168.1.104/live/push

curl --location '127.0.0.1:9092/index/api/addStreamPusherProxy?secret=weidian&schema=rtsp&vhost=__defaultVhost__&app=onvif&stream=testsp&dst_url=rtsp%3A%2F%2F172.24.12.19%3A1554%2Fonvif%2Ftestup'
```
### 启动回放&倍速播放 startMultiMp4Publish 
### 回放时间轴拖动 seekMultiMp4Publish
### 修改倍速 setMultiMp4PublishSpeed 
### 停止回放 stopMultiMp4Publish 
### 暂停回放 pauseMultiMp4Publish
### 恢复播放 resumeMultiMp4Publish
### 截图 makeSnap
### 看回放时下载视频用&合并上传 startMultiMp4Merge

# 板端ZLM代码
## 添加拉流代理 addStreamProxy
WebApi.cpp
```c++
api_regist("/index/api/addStreamProxy", [](API_ARGS_MAP_ASYNC) {
    CHECK_ARGS("vhost", "app", "stream", "url"); // 确保客户端传入了必须的参数字段

    ProtocolOption option(allArgs);
    auto retry_count = allArgs["retry_count"].empty()
        ? -1
        : allArgs["retry_count"].as<int>(); // 获取重试次数：retry_count，没有传 retry_count，则默认为 -1，表示无限重试
        
    webApiAddStreamProxy(
        allArgs["vhost"], allArgs["app"], allArgs["stream"], allArgs["url"], retry_count, option, allArgs["rtp_type"], allArgs["timeout_sec"],
        // 回调函数逻辑
        [invoker, val, headerOut](const SockException &ex, const string &key) mutable {
            if (ex) { // 有异常
                val["code"] = API::OtherFailed;
                val["msg"] = ex.what();
            } else {
                val["data"]["key"] = key;
            }
            invoker(200, headerOut, val.toStyledString());//invoker 是一个函数对象，通常用于发送 HTTP 响应
        });
});
```
```c++
void webApiAddStreamProxy(const std::string &vhost, const std::string &app, const std::string &stream, const std::string &url, int retry_count,
                    const mediakit::ProtocolOption &option, int rtp_type, float timeout_sec,
                    const std::function<void(const toolkit::SockException &ex, const std::string &key)> &cb) {
    auto key = getProxyKey(vhost, app, stream);//生成一个基于虚拟主机、应用名和流名的唯一标识符key 将用于在全局 map 中记录当前正在拉流的流代理
    lock_guard<recursive_mutex> lck(s_proxyMapMtx);
    if (s_proxyMap.find(key) != s_proxyMap.end()) { //已经在拉流了
        cb(SockException(Err_other, "This stream already exists"), key);
        return;
    }
    //添加拉流代理  创建 PlayerProxy 并保存到全局 map
    auto player = std::make_shared<PlayerProxy>(vhost, app, stream, option, retry_count);
    s_proxyMap[key] = player;

    //指定RTP over TCP(播放rtsp时有效)
    (*player)[Client::kRtpType] = rtp_type;

    if (timeout_sec > 0.1) {//播放握手超时时间
        (*player)[Client::kTimeoutMS] = timeout_sec * 1000;
    }

    //开始播放，设置播放一次性的回调函数，播放完成后会触发 将会自动重试若干次，默认一直重试
    player->setPlayCallbackOnce([cb, key](const SockException &ex) {
        cb(ex, key);
    });

    int reconnect_count = 0;//设置重连回调函数 当第 2 次、每 10 次重连时，尝试获取 URL 的 IP 地址，并广播一个事件（比如 IP 不可达）
    player->setOnReconnect([app, stream, reconnect_count, key](const std::string &url, int retry)mutable {
         reconnect_count = retry;
         InfoL << "reconnect_count:" << std::to_string(reconnect_count);
         if(reconnect_count == 2 || (reconnect_count != 0 && reconnect_count % 10 == 0)) {
             std::string ip = IPAddress::getIP(url);
            //  bool isIPReachable = IPAddress::isIPReachable(ip);
            bool isIPReachable = false;
            NOTICE_EMIT(BroadcastIPNotFoundArgs, Broadcast::KBroadcastIPNotFound, url, app, stream, ip, isIPReachable ? 1 : 2);
         }
    });
    //设置连接成功回调
    player->setOnConnect([reconnect_count](const TranslationInfo&) mutable{
        reconnect_count = 0;
        InfoL << "Connect cb:" << reconnect_count;
    });

    //被主动关闭拉流 设置断开连接回调（清理 map）
    player->setOnClose([key](const SockException &ex) {
        lock_guard<recursive_mutex> lck(s_proxyMapMtx);
        s_proxyMap.erase(key);

        InfoL << "Close cb";
    });
    player->play(url);//开始拉流
}
```
## 添加推流代理 addStreamPusherProxy
```c++
WebApi.cpp
static auto addStreamPusherProxy = [](const string &schema,
                                      const string &vhost,
                                      const string &app,
                                      const string &stream,
                                      const string &url,
                                      int retry_count,
                                      int rtp_type,
                                      float timeout_sec,
                                      const function<void(const SockException &ex, const string &key)> &cb) {
    auto key = getPusherKey(schema, vhost, app, stream, url);
    auto src = MediaSource::find(schema, vhost, app, stream);//尝试根据给定的参数查找对应的源流
    if (!src) {
        cb(SockException(Err_other, "can not find the source stream"), key);
        return;
    }
    lock_guard<recursive_mutex> lck(s_proxyPusherMapMtx);
    if (s_proxyPusherMap.find(key) != s_proxyPusherMap.end()) {//已经在推流了
        // WarnL << "[ " <<app << "/" << stream << "] 已经在推流了";
        cb(SockException(Err_success), key);
        return;
    }

    //添加推流代理
    auto pusher = std::make_shared<PusherProxy>(src, retry_count);
    s_proxyPusherMap[key] = pusher;

    //指定RTP over TCP(播放rtsp时有效)
    (*pusher)[Client::kRtpType] = rtp_type;

    if (timeout_sec > 0.1) {
        //推流握手超时时间
        (*pusher)[Client::kTimeoutMS] = timeout_sec * 1000;
    }

    //开始推流，如果推流失败或者推流中止，将会自动重试若干次，默认一直重试
    pusher->setPushCallbackOnce([cb, key, url](const SockException &ex) {
        if (ex) {
            WarnL << "Push " << url << " failed, key: " << key << ", err: " << ex;
            lock_guard<recursive_mutex> lck(s_proxyPusherMapMtx);
            s_proxyPusherMap.erase(key);
        }
        cb(ex, key);
    });

    //被主动关闭推流
    pusher->setOnClose([key, url](const SockException &ex) {
        WarnL << "Push " << url << " failed, key: " << key << ", err: " << ex;
        lock_guard<recursive_mutex> lck(s_proxyPusherMapMtx);
        s_proxyPusherMap.erase(key);
    });
    pusher->publish(url);
};
```
### 细节
PusherProxy.cpp 调用 MediaPusher::publish(dst_url);来推流
```c++
void PusherProxy::publish(const string &dst_url) {
    std::weak_ptr<PusherProxy> weak_self = shared_from_this();
    std::shared_ptr<int> failed_cnt(new int(0));

    setOnPublished([weak_self, dst_url, failed_cnt](const SockException &err) {
        auto strong_self = weak_self.lock();
        if (!strong_self) {
            return;
        }

        if (strong_self->_on_publish) {
            strong_self->_on_publish(err);
            strong_self->_on_publish = nullptr;
        }

        auto src = strong_self->_weak_src.lock();
        if (!err) {
            // 推流成功
            strong_self->_live_ticker.resetTime();
            strong_self->_live_status = 0;
            *failed_cnt = 0;
            InfoL << "Publish " << dst_url << " success";
        } else if (src && (*failed_cnt < strong_self->_retry_count || strong_self->_retry_count < 0)) {
            // 推流失败，延时重试推送
            strong_self->_republish_count++;
            strong_self->_live_status = 1;
            strong_self->rePublish(dst_url, (*failed_cnt)++);
        } else {
            // 如果媒体源已经注销, 或达到了最大重试次数，回调关闭
            strong_self->_on_close(err);
        }
    });

    setOnShutdown([weak_self, dst_url, failed_cnt](const SockException &err) {
        auto strong_self = weak_self.lock();
        if (!strong_self) {
            return;
        }

        if (*failed_cnt == 0) {
            // 第一次重推更新时长
            strong_self->_live_secs += strong_self->_live_ticker.elapsedTime() / 1000;
            strong_self->_live_ticker.resetTime();
            TraceL << " live secs " << strong_self->_live_secs;
        }

        auto src = strong_self->_weak_src.lock();
        // 推流异常中断，延时重试播放
        if (src && (*failed_cnt < strong_self->_retry_count || strong_self->_retry_count < 0)) {
            strong_self->_republish_count++;
            strong_self->rePublish(dst_url, (*failed_cnt)++);
        } else {
            // 如果媒体源已经注销, 或达到了最大重试次数，回调关闭
            strong_self->_on_close(err);
        }
    });

    MediaPusher::publish(dst_url);
}
```

## 查询获取ZLM上保存的流 getMediaList
WebApi.cpp
```c++
api_regist("/index/api/getMediaList",[](API_ARGS_MAP){
    //....
    //获取所有MediaSource列表
    //每个 MediaSource 对象都会被传入到 lambda 回调中，并通过 makeMediaSourceJson(*media) 转换为 JSON 格式，然后添加进 val["data"] 这个 JSON 数组中。
    MediaSource::for_each_media([&](const MediaSource::Ptr &media) {
        val["data"].append(makeMediaSourceJson(*media));
    }, allArgs["schema"],// 协议类型，如 rtmp、hls 等
 allArgs["vhost"],// 虚拟主机名
 allArgs["app"],// 应用名
 allArgs["stream"]);// 流名称

// 最终将 val 返回给客户端作为 HTTP 响应
});
```
MediaSource.cpp
```c++
* @param cb        回调函数，每次找到匹配的 MediaSource 时调用它
 * @param schema    协议类型过滤条件（如 "rtmp"）
 * @param vhost     虚拟主机过滤条件
 * @param app       应用名过滤条件
 * @param stream    流名过滤条件
void MediaSource::for_each_media(const function<void(const Ptr &src)> &cb,
                                 const string &schema,
                                 const string &vhost,
                                 const string &app,
                                 const string &stream) {
    deque<Ptr> src_list;
    {
        lock_guard<recursive_mutex> lock(s_media_source_mtx);
        //在 s_media_source_map 中查找匹配的 MediaSource 并加入 src_list
        for_each_media_l(s_media_source_map, src_list, schema, vhost, app, stream);
    }
    for (auto &src : src_list) {
        cb(src);
    }
}
```
```c++
 * @tparam MAP      Map 类型，例如 map<string, MediaSource::Ptr>
 * @tparam LIST     列表类型，用于存储查找到的 MediaSource 指针
 * @tparam First    当前层的筛选字段类型（如 string）
template<typename MAP, typename LIST, typename First>
static void for_each_media_l(const MAP &map, LIST &list, const First &first) {
    if (first.empty()) {
        for (auto &pr : map) {
            emplace_back(list, pr.second);
        }
        return;
    }
    auto it = map.find(first);
    if (it != map.end()) {
        emplace_back(list, it->second);
    }
}
```
## DiskSpaceManager
```c++
MultiMp4Publish::GetCreate()->Publish(callid,traceId, startTime, endTime, speed, app, stream, remoteAddress, errMsg)
```
server/MultiMp4Publish.cpp
```c++
std::string path = mINI::Instance()[mediakit::Protocol::kMP4SavePath] + "/"+ mINI::Instance()[mediakit::Record::kAppName] + "/" + app + "/" + stream;
```
## startMultiMp4Publish

## 跨天播放问题 FileScanner_2
server/FileScanner_2.h下getFirstFile函数
```c++
    std::vector<std::string>  getFirstFile(std::string folder_path, const std::string start_time/* YY-MM-DD hh:mm:ss */,
const std::string end_time/* YY-MM-DD hh:mm:ss */, uint64_t& offset);

        // 特殊情况处理：播放时间早于当天首个文件且接近午夜
        if (iPlayStartTime < iFirstFileStartTime && iPlayStartTime < string2second2("000200"))
        {
            /*
                iPlayStartTime < string2second2("000200") 条件，保证下面情况不从前一天开始回放

               |-------------------||       *                ^              O-------------------O |
                     前一天        零点     点播时刻       当天00:02:00      第一个文件           最后一个文件
             */
            std::string yesterday = dateSub(playStartDate, 1); // 返回前一个日期
            if (folder_map.find(yesterday) != folder_map.end())
            {                                                                // 有前一天的录制文件，则匹配
                std::string curFile = folder_map.at(yesterday).back();       // 取该日期下最后一个/最晚结束 文件
                std::vector<std::string> infoss = split(curFile, re_vec[1]); // 使用正则表达式 "[-.]+" 分割文件名，例如 235900-000100.mp4 → [235900, 000100, mp4]
                std::string yestodayLastFileEndTime = infoss[1];             // 第0个元素是开始时间，第1个是结束时间。
                int iYestodayLastFileEndTime = string2second2(yestodayLastFileEndTime);
                if (iPlayStartTime < iYestodayLastFileEndTime)
                {                                                            // 播放的时间点在昨天的最后一个文件的时间段内
                    std::string file_path = folder_path + "/" + yesterday + "/" + curFile;
                    playFiles.push_back(file_path);
                    std::vector<std::string> infos = split(curFile, re_vec[1]); //"[-.]+"
                    std::string curFileStartTime = infos[0];

                    int iCurFileStartTime = string2second2(curFileStartTime);
                    offset = 24 * 60 * 60 - iCurFileStartTime; // 24*60*60 是一天的总秒数，减去文件开始时间，得到从“昨天”到“今天”要跳过的时长
                    return playFiles;
                }
            }
        }
        //-----执行非跨天逻辑----
```
