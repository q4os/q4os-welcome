set(welcome-screen5.exu_SRCS
    appmain.cpp
    form1.cpp
    form2.cpp
    form3.cpp
)

ki18n_wrap_ui(welcome-screen5.exu_SRCS form1.ui form2.ui form3.ui)

add_executable(welcome-screen5.exu ${welcome-screen5.exu_SRCS} resource1.qrc)

target_link_libraries(welcome-screen5.exu
    Qt5::Widgets
    KF5::CoreAddons
    KF5::I18n
    KF5::XmlGui
    KF5::ConfigWidgets
)

install( TARGETS welcome-screen5.exu DESTINATION /usr/bin/ )
install( FILES data/q4os-welcome-screen.desktop DESTINATION /usr/share/applications/ RENAME q4os-welcome-screen5.desktop )
