QT += widgets

TARGET = Shelfr
TEMPLATE = app

# Headers
HEADERS += \
    headers/core/book.h \
    headers/core/film.h \
    headers/core/media.h \
    headers/core/mediavisitorinterface.h \
    headers/core/music.h \
    headers/core/videogame.h \
    headers/core/jsonmanager.h \
    headers/gui/mainwindow.h \
    headers/gui/sidebar.h \
    headers/gui/workspace.h \
    headers/gui/thememanager.h \
    headers/gui/defaultview.h \
    headers/gui/additemview.h \
    headers/gui/searchitemview.h \
    headers/gui/mediacard.h \
    headers/gui/edititemview.h \
    headers/gui/viewitemview.h \
    headers/gui/mediacardvisitor.h \
    headers/gui/mediafiltervisitor.h \
    headers/gui/baseview.h

# Sources
SOURCES += \
    main.cpp \
    src/core/book.cpp \
    src/core/film.cpp \
    src/core/media.cpp \
    src/core/mediavisitorinterface.cpp \
    src/core/music.cpp \
    src/core/videogame.cpp \
    src/core/jsonmanager.cpp \
    src/gui/mainwindow.cpp \
    src/gui/sidebar.cpp \
    src/gui/workspace.cpp \
    src/gui/thememanager.cpp \
    src/gui/defaultview.cpp \
    src/gui/additemview.cpp \
    src/gui/searchitemview.cpp \
    src/gui/mediacard.cpp \
    src/gui/edititemview.cpp \
    src/gui/viewitemview.cpp \
    src/gui/mediacardvisitor.cpp \
    src/gui/mediafiltervisitor.cpp \
    src/gui/baseview.cpp

# Resources
RESOURCES += resources.qrc