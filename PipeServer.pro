TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Sources\main.cpp \
        Sources\stdafx.cpp \
        Sources\PipeManager.cpp \
        Sources\pipeserver.cpp


HEADERS += \
        Headers\stdafx.h \
        Headers\PipeManager.h \
        Headers\csvfile.h \
        Headers\pipeserver.h


