QT       += core gui opengl widgets xml

TARGET = template
TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/mainwidget.cpp \
    src/geometryengine.cpp \
    src/objloader.cpp \
    src/particule.cpp

HEADERS += \
    src/mainwidget.h \
    src/geometryengine.h \
    src/objloader.h \
    src/particule.h

RESOURCES += \
    ressources/shaders.qrc \


