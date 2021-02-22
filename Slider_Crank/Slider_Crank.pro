QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    crank.cpp \
    fixedhinge.cpp \
    hinge.cpp \
    main.cpp \
    mainwidget.cpp \
    mywidget.cpp \
    plot.cpp \
    point.cpp \
    qcustomplot.cpp \
    scene.cpp \
    slider.cpp

HEADERS += \
    crank.h \
    fixedhinge.h \
    hinge.h \
    mainwidget.h \
    mywidget.h \
    plot.h \
    point.h \
    qcustomplot.h \
    scene.h \
    slider.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
