@echo off
setlocal enableextensions
cd /d "%~dp0"

:: ANSI renk kodları
set "COLOR_GREEN=[92m"
set "COLOR_CYAN=[96m"
set "COLOR_YELLOW=[93m"
set "COLOR_MAGENTA=[95m"
set "COLOR_BLUE=[94m"
set "COLOR_RED=[91m"
set "COLOR_RESET=[0m"

:: Proje klasörleri
set build_folder=build_win
set release_folder=release_win
set publish_folder=publish_win

:: Temizleme işlemi: önceki build, release ve publish klasörlerini sil
echo %COLOR_GREEN%-----------------------------
echo  CLEANING FOLDERS
echo -----------------------------%COLOR_RESET%

for %%d in (build %release_folder% %publish_folder%) do (
    echo Deleting "%%d" folder...
    if exist "%%d" (
        rd /S /Q "%%d"
        echo %COLOR_GREEN% %%d directory deleted %COLOR_RESET%
    ) else (
        echo %COLOR_RED% %%d directory not found! %COLOR_RESET%
    )
)

:: Gerekli klasörlerin oluşturulması
echo %COLOR_CYAN%-----------------------------
echo  CREATING FOLDERS
echo -----------------------------%COLOR_RESET%

for %%d in (%release_folder% %build_folder% %publish_folder%) do (
    echo %COLOR_GREEN% Creating "%%d" folder... %COLOR_RESET%
    mkdir "%%d"
)

:: CMake ile projenin yapılandırılması ve install prefix belirtilmesi
echo %COLOR_YELLOW%-----------------------------
echo  CONFIGURING PROJECT WITH CMAKE
echo -----------------------------%COLOR_RESET%

call cmake -B %build_folder% -S . -G "Visual Studio 17 2022" -A x64 -DCMAKE_CXX_STANDARD=11 -DCMAKE_INSTALL_PREFIX=%publish_folder%

:: Debug ve Release sürümlerinin derlenmesi
echo %COLOR_MAGENTA%-----------------------------
echo  BUILDING DEBUG AND RELEASE APPLICATIONS
echo -----------------------------%COLOR_RESET%

call cmake --build %build_folder% --config Debug
call cmake --build %build_folder% --config Release

:: Debug ve Release sürümlerinin publish klasörüne kurulumu
echo %COLOR_BLUE%-----------------------------
echo  INSTALLING DEBUG AND RELEASE BUILDS TO PUBLISH FOLDER
echo -----------------------------%COLOR_RESET%

call cmake --install %build_folder% --config Debug
call cmake --install %build_folder% --config Release

:: Tamamlanma mesajı
echo %COLOR_GREEN%-----------------------------
echo  OPERATION COMPLETED!
echo -----------------------------%COLOR_RESET%

pause
exit /b 0
