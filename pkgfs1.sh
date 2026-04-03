#!/bin/sh

cd $(dirname $0)
THIS_SCRIPT_DIR="$(pwd)"
OUT1DIR="$THIS_SCRIPT_DIR/debian/q4os-welcome-common/" ; rm -rf $OUT1DIR ; mkdir -p $OUT1DIR/

mkdir -p $OUT1DIR/usr/share/icons/hicolor/16x16/apps/
mkdir -p $OUT1DIR/usr/share/icons/hicolor/24x24/apps/
mkdir -p $OUT1DIR/usr/share/icons/hicolor/32x32/apps/
mkdir -p $OUT1DIR/usr/share/icons/hicolor/48x48/apps/
mkdir -p $OUT1DIR/usr/share/icons/hicolor/64x64/apps/
mkdir -p $OUT1DIR/usr/share/icons/hicolor/128x128/apps/
cp $THIS_SCRIPT_DIR/src/data/hi16-app-welcomescreen.svg $OUT1DIR/usr/share/icons/hicolor/16x16/apps/welcome-screen.svg
cp $THIS_SCRIPT_DIR/src/data/hi24-app-welcomescreen.svg $OUT1DIR/usr/share/icons/hicolor/24x24/apps/welcome-screen.svg
cp $THIS_SCRIPT_DIR/src/data/hi32-app-welcomescreen.svg $OUT1DIR/usr/share/icons/hicolor/32x32/apps/welcome-screen.svg
cp $THIS_SCRIPT_DIR/src/data/hi48-app-welcomescreen.svg $OUT1DIR/usr/share/icons/hicolor/48x48/apps/welcome-screen.svg
cp $THIS_SCRIPT_DIR/src/data/hi64-app-welcomescreen.svg $OUT1DIR/usr/share/icons/hicolor/64x64/apps/welcome-screen.svg
cp $THIS_SCRIPT_DIR/src/data/hi128-app-welcomescreen.svg $OUT1DIR/usr/share/icons/hicolor/128x128/apps/welcome-screen.svg
mkdir -p $OUT1DIR/opt/program_files/q4os-welcome/share/
cp $THIS_SCRIPT_DIR/src/data/background1.png $OUT1DIR/opt/program_files/q4os-welcome/share/
cp $THIS_SCRIPT_DIR/src/data/background2.png $OUT1DIR/opt/program_files/q4os-welcome/share/
