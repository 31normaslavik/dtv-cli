<!-- MANPAGE: BEGIN EXCLUDED SECTION -->
<div align="center">

![DTV-CLI](.github/head.jpg)
    
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
### Downloading videos, playlists with translation and subtitles from the Yandex neural network
### AVAILABLE TRANSLATION SITES [![Supported Sites](https://img.shields.io/badge/-push_me-187795.svg?style=for-the-badge)](https://github.com/FOSWLY/vot-cli/wiki/%5BEN%5D-Supported-sites "Supported Sites")
### AVAILABLE SITES FOR SIMPLE DOWNLOAD [![Supported Sites](https://img.shields.io/badge/-push_me-187795.svg?style=for-the-badge)](https://github.com/yt-dlp/yt-dlp/blob/master/supportedsites.md "Supported Sites")

## RELEASE
File|Description
:---|:---
[dtv-cli](https://github.com/31normaslavik/dtv-cli/releases/latest/download/dtv-cli)|**Linux/BSD**

## [INSTALL](INSTALL.md) 🔗

### HOW USE 
```
If the specified path does not exist, the program will try to   
create the missing directories.

Usage: dtv-cli [Options] urls

# mp4, 1080p, path current
 dtv-cli -u "url1"

# mp4, 480p, fps 30, path ./playlist4
 dtv-cli --output ./playlist4 --extension mp4 --height 480 --urls "url1" "url2"

# mp4, 1080p, fps 60, path ./playlist1
 dtv-cli --output ./playlist1 --extension mp4 --height 1080 --fps 60 --urls "url"

# mp4, 2160p, fps 60, path ./playlist4
 dtv-cli --output ./playlist4 --extension mp4 --height 2160 --fps 60 --urls "url1" "url2"

# webm, 2160p, fps 60, path /home/user/Videos
 dtv-cli -o /home/user/Videos -e webm -H 2160 --fps 60 -u "url1" "url2" "url3"

# mp4, 4320p, fps 60, path ./myvideos
 dtv-cli -o ./myvideos -e mp4 -H 4320 --fps 60 -u "url1" "url2" "url3"

# webm, 1080p, fps 30, path current
 dtv-cli -f webm -u "url1"

# mp4, 1080p, fps 30, ru subtitles, path current
 dtv-cli write-subs -u "url1"

# mp4, 1080p, fps 30, en subtitles, path current
 dtv-cli --write-subs --sub-lang "en" -u "url1"

# mp4, 1080p, fps 30, translate audio from ru to en, path current
 dtv-cli --translate-from-lang "ru" --translate-to-lang"en" -u "url1"

# mp4, 1080p, fps 30, translate audio from ru to kk, ru subtitles, path current
 dtv-cli --translate-from-lang "en" --translate-to-lang"kk" --write-subs --sub-lang "ru" -u "url1"

# mp4, 1080p, fps 30, translate audio from en to ru, ru subtitles, replace main audio stream with volume 50, path current
 dtv-cli "url" --output /disk_2/Videos/ --replace-audio Brimstone_-_In_One_Breath.flac --vol-audio 50 --write-subs

```

