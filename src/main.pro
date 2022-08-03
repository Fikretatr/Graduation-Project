TEMPLATE = app
TARGET = ssde
INCLUDEPATH += .

QT       += core gui
QT 		 += widgets

CONFIG += c++11

# Input
HEADERS += include/nlohmann_json.h \
           jsonToVlog.h \
           secdialog.h \
           statediagram.h \
           transition.h  \
           state.h  \
           fsd.h  \
           properties.h \
           mainwindow.h
SOURCES += transition.cpp \
           jsonToVlog.cpp \
           parser.cpp \
           state.cpp \
           fsd.cpp \
           properties.cpp \
           main.cpp \
           mainwindow.cpp

RESOURCES += resources.qrc

DISTFILES += \
    code.txt \
    output.txt
