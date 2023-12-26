#ifndef SECONDSCENE_H
#define SECONDSCENE_H
#include <QGraphicsScene>
#include <QObject>
#include "Eagle.h"
#include "Brick.h"
#include "Wall.h"
#include "Grass.h"
#include "River.h"
#include "Ice.h"
#include "Player.h"
#include "Bullet.h"


class SecondScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SecondScene(QObject *parent = nullptr);
    void setBrickwall(int brickFirst_x,int brickFirst_y,int num_x,int num_y);
    void setGrasswall(int grassFirst_x,int grassFirst_y,int num_x,int num_y);
    void setRiver(int riverFirst_x,int riverFirst_y,int num_x,int num_y);
    void setIce(int IceFirst_x,int IceFirst_y,int num_x,int num_y);

public slots:
    void player_move();
signals:

private:
    Eagle *eagle;
    Brick *brick;
    Brick *brickFirst;
    Wall *wall;
    Grass *grass;
    River *river;
    Ice *ice;
    int number_of_player;
    QList<int> keys;
    Player *player_1;
    Player *player_2;
    QTimer *keyRespondTimer;
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // SECONDSCENE_H
