QT       += core
QT -= gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addresourcedialog.cpp \
    deleteresourcedialog.cpp \
    editresourcedialog.cpp \
    employeeactionswindow.cpp \
    libraryemployeeinterface.cpp \
    main.cpp \
    mainwindow.cpp \
    Resource.cpp \
    Article.cpp \
    Book.cpp \
    DigitalBook.cpp \
    Thesis.cpp \
    studentactionswindow.cpp

HEADERS += \
    addresourcedialog.h \
    deleteresourcedialog.h \
    editresourcedialog.h \
    employeeactionswindow.h \
    libraryemployeeinterface.h \
    mainwindow.h \
    Resource.h \
    Article.h \
    Book.h \
    DigitalBook.h \
    Thesis.h \
    studentactionswindow.h

FORMS += \
    addresourcedialog.ui \
    deleteresourcedialog.ui \
    editresourcedialog.ui \
    employeeactionswindow.ui \
    libraryemployeeinterface.ui \
    mainwindow.ui \
    studentactionswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    bleu.qrc \
    mainback.qrc \
    white.qrc \
    wholeback.qrc \
    wholeback.qrc \
    wholebackground.qrc

DISTFILES += \
    libraryemployees.csv \
    resource.csv

QMAKE_POST_LINK += $$quote(copy /Y \"$$PWD\\libraryemployees.csv\" \"$$OUT_PWD\\\")

