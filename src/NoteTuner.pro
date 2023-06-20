QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    midiplayer.cpp \
    midiwriter.cpp \
    notemanager.cpp \
    notemodel.cpp \
    notetablewidget.cpp \
    notewidget.cpp \
    recordmanager.cpp \
    spectrumwidget.cpp

HEADERS += \
    constants.h \
    mainwindow.h \
    midiplayer.h \
    midiwriter.h \
    notemanager.h \
    notemodel.h \
    notetablewidget.h \
    notewidget.h \
    recordmanager.h \
    spectrumwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -lwinmm

INCLUDEPATH += C:\cpp_libs\bass
LIBS += C:\cpp_libs\bass\bass.lib

INCLUDEPATH += C:\cpp_libs\aubio\include
LIBS += -LC:\cpp_libs\aubio\lib -laubio

INCLUDEPATH += C:\cpp_libs\midifile\include
LIBS += -LC:\cpp_libs\midifile\lib\ -lmidifile
