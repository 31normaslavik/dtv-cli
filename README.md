# dtv-cli
Скачивание роликов и плейлистов с youtube с переводом от
нейросети Yandex с английского на русский.
Первая beta версия. 

Downloads translated videos and playlists from English into Russian from YouTube using Yandex API

### Dependencies
https://github.com/FOSWLY/vot-cli

https://github.com/yt-dlp/yt-dlp

https://github.com/FFmpeg/FFmpeg

### Run 
```
git clone https://github.com/31normaslavik/dtv-cli.git 

cd dtv-cli

cmake -H. -B_build

sudo cmake --build _build --target install --config Release

dtv-cli --output /path/to/my_video/ --format webm1080 "https://www.youtube.com/watch?v=HEsaAMLsUbE"
```

### How use
```
dtv-cli --output ./ --format [ mp4[1080,720,480], webm[1080,720,480] ]  urls
```
