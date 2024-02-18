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
#include "Skill.h"
#include "Score.h"
#include "Grass.h"
#include "River.h"
#include "Ice.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr,Score *score=nullptr, int Round=0, int number=1);
    void Round1Scene();
    void Round2Scene();
    void setGrasswall(int grassFirst_x,int grassFirst_y,int num_x,int num_y);
    void setRiver(int riverFirst_x,int riverFirst_y,int num_x,int num_y);
    void setIce(int IceFirst_x,int IceFirst_y,int num_x,int num_y);

    void setBrickwall(int brickFirst_x,int brickFirst_y,int num_x,int num_y);
    void setEagleBrickWall();
    void setenemy(int x);
    void setplayerlife(Player *player);
    void spawnEnemy() ;
public slots: //slots function
    void handleBrickDeleted(Bullet *bullet, Brick *brick);
    void GameEndded(Bullet *bullet, Eagle *eagle);
    void enemyDestroy(Bullet *bullet, Enemy *enemy);
    void loseOneLife(Bullet *bullet, Player *player);
    void handleBulletDeleted(Bullet *bullet);

    //skill
    void addOneLife(Player *player);
    void grenadeBoom();
    void helmetProtect(Player *player);
    void shovelChange();
    void playergetStar();
    void enemyStop();
    void player_move();
    void togglePause();
    void saveNowData(int Round);

signals:
    //grenade, helmet, shovel, star, tank, timer
    void player_grenade();
    void player_helmet(Player *player);
    void player_shovel();
    void player_star();
    void player_tank(Player *player);
    void player_timer();
    void gameover();
    void bulletStop();
    void bulletStart();

private:
    Eagle *eagle;
    Brick *brick;
    Brick *brickFirst;
    QList<Brick*> eagleBrick;
    Wall *wall;
    Grass *grass;
    River *river;
    Ice *ice;
    Player *player_1;
    Player *player_2;
    QTimer *keyRespondTimer;
    Enemy *enemy;
    QList<Enemy*> enemies;
    bool timerSkill = false;
    QTimer *timer ;
    Skill *skill;
    int enemyCounter;
    int enemyslain = 0;
    int enemyTotal=0;
    int armorlife=4;
    bool isPaused=false;
    QGraphicsTextItem *text;
    QGraphicsTextItem *textlifep1;
    QGraphicsTextItem *textlifep2;
    QGraphicsTextItem *textenemylife;
    Score *sc;
    int number_of_player;
    QList<int> keys;
    bool bullet_faster;
    int Round;
    QString p1life;
    QString p2life;
    QString enemylife;

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // SCENE_H
