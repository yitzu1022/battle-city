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
<<<<<<< HEAD
    void setRotation(qreal newRotation);
    qreal rotation() const;
=======
>>>>>>> ca69e8e2c571cfcdcb483cf913a4679b793fcf82

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
<<<<<<< HEAD
    qreal m_rotation;
=======
>>>>>>> ca69e8e2c571cfcdcb483cf913a4679b793fcf82
};

#endif // BULLET_H
