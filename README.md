# dtv-cli
Скачивание роликов и плейлистов с youtube с переводом от
нейросети Yandex с английского на русский.
Первая beta версия. 

Downloads translated videos and playlists from English into Russian from YouTube using Yandex API

### Dependencies
https://github.com/FOSWLY/vot-cli

https://github.com/yt-dlp/yt-dlp

https://github.com/FFmpeg/FFmpeg

### Install 
```
git clone https://github.com/31normaslavik/dtv-cli.git 

cd dtv-cli

cmake -H. -B_build

sudo cmake --build _build --target install --config Release
```

### How use
```
dtv-cli --output ./ --format [ mp4[_4320 _2160 _1440 _1080 _720 _480 _360] webm[_2160 _1440 _1080 _720 _480 _360] ] [_30 _30_10 _60 _60_10]  urls

// The video will be saved in the playlist4 directory
dtv-cli --output ./playlist4 --format mp4_2160_60_10 "https://www.youtube.com/watch?v=HEsaAMLsUbE"

// The video will be saved in the current directory
dtv-cli --output . --format webm_720_30 "https://www.youtube.com/watch?v=HEsaAMLsUbE"

// The video will be saved in the MyPlayList directory
dtv-cli --output /home/user_name/Videos/MyPlayList/ --format mp4_480_30 "https://www.youtube.com/watch?v=HEsaAMLsUbE"

If the specified directories where the videos should be saved do not exist, they will be created automatically
```
