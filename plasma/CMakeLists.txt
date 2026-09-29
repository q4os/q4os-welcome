cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(q4os-welcome5)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 5.3.0 REQUIRED COMPONENTS Core Gui Widgets)

#the forms' strings go through wsTr() (ws_tr.h), the gettext "welcome-screen" catalog the Trinity
#frontend reads too, not through Qt's own tr()/.qm translations
qt5_wrap_ui(UI_HEADERS form1.ui form2.ui form3.ui OPTIONS -tr wsTr)

#shared/ is a sibling of plasma/, trinity/'s tqmake build compiles the same files - the toolkit-free
#actions behind the buttons and the wording both frontends set from code
add_executable(welcome-screen5.exu
    main.cpp
    form1.cpp
    form2.cpp
    form3.cpp
    ../shared/ws_actions.cpp
    ../shared/ws_flows.cpp
    resource1.qrc
    ${UI_HEADERS}
)

target_include_directories(welcome-screen5.exu PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../shared)

#plain Qt5, no KF5 and no q4os-api library: the KF5 xmlgui/i18n/coreaddons the generated tree
#pulled in only served KAboutData and KMessageBox
target_link_libraries(welcome-screen5.exu
    Qt5::Widgets
)
