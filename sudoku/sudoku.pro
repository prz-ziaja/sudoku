TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lstdc++fs

SOURCES += \
        main.cpp \
    map_sudoku.cpp \
    getsudoku_filesystem.cpp


HEADERS += \
    map_sudoku.h \
    getsudoku_filesystem.h
