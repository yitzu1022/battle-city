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
    friend class Enemy;
    friend class Scene;
public:
    Bullet(bool isMyBullet = false);
    bool isMine(){return isMyBullet;} // return whether the bullet is shot by player
    void setRotation(qreal newRotation); // set the way bullet move
    qreal rotation() const;

private slots:
    void move();

signals:
    // if bullet hit item, it sent signal
    void bulletHitsBrick(Bullet *bullet, Brick *brick);
    void bulletHitsEagle(Bullet *bullet, Eagle *eagle);
    void bulletHitsEnemy(Bullet *bullet, Enemy *Enemy);
    void bulletHitsPlayer(Bullet *bullet, Player *player);
    void bulletDeleted(Bullet *bullet);
    void bullet_bullet(Bullet *bullet1, Bullet *bullet2);

public slots:
    // get the signal for stop and start bullet move()
    void stop();
    void start();

private:
    QTimer *timer;
    int speed = 10; //the speed that bullet move
    bool isMyBullet;
    qreal m_rotation;
};

#endif // BULLET_H
