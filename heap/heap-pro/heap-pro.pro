TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../heap.cpp \
    ../main.cpp \
    ../../tree/tree.cpp \
    ../pqueue.cpp

HEADERS += \
    ../heap.h \
    ../../tree/tree.h \
    ../pqueue.h

