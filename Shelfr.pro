QT += core widgets

CONFIG += c++17

# You can make your code fail to compile if you use deprecated APIs.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    src/core/book.cpp \
    src/core/film.cpp \
    src/core/jsonmanager.cpp \
    src/core/media.cpp \
    src/core/music.cpp \
    src/core/videogame.cpp \
    src/gui/additemview.cpp \
    src/gui/baseview.cpp \
    src/gui/defaultview.cpp \
    src/gui/edititemview.cpp \
    src/gui/mainwindow.cpp \
    src/gui/mediacard.cpp \
    src/gui/mediacardvisitor.cpp \
    src/gui/mediafiltervisitor.cpp \
    src/gui/searchitemview.cpp \
    src/gui/sidebar.cpp \
    src/gui/thememanager.cpp \
    src/gui/viewitemview.cpp \
    src/gui/workspace.cpp

HEADERS += \
    headers/core/book.h \
    headers/core/film.h \
    headers/core/jsonmanager.h \
    headers/core/media.h \
    headers/core/mediavisitorinterface.h \
    headers/core/music.h \
    headers/core/videogame.h \
    headers/gui/additemview.h \
    headers/gui/baseview.h \
    headers/gui/defaultview.h \
    headers/gui/edititemview.h \
    headers/gui/mainwindow.h \
    headers/gui/mediacard.h \
    headers/gui/mediacardvisitor.h \
    headers/gui/mediafiltervisitor.h \
    headers/gui/searchitemview.h \
    headers/gui/sidebar.h \
    headers/gui/thememanager.h \
    headers/gui/viewitemview.h \
    headers/gui/workspace.h

# ADD THIS LINE - Include the resource file
RESOURCES += resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target