QT += widgets

TARGET = Shelfr
TEMPLATE = app

# Headers
HEADERS += \
    headers/core/book.h \
    headers/core/film.h \
    headers/core/media.h \
    headers/core/mediaobserverinterface.h \
    headers/core/mediavisitorinterface.h \
    headers/core/music.h \
    headers/core/videogame.h \
    headers/gui/mainwindow.h \
    headers/gui/sidebar.h \
    headers/gui/workspace.h

# Sources
SOURCES += \
    main.cpp \
    src/core/book.cpp \
    src/core/film.cpp \
    src/core/media.cpp \
    src/core/mediaobserverinterface.cpp \
    src/core/mediavisitorinterface.cpp \
    src/core/music.cpp \
    src/core/videogame.cpp \
    src/gui/mainwindow.cpp \
    src/gui/sidebar.cpp \
    src/gui/workspace.cpp

# Resources
RESOURCES += resources.qrc