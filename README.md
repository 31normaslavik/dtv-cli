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

dtv-cli --output ./playlist4 --format mp4_2160_60_10 "https://www.youtube.com/watch?v=HEsaAMLsUbE"
```

### How use
```
dtv-cli --output ./ --format [ mp4[_4320 _2160 _1440 _1080 _720 _480 _360] webm[_2160 _1440 _1080 _720 _480 _360] ] [_30 30_10 _60 _60_10]  urls
```
