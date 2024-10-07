#!/bin/bash

# ANSI renk kodları
COLOR_GREEN='\033[0;32m'
COLOR_CYAN='\033[0;36m'
COLOR_YELLOW='\033[0;33m'
COLOR_MAGENTA='\033[0;35m'
COLOR_BLUE='\033[0;34m'
COLOR_RED='\033[0;31m'
COLOR_RESET='\033[0m'

# Proje klasörleri
build_folder="build_linux"
release_folder="release_linux"
publish_folder="publish_linux"

# Temizleme işlemi: önceki build, release ve publish klasörlerini sil
echo -e "${COLOR_GREEN}-----------------------------"
echo -e " CLEANING FOLDERS"
echo -e "-----------------------------${COLOR_RESET}"

for folder in "$build_folder" "$release_folder" "$publish_folder"; do
    echo "Deleting \"$folder\" folder..."
    if [ -d "$folder" ]; then
        rm -rf "$folder"
        echo -e "${COLOR_GREEN}$folder directory deleted${COLOR_RESET}"
    else
        echo -e "${COLOR_RED}$folder directory not found!${COLOR_RESET}"
    fi
done

# Gerekli klasörlerin oluşturulması
echo -e "${COLOR_CYAN}-----------------------------"
echo -e " CREATING FOLDERS"
echo -e "-----------------------------${COLOR_RESET}"

for folder in "$release_folder" "$build_folder" "$publish_folder"; do
    echo -e "${COLOR_GREEN}Creating \"$folder\" folder...${COLOR_RESET}"
    mkdir -p "$folder"
done

# CMake ile projenin yapılandırılması ve install prefix belirtilmesi
echo -e "${COLOR_YELLOW}-----------------------------"
echo -e " CONFIGURING PROJECT WITH CMAKE"
echo -e "-----------------------------${COLOR_RESET}"

cmake -B "$build_folder" -S . -DCMAKE_CXX_STANDARD=11 -DCMAKE_INSTALL_PREFIX="$publish_folder"

# Debug ve Release sürümlerinin derlenmesi
echo -e "${COLOR_MAGENTA}-----------------------------"
echo -e " BUILDING DEBUG AND RELEASE APPLICATIONS"
echo -e "-----------------------------${COLOR_RESET}"

cmake --build "$build_folder" --config Debug
cmake --build "$build_folder" --config Release

# Debug ve Release sürümlerinin publish klasörüne kurulumu
echo -e "${COLOR_BLUE}-----------------------------"
echo -e " INSTALLING DEBUG AND RELEASE BUILDS TO PUBLISH FOLDER"
echo -e "-----------------------------${COLOR_RESET}"

cmake --install "$build_folder" --config Debug
cmake --install "$build_folder" --config Release

# Tamamlanma mesajı
echo -e "${COLOR_GREEN}-----------------------------"
echo -e " OPERATION COMPLETED!"
echo -e "-----------------------------${COLOR_RESET}"
