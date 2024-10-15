<!-- MANPAGE: BEGIN EXCLUDED SECTION -->
<div align="center">

![DTV-CLI](.github/workflows/head.jpg)
    
[![GitHub Release](https://img.shields.io/github/v/release/31normaslavik/dtv-cli?sort=date&display_name=tag&style=for-the-badge&labelColor=green)](https://github.com/31normaslavik/dtv-cli/releases "Release")
[![Supported Sites](https://img.shields.io/badge/-Supported_Sites-brightgreen.svg?style=for-the-badge)](https://github.com/yt-dlp/yt-dlp/blob/master/supportedsites.md "Supported Sites")
[![License: Unlicense](https://img.shields.io/badge/-license-blue.svg?style=for-the-badge)](LICENSE "License")
[![CI Status](https://img.shields.io/github/actions/workflow/status/31normaslavik/dtv-cli/.github/workflows/ubuntu.yml?branch=main&label=Tests&style=for-the-badge&labelColor=4B88A2)](https://github.com/31normaslavik/dtv-cli/actions "CI Status")
![GitHub commit activity](https://img.shields.io/github/commit-activity/m/31normaslavik/dtv-cli?style=for-the-badge&labelColor=70A37F&color=ADBDFF)
![GitHub last commit](https://img.shields.io/github/last-commit/31normaslavik/dtv-cli?display_timestamp=author&style=for-the-badge&labelColor=79B473)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/31normaslavik/dtv-cli/.github%2Fworkflows%2Fubuntu.yml?style=for-the-badge&labelColor=505168)
![GitHub branch check runs](https://img.shields.io/github/check-runs/31normaslavik/dtv-cli/main?style=for-the-badge&labelColor=004777)
![GitHub Created At](https://img.shields.io/github/created-at/31normaslavik/dtv-cli?style=for-the-badge&labelColor=DBBEA1&color=E08E45)
![GitHub Downloads (all assets, all releases)](https://img.shields.io/github/downloads/31normaslavik/dtv-cli/total?style=for-the-badge&labelColor=379392&color=B3C0A4)
    
</div>
<!-- MANPAGE: END EXCLUDED SECTION -->
    

# dtv-cli
## Версия на русском языке: [Нажми меня](README_RU.md)
### Downloading videos, playlists with translation and subtitles from the Yandex neural network
## Available for translation sites [![Supported Sites](https://img.shields.io/badge/-push_me-187795.svg?style=for-the-badge)](https://github.com/FOSWLY/vot-cli/wiki/%5BEN%5D-Supported-sites "Supported Sites")


## [INSTALL](INSTALL.md) <svg height="32" width="32" role="img" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg"><title>Code::Blocks</title><path d="M.011 0v8.406H8.61V0zm15.39 0v8.406H24V0zM8.972.658l.012 7.869 2.54 2.43.007-5.564zm6.066 0-2.555 4.735.004 5.564 2.54-2.43zM.332 8.768l5.52 2.677 5.655-.006-2.773-2.67zm14.944 0L12.53 11.49l5.655-.09 5.498-2.631zm-9.323 3.855L.318 15.232h8.405l2.748-2.722zm6.565-.113 2.747 2.722h8.402l-5.586-2.609zm-1.006.533-2.54 2.43-.011 7.873 2.555-4.74zm.964 0-.008 5.564 2.559 4.74-.011-7.874zM0 15.598V24h8.598v-8.402zm15.39 0V24h8.598v-8.402z"/></svg>


### HOW USE <svg height="32" width="32" role="img" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg"><title>GNOME Terminal</title><path d="M1.846 0A1.841 1.841 0 000 1.846v18.463c0 1.022.823 1.845 1.846 1.845h20.308A1.841 1.841 0 0024 20.31V1.846A1.841 1.841 0 0022.154 0H1.846zm0 .924h20.308c.512 0 .922.41.922.922v18.463c0 .511-.41.921-.922.921H1.846a.919.919 0 01-.922-.921V1.846c0-.512.41-.922.922-.922zm0 .922v18.463h20.308V1.846H1.846zm1.845 2.14l3.235 1.758v.836L3.69 8.477V7.385l2.243-1.207v-.033L3.69 5.076v-1.09zM7.846 9.23h3.693v.924H7.846V9.23zM0 21.736v.418C0 23.177.823 24 1.846 24h20.308A1.841 1.841 0 0024 22.154v-.418a2.334 2.334 0 01-1.846.918H1.846A2.334 2.334 0 010 21.736Z"/></svg>
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

