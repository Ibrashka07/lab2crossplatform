QT += widgets #добавляет модуль widgets в список подключаемых модулей

CONFIG += c++17 # говорит компилятору: «используй стандарт C++17». CONDIG-хранит настройки сборки
CONFIG -= app_bundle # не создавать .app-бандл.

TARGET = ObjectTreeDemo # имя итогового файла
TEMPLATE = app # тип проекта - приложение

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h \
    widgets.h

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
