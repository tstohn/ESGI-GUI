QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
QT += svg
QT += svgwidgets

INCLUDEPATH += $$PWD/src
INCLUDEPATH += $$PWD/src/controller
INCLUDEPATH += $$PWD/src/model
INCLUDEPATH += $$PWD/src/view

INCLUDEPATH += $$PWD/external/ESGI/include/Demultiplexing
INCLUDEPATH += $$PWD/external/ESGI/include/Utils
INCLUDEPATH += $$PWD/external/ESGI/include/FeatureCounting
INCLUDEPATH += $$PWD/external/ESGI/external

INCLUDEPATH += /usr/local/Cellar/boost/1.85.0/include
INCLUDEPATH += $$system(brew --prefix boost)/include
INCLUDEPATH += /usr/local/opt/boost/include

LIBS += -L$$PWD/external/lib -lesgi

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/controller/demultiplexingcontroller.cpp \
    src/model/demultiplexingparameters.cpp \
    src/controller/demultiplexingHandler.cpp \
    src/main.cpp \
    src/view/constantparameters.cpp \
    src/view/mainwindow.cpp \
    src/qpixmaplayoutitem.cpp \
    src/readassemblyevents.cpp \
    src/view/rnaparameters.cpp \
    src/view/startwindow.cpp \
    src/view/umiParameters.cpp \
    src/view/variableParameters.cpp

HEADERS += \
    src/controller/demultiplexingcontroller.h \
    src/model/demultiplexingparameters.h \
    src/controller/demultiplexingHandler.h \
    src/view/constantparameters.h \
    src/view/mainwindow.h \
    src/qpixmaplayoutitem.h \
    src/readassemblyevents.h \
    src/view/parameterbaseclass.h \
    src/view/rnaparameters.h \
    src/view/startwindow.h \
    src/view/umiParameters.h \
    src/view/variableParameters.h

FORMS += \
    src/view/constantparameters.ui \
    src/view/mainwindow.ui \
    src/view/rnaparameters.ui \
    src/view/startwindow.ui \
    src/view/testRun.ui \
    src/view/umiParameters.ui \
    src/view/variableParameters.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

