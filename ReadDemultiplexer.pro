QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
QT += svg
QT += svgwidgets

INCLUDEPATH += $$PWD/src

INCLUDEPATH += $$PWD/tools/SCDemultiplexingPipeline/src/lib
INCLUDEPATH += $$PWD/tools/SCDemultiplexingPipeline/include
INCLUDEPATH += /usr/local/Cellar/boost/1.85.0/include
INCLUDEPATH += $$system(brew --prefix boost)/include
INCLUDEPATH += /usr/local/opt/boost/include

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/EventHandler/demultiplexingHandler.cpp \
    src/main.cpp \
    src/windows/constantparameters.cpp \
    src/windows/mainwindow.cpp \
    src/qpixmaplayoutitem.cpp \
    src/readassemblyevents.cpp \
    src/windows/rnaparameters.cpp \
    src/windows/startwindow.cpp \
    src/windows/umiParameters.cpp \
    src/windows/variableParameters.cpp

HEADERS += \
    src/EventHandler/demultiplexingHandler.h \
    src/windows/constantparameters.h \
    src/windows/mainwindow.h \
    src/qpixmaplayoutitem.h \
    src/readassemblyevents.h \
    src/windows/parameterbaseclass.h \
    src/windows/rnaparameters.h \
    src/windows/startwindow.h \
    src/windows/umiParameters.h \
    src/windows/variableParameters.h

FORMS += \
    src/windows/constantparameters.ui \
    src/windows/mainwindow.ui \
    src/windows/rnaparameters.ui \
    src/windows/startwindow.ui \
    src/windows/testRun.ui \
    src/windows/umiParameters.ui \
    src/windows/variableParameters.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

