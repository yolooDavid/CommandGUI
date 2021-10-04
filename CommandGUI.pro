QT += core widgets
TARGET = CommandGUI
TEMPLATE = app
SOURCES += main.cpp mainwindow.cpp command.cpp
HEADERS += mainwindow.h command.h
LIBS += -lboost_thread-mt -lpthread

macx {
    _BOOST_PATH = /usr/local/Cellar/boost/1.76.0
    INCLUDEPATH += "$${_BOOST_PATH}/include"
    LIBS += -L$${_BOOST_PATH}/lib
}
