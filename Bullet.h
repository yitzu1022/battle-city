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
    void setRotation(qreal newRotation);
    qreal rotation() const;

    void setFast();

private slots:
    void move();


signals:
    void bulletHitsBrick(Bullet *bullet, Brick *brick);
    void bulletHitsEagle(Bullet *bullet, Eagle *eagle);
    void bulletHitsEnemy(Bullet *bullet, Enemy *Enemy);
    void bulletHitsPlayer(Bullet *bullet, Player *player);
    void bulletDeleted(Bullet *bullet);
    void bullet_bullet(Bullet *bullet1, Bullet *bullet2);

private:
    QTimer *timer;
    int speed = 10;
    bool isMyBullet;
    qreal m_rotation;
friend class Enemy;
};

#endif // BULLET_H
