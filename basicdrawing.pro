QT += widgets core gui

INCLUDEPATH+= \Eigen

HEADERS       = window.h \
    renderarea.h \
    linkedstructure.h \
    link.h \
    ik.h
SOURCES       = main.cpp\ window.cpp \
    renderarea.cpp \
    linkedstructure.cpp \
    ik.cpp \
    link.cpp
RESOURCES += basicdrawing.qrc



