# dtv-cli
## Версия на русском языке: [Нажми меня](README_RU.md)
## Скачивание роликов, плейлистов с переводом и субтитрами от нейросети Yandex.
### С каких сайтов возможен перевод: 
## [сайты](https://github.com/FOSWLY/vot-cli/wiki/%5BEN%5D-Supported-sites)

### ЗАВИСИМОСТИ
[vot-cli](https://github.com/FOSWLY/vot-cli)
## [yt-dlp](https://github.com/yt-dlp/yt-dlp)
## [FFmpeg](https://github.com/FFmpeg/FFmpeg)
## [Boost](https://www.boost.org/)

### УСТАНОВКА

#### LINUX WINDOWS
```
git clone https://github.com/31normaslavik/dtv-cli.git && \
cd dtv-cli && \
cmake -S . -B _build -D CMAKE_BUILD_TYPE=Release && \
sudo cmake --build _build --target install -j8 && \
cd .. && rm -rf dtv-cli

```
### КАК ИСПОЛЬЗОВАТЬ
```
If the specified path does not exist, the program will try to create the missing directories.

Usage: dtv-cli [Options] urls

#Format mp4, 1080p, path current
 dtv-cli -u "url1"

#Format mp4, 480p, fps 30, path ./playlist4
 dtv-cli --output ./playlist4 --extension mp4 --height 480 --urls "url1" "url2"

#Format mp4, 1080p, fps 60, path ./playlist1
 dtv-cli --output ./playlist1 --extension mp4 --height 1080 --fps 60 --urls "url"

#Format mp4, 2160p, fps 60, path ./playlist4
 dtv-cli --output ./playlist4 --extension mp4 --height 2160 --fps 60 --urls "url1" "url2"

#Format webm, 2160p, fps 60, path /home/user/Videos
 dtv-cli -o /home/user/Videos -e webm -H 2160 --fps 60 -u "url1" "url2" "url3"

#Format mp4, 4320p, fps 60, path ./myvideos
 dtv-cli -o ./myvideos -e mp4 -H 4320 --fps 60 -u "url1" "url2" "url3"

#Format webm, 1080p, fps 30, path current
 dtv-cli -f webm -u "url1"

#Format mp4, 1080p, fps 30, ru subtitles, path current
 dtv-cli write-subs -u "url1"

#Format mp4, 1080p, fps 30, en subtitles, path current
 dtv-cli --write-subs --sub-lang "en" -u "url1"

#Format mp4, 1080p, fps 30, translate audio from ru to en, path current
 dtv-cli --translate-from-lang "ru" --translate-to-lang"en" -u "url1"

#Format mp4, 1080p, fps 30, translate audio from ru to kk, ru subtitles, path current
 dtv-cli --translate-from-lang "en" --translate-to-lang"kk" --write-subs --sub-lang "ru" -u "url1"

#Format mp4, 1080p, fps 30, translate audio from en to ru, ru subtitles, replace main audio stream with volume 50, path current
 dtv-cli "url" --output /disk_2/Videos/ --replace-audio Brimstone_-_In_One_Breath.flac --vol-audio 50 --write-subs

```
### DEV VC-CODE
#### В корне проекта введите команду
```
 rm -rf _build && bear -- cmake -S . -B _build && bear -- cmake --build _build -j8
```
#### Далее, если vc code был в этот момент запущен, перезапустить его, либо нажмите Help -> Show all commands -> введите в терминале "Reload Window" и нажмите Еnter. Проект готов к разработке.


