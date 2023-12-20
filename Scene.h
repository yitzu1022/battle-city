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

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    void setBrickwall(int brickFirst_x,int brickFirst_y,int num_x,int num_y);


    void spawnEnemy() ;

public slots: //slots function
    void handleBrickDeleted(Bullet *bullet, Brick *brick);
    void GameEndded(Bullet *bullet, Eagle *eagle);
    void enemyDestroy(Bullet *bullet, Enemy *enemy);
    void loseOneLife(Bullet *bullet, Player *player);
    void handleBulletDeleted(Bullet *bullet);

    //skill
    void addOneLife();
    void grenadeBoom();
    void helmetProtect(Player *player);

signals:
    //grenade, helmet, shovel, star, tank, timer
    void player_grenade();
    void player_helmet(Player *player);
    void player_shovel();
    void player_star(Player *player, Skill *skill);
    void player_tank();
    void player_timer();

private:
    Eagle *eagle;
    Brick *brick;
    Brick *brickFirst;
    Wall *wall;
    Player *player;
    Enemy *enemy;
    QList<Enemy*> enemies;
    QTimer *timer ;
    Skill *skill;
    int enemyCounter;
    int enemyslain = 0;



protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // SCENE_H
