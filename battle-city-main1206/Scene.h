#ifndef SCENE_H
#define SCENE_H
#include <QGraphicsScene>
#include <QObject>
#include "Eagle.h"
#include "Enemy.h"
#include "Brick.h"
#include "Wall.h"
#include "Player.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    void setBrickwall(int brickFirst_x,int brickFirst_y,int num_x,int num_y);
    void spawnEnemy() ;
public slots: //slots function
    void stopBrick(Enemy *enemy);
    void stopWall(Enemy *enemy);
    void stopEnemy(Enemy *enemy,Enemy *otherenemy);

signals:


private:
    Eagle *eagle;
    Brick *brick;
    Brick *brickFirst;
    Wall *wall;
    Player *player;
    Enemy *enemy;
    Enemy *otherenemy;
    QTimer *timer ;
    int enemyCounter;

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // SCENE_H
