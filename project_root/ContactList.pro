QT       += core gui widgets
CONFIG   += c++17
TARGET    = ContactList
TEMPLATE  = app

INCLUDEPATH += src

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    src/Avl.cpp \

HEADERS += \
    mainwindow.h \
    src/Contact.h \
    src/AvlTree.h \

FORMS += mainwindow.ui