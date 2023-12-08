#ifndef BULLET_H
#define BULLET_H

#include "Enemy.h"
#include "Eagle.h"
#include "Brick.h"
#include "Player.h"

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet(bool isMyBullet = false);
    bool isMine(){return isMyBullet;}

private slots:
    void move();


signals:
    void bulletHitsBrick(Bullet *bullet, Brick *brick);
    void bulletHitsEagle(Bullet *bullet, Eagle *eagle);
    void bulletHitsEnemy(Bullet *bullet, Enemy *Enemy);
    void bulletHitsPlayer(Bullet *bullet, Player *player);

private:
    QTimer *timer;
    bool isMyBullet;
};

#endif // BULLET_H
