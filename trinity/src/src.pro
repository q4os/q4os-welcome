TEMPLATE = app
LANGUAGE = C++

DESTDIR = ../build
OBJECTS_DIR = ../build/.obj
UI_DIR = ../build/.ui
MOC_DIR = ../build/.moc
QMOC_DIR = ../build/.qmoc
QRCC_DIR = ../build/.qrcc

CONFIG += warn_off

QMAKE_UIC=/usr/share/tqt3/bin/tquic
QMAKE_MOC=/usr/share/tqt3/bin/tqmoc
QMAKE_MOC_SRC=/usr/share/tqt3/src/moc

#shared/ is a sibling of trinity/, plasma/'s cmake build compiles the same files - the toolkit-free
#actions behind the buttons and the wording both frontends set from code
SOURCES += form1.cpp \
 appmain.cpp \
 form2.cpp \
 form3.cpp \
 ../../shared/ws_actions.cpp \
 ../../shared/ws_flows.cpp

HEADERS += form1.h \
 appmain.h \
 form2.h \
 form3.h \
 ../../shared/ws_actions.h \
 ../../shared/ws_flows.h \
 ../../shared/ws_dialogs.h \
 ws_dialogs_tqt.h \
 ../../shared/ws_strings.h \
 ../../shared/ws_paths.h

FORMS += ui_form1.ui \
 ui_form2.ui \
 ui_form3.ui

TARGET = welcome-screen.exu

target.path = /usr/bin
data02.files = data/q4os-welcome-screen.desktop
data02.path = /usr/share/applications
INSTALLS += target data02

INCLUDEPATH += \
 ../../shared \
 /usr/include \
 /usr/include/tqt \
 /usr/include/tqt3 \
 /opt/trinity/include

#no q4os-api library any more: the shell command helpers it was linked for live in shared/
LIBS += \
  -L/opt/trinity/lib \
  -ltqt-mt \
  -ltdecore \
  -ltdeui

QMAKE_LIBS_QT = -ltqt
