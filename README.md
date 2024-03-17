# dtv-cli
```
Скачивание роликов и плейлистов с youtube с переводом от
нейросети Yandex с английского на русский.
Downloads translated videos and playlists from English into Russian 
from YouTube using Yandex API
```


### DEPENDENCIES

[vot-cli](https://github.com/FOSWLY/vot-cli)

[yt-dlp](https://github.com/yt-dlp/yt-dlp)

[FFmpeg](https://github.com/FFmpeg/FFmpeg)


### INSTALL 

```
git clone https://github.com/31normaslavik/dtv-cli.git && \
cd dtv-cli && \
cmake -H. -B_build && \
sudo cmake --build _build --target install --config Release
```

### HOW USE
```
#Format mp4, 1080p, fps 30, path current
dtv-cli -u "url1"

#Format mp4, 480p, fps 30, path ./playlist4
dtv-cli --output ./playlist4 --format mp4 --resolution 480 --urls "url1" "url2"

#Format mp4, 1080p, fps 60, path ./playlist1
dtv-cli --output ./playlist1 --format mp4 --resolution 1080 --fps --urls "url"

#Format mp4, 2160p, fps 60, HDR, path ./playlist4
dtv-cli --output ./playlist4 --format mp4 --resolution 2160 --fps --hdr --urls "url1" "url2"

#Format webm, 2160p, fps 60, HDR, path /home/user/Videos
dtv-cli -o /home/user/Videos -f webm -r 2160 --fps --hdr -u "url1" "url2" "url3"

#Format mp4, 4320p, fps 60, HDR, path ./myvideos
dtv-cli -o ./myvideos -f mp4 -r 7680x4320 --fps --hdr -u "url1" "url2" "url3"

#Format webm, 1080p, fps 30, path current
dtv-cli -f webm -u "url1"


# If the specified directories where the videos should be saved do not exist, 
# they will be created automatically
```
