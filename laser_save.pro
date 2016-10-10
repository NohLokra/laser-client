SOURCES += \
    main.cpp \
    mainwindow.cpp \
    apiservice.cpp \
    scoreparser.cpp \
    filewatcher.cpp \
    logmanager.cpp \
    jsonencodable.cpp

QT += widgets network

HEADERS += \
    mainwindow.h \
    apiservice.h \
    scoreparser.h \
    filewatcher.h \
    logmanager.h \
    jsonencodable.h

CONFIG += c++11
