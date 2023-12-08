#include "Bullet.h"

#include <QGraphicsScene>

Bullet::Bullet(bool isMyBullet): isMyBullet(isMyBullet)
{
    setPixmap(QPixmap(":/images/bullet.png").scaled(25,25,Qt::KeepAspectRatio));

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Bullet::move);
    timer->start(50);
}

void Bullet::move() {

    // If the bullet collides either Brick, Eagle, Enemy or Player, destroy both
    // if the bullet is out of Scene, it also should be delete ...add
    QList<QGraphicsItem *> colliding_items = collidingItems();
    foreach (QGraphicsItem *item, colliding_items) {
        if (dynamic_cast<Brick *>(item)) {
            emit bulletHitsBrick(this, dynamic_cast<Brick *>(item));
            return;
        }
        else if (dynamic_cast<Eagle *>(item)) {
            emit bulletHitsEagle(this, dynamic_cast<Eagle *>(item));
            return;
        }
        else if (dynamic_cast<Enemy *>(item) && isMine() == true) {
            emit bulletHitsEnemy(this, dynamic_cast<Enemy *>(item));
            return;
        }
        else if (dynamic_cast<Player *>(item) && isMine() == false) {
            emit bulletHitsPlayer(this, dynamic_cast<Player *>(item));
            return;
        }
    }

    // Move the bullet up
    // Should be change by direction
    // if direction .....
    setPos(x(), y()-10);


}
