QT += core gui widgets sql charts

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    butceyoneticisi.cpp \
    harcamadialog.cpp \
    hedefdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    rapordialog.cpp \
    veritabani.cpp

HEADERS += \
    butceyoneticisi.h \
    harcamadialog.h \
    hedefdialog.h \
    mainwindow.h \
    rapordialog.h \
    veritabani.h

FORMS += \
    harcamadialog.ui \
    hedefdialog.ui \
    mainwindow.ui \
    rapordialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
