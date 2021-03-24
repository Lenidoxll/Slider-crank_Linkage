QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    _constants.cpp \
    double_slider_crank_linkage.cpp \
    image_of_slider_crank_linkage.cpp \
    main.cpp \
    mainwindow.cpp \
    mechanism_1.cpp \
    mechanism_2.cpp \
    menegement.cpp \
    menu.cpp \
    parts.cpp \
    plot.cpp \
    plot_2.cpp \
    qcustomplot.cpp \
    slider_crank_linkage.cpp \
    value.cpp

HEADERS += \
    _constants.h \
    double_slider_crank_linkage.h \
    image_of_slider_crank_linkage.h \
    mainwindow.h \
    mechanism_1.h \
    mechanism_2.h \
    menegement.h \
    menu.h \
    parts.h \
    plot.h \
    plot_2.h \
    qcustomplot.h \
    slider_crank_linkage.h \
    value.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    status_pause_or_play.qrc \
    tollbars_icons.qrc
