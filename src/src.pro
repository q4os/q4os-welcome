TEMPLATE = app
LANGUAGE = C++

DESTDIR = ../build
OBJECTS_DIR = ../build/.obj
UI_DIR = ../build/.ui
MOC_DIR = ../build/.moc
QMOC_DIR = ../build/.qmoc
QRCC_DIR = ../build/.qrcc

CONFIG += warn_off
# CONFIG -= exceptions stl warn_on

# >>> other CONFIG options ..
# CONFIG += warn_on qt thread
# CONFIG += exceptions stl rtti opengl x11 console precompile_header windows
# CONFIG += qtestlib assistant uitools dbus help
# QT += sql svg xml network qt3support opengl script webkit xmlpatterns

# REQUIRES = thread

QMAKE_UIC=/usr/share/tqt3/bin/tquic
QMAKE_MOC=/usr/share/tqt3/bin/tqmoc
QMAKE_MOC_SRC=/usr/share/tqt3/src/moc

# QMAKE_POST_LINK  = find data/ -name hi\*-app-welcomescreen.svg -execdir mkdir -p ../../build/.icons/"{}" \; ; find data/ -name hi\*-app-welcomescreen.svg -execdir cp "{}" ../../build/.icons/"{}"/welcome-screen.svg \;
# QMAKE_CLEAN += rm -rf ../build/.icons

SOURCES += form1.cpp \
 appmain.cpp \
 form2.cpp \
 form3.cpp
HEADERS += form1.h \
 appmain.h \
 form2.h \
 form3.h
FORMS += ui_form1.ui \
 ui_form2.ui \
 ui_form3.ui

TARGET = welcome-screen.exu

# >>> installation ..
target.path = /usr/bin
# data01.files = data/some_script.sh
# data01.path = /usr/share/apps/q4os_system/bin
data02.files = data/q4os-welcome-screen.desktop
data02.path = /usr/share/applications
# data03.files = ../build/.icons/16x16/welcome-screen.svg
# data03.extra = ""mkdir -p ../build/.icons/16x16 ; cp data/hi16-app-welcomescreen.svg ../build/.icons/16x16/welcome-screen.svg""
# data03.path = /usr/share/icons/hicolor/16x16/apps/
# data04.files = ../build/.icons/32x32/welcome-screen.svg
# data04.extra = ""mkdir -p ../build/.icons/32x32 ; cp data/hi32-app-welcomescreen.svg ../build/.icons/32x32/welcome-screen.svg""
# data04.path = /usr/share/icons/hicolor/32x32/apps/
# data05.files = ../build/.icons/48x48/welcome-screen.svg
# data05.extra = ""mkdir -p ../build/.icons/48x48 ; cp data/hi48-app-welcomescreen.svg ../build/.icons/48x48/welcome-screen.svg""
# data05.path = /usr/share/icons/hicolor/48x48/apps/
# data06.files = ../build/.icons/64x64/welcome-screen.svg
# data06.extra = ""mkdir -p ../build/.icons/64x64 ; cp data/hi64-app-welcomescreen.svg ../build/.icons/64x64/welcome-screen.svg""
# data06.path = /usr/share/icons/hicolor/64x64/apps/
# data07.files = ../build/.icons/128x128/welcome-screen.svg
# data07.extra = ""mkdir -p ../build/.icons/128x128 ; cp data/hi128-app-welcomescreen.svg ../build/.icons/128x128/welcome-screen.svg""
# data07.path = /usr/share/icons/hicolor/128x128/apps/
# data08.files = ../build/.icons/24x24/welcome-screen.svg
# data08.extra = ""mkdir -p ../build/.icons/24x24 ; cp data/hi24-app-welcomescreen.svg ../build/.icons/24x24/welcome-screen.svg""
# data08.path = /usr/share/icons/hicolor/24x24/apps/
# data09.files = data/background1.png
# data09.path = /opt/program_files/q4os-welcome/share
# data10.files = data/background2.png
# data10.path = /opt/program_files/q4os-welcome/share

# INSTALLS += target data02 data03 data04 data05 data06 data07 data08 data09 data10
INSTALLS += target data02

# TARGETDEPS += ../build/libsrc0_lib1.a

INCLUDEPATH += \
 ../../../q4os_api/level3/03_shell_cmd \
 /usr/include/tqt \
 /usr/include/tqt3 \
 /opt/trinity/include

LIBS += \
  -L../../../q4os_api/build \
  -L/usr/lib \
  -L/opt/trinity/lib \
  -lshell_cmd \
  -ltqt-mt \
  -ltdecore \
  -ltdeui

#fix tde/trixie /usr/share/tqt3/mkspecs/default/qmake.conf:
QMAKE_LIBS_QT = -ltqt
#CONFIG += thread
