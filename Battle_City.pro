QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Brick.cpp \
    Bullet.cpp \
    ChooseRound.cpp \
    ChoosesScene.cpp \
    Eagle.cpp \
    Enemy.cpp \
    Grass.cpp \
    Ice.cpp \
    Player.cpp \
    River.cpp \
    Scene.cpp \
    Skill.cpp \
    Score.cpp \
    ScoreScene.cpp \
    Start.cpp \
    Startscene.cpp \
    Wall.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    Brick.h \
    Bullet.h \
    ChooseRound.h \
    ChooseScene.h \
    Eagle.h \
    Enemy.h \
    Grass.h \
    Ice.h \
    Player.h \
    River.h \
    Scene.h \
    Skill.h \
    Score.h \
    ScoreScene.h \
    Start.h \
    Startscene.h \
    Wall.h \
    widget.h

FORMS += \
    ChooseRound.ui \
    Score.ui \
    Start.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
