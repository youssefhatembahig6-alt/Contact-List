QT       += core gui widgets
CONFIG   += c++17
TARGET    = ContactList
TEMPLATE  = app

INCLUDEPATH += src
INCLUDEPATH += /usr/include/mysql

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    src/Avl.cpp \
    src/Database.cpp \

HEADERS += \
    mainwindow.h \
    src/Contact.h \
    src/AvlTree.h \
    src/Database.h \

FORMS += mainwindow.ui
LIBS += -L/usr/lib64/mysql -lmysqlclient