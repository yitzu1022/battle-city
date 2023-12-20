#ifndef SCENE_H
#define SCENE_H
#include <QGraphicsScene>
#include <QObject>
#include "Eagle.h"
#include "Enemy.h"
#include "Brick.h"
#include "Wall.h"
#include "Player.h"
#include "Bullet.h"
#include "Score.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr,Score *score=nullptr);
    void setBrickwall(int brickFirst_x,int brickFirst_y,int num_x,int num_y);
    void setenemy(int x);
    void setplayerlife(Player *player);
    void spawnEnemy() ;
public slots: //slots function
    void handleBrickDeleted(Bullet *bullet, Brick *brick);
    void GameEndded(Bullet *bullet, Eagle *eagle);
    void enemyDestroy(Bullet *bullet, Enemy *enemy);
    void loseOneLife(Bullet *bullet, Player *player);
    void handleBulletDeleted(Bullet *bullet);
    void player_move();
    void togglePause();
signals:
    void gameover();

private:
    Eagle *eagle;
    Brick *brick;
    Brick *brickFirst;
    Wall *wall;
    Player *player_1;
    Player *player_2;
    QTimer *keyRespondTimer;
    Enemy *enemy;
    QTimer *timer ;
    int enemyCounter;
    int enemyslain = 0;
    bool isPaused=false;
    QGraphicsTextItem *text;
    QGraphicsTextItem *textlife;
    QGraphicsTextItem *textenemylife;
    Score *sc;
    int number_of_player;
    QList<int> keys;
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // SCENE_H
