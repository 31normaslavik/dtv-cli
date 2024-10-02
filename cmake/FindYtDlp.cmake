
if(NOT YTDLP)

    if(CMAKE_SYSTEM_NAME STREQUAL Linux)
        message("CMAKE_SYSTEM_NAME is: ${CMAKE_SYSTEM_NAME}")

        file(DOWNLOAD https://github.com/yt-dlp/yt-dlp/releases/latest/download/SHA2-512SUMS
            ${PROJECT_BINARY_DIR}/bin/dtv/SHA2-512SUMS
            INACTIVITY_TIMEOUT 30
            SHOW_PROGRESS
        )

        file(STRINGS ${PROJECT_BINARY_DIR}/bin/dtv/SHA2-512SUMS
            HASH
            LIMIT_COUNT 1
            REGEX yt-dlp$
            ENCODING UTF-8
        )
        string(SUBSTRING ${HASH} 0 128 HASH)

        file(DOWNLOAD https://github.com/yt-dlp/yt-dlp/releases/latest/download/yt-dlp
            ${PROJECT_BINARY_DIR}/bin/dtv/yt-dlp
            EXPECTED_HASH SHA512=${HASH}
            INACTIVITY_TIMEOUT 30
            SHOW_PROGRESS
        )
    endif()

    if(WIN32)
        message("CMAKE_SYSTEM_NAME is: ${CMAKE_SYSTEM_NAME}")

        file(DOWNLOAD https://github.com/yt-dlp/yt-dlp/releases/latest/download/SHA2-512SUMS
            ${PROJECT_BINARY_DIR}/bin/dtv/SHA2-512SUMS
            INACTIVITY_TIMEOUT 30
            SHOW_PROGRESS
        )

        file(STRINGS ${PROJECT_BINARY_DIR}/bin/dtv/SHA2-512SUMS
            HASH
            LIMIT_COUNT 1
            REGEX yt-dlp.exe$
            ENCODING UTF-8
        )
        string(SUBSTRING ${HASH} 0 128 HASH)

        file(DOWNLOAD https://github.com/yt-dlp/yt-dlp/releases/latest/download/yt-dlp.exe
            ${PROJECT_BINARY_DIR}/bin/dtv/yt-dlp.exe
            EXPECTED_HASH SHA512=${HASH}
            INACTIVITY_TIMEOUT 30
            SHOW_PROGRESS
        )
    endif()

    if(CMAKE_SYSTEM_NAME STREQUAL Darwin)
        message("CMAKE_SYSTEM_NAME is: ${CMAKE_SYSTEM_NAME}")

        file(DOWNLOAD https://github.com/yt-dlp/yt-dlp/releases/latest/download/SHA2-512SUMS
            ${PROJECT_BINARY_DIR}/bin/dtv/SHA2-512SUMS
            INACTIVITY_TIMEOUT 30
            SHOW_PROGRESS
        )

        file(STRINGS ${PROJECT_BINARY_DIR}/bin/dtv/SHA2-512SUMS
            HASH
            LIMIT_COUNT 1
            REGEX yt-dlp_macos$
            ENCODING UTF-8
        )
        string(SUBSTRING ${HASH} 0 128 HASH)

        file(DOWNLOAD https://github.com/yt-dlp/yt-dlp/releases/latest/download/yt-dlp_macos
            ${PROJECT_BINARY_DIR}/bin/dtv/yt-dlp_macos
            EXPECTED_HASH SHA512=${HASH}
            INACTIVITY_TIMEOUT 30
            SHOW_PROGRESS
        )
    endif()
endif()
