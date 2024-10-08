

find_program(MAKE make)
message("MAKE:      ${MAKE}")

find_program(PYTHON3 python3)
message("PYTHON3:   ${PYTHON3}")

find_program(NODE node)
message("NODE:      ${NODE}")

find_program(VOTCLI vot-cli)
message("VOTCLI:    ${VOTCLI}")

find_program(YTDLP yt-dlp)
message("YTDLP:     ${YTDLP}")

# debian ubuntu
find_program(APT apt)
message("APT:       ${APT}")

# debian ubuntu
find_program(APTGET apt-get)
message("APTGET:    ${APTGET}")

# only in manjaro
find_program(PAMAC pamac)
message("PAMAC:     ${PAMAC}")

# arch
find_program(PACMAN pacman)
message("PACMAN:    ${PACMAN}")

find_program(YAY yay)
message("YAY:       ${YAY}")

# preinstalled in fedora
find_program(FLATPAK flatpak)
message("FLATPAK:   ${FLATPAK}")

# fedora
find_program(RPM rpm)
message("RPM:       ${RPM}")

find_program(ZYPPER zypper)
message("ZYPPER:    ${ZYPPER}")

find_program(PORTAGE portage)
message("PORTAGE:   ${PORTAGE}")

find_program(VCPKG vcpkg)
message("VCPKG:     ${VCPKG}")

find_program(PIP pip)
message("PIP:       ${PIP}")

find_program(CONAN conan)
message("CONAN:     ${CONAN}")

find_program(BUILD2 build2)
message("BUILD2:    ${BUILD2}")

find_program(CPM cpm)
message("CPM:       ${CPM}")

# preinstalled in ubuntu
find_program(SNAP snap)
message("SNAP:      ${SNAP}")

# fedora
find_program(DNF dnf)
message("DNF:       ${DNF}")

# debian
find_program(DPKG dpkg)
message("DPKG:      ${DPKG}")
