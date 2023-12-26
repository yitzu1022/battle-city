#include "Bullet.h"
#include "Player.h"

#include <QGraphicsScene>

Bullet::Bullet(bool isMyBullet): isMyBullet(isMyBullet)
{
    setPixmap(QPixmap(":/images/bullet.png").scaled(25,25,Qt::KeepAspectRatio));

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Bullet::move);
    timer->start(50);
}

void Bullet::move() {
    // Check if the bullet is out of the scene
    if (scene() == nullptr || !scene()->sceneRect().contains(pos())) {
        // Remove the bullet from the scene first
        scene()->removeItem(this);
        qDebug("bullet deleted");
        delete this;
        return;
    }

    // If the bullet collides either Brick, Eagle, Enemy or Player, destroy both
    // if the bullet is out of Scene, it also should be delete ...add
    QList<QGraphicsItem *> colliding_items = collidingItems();
    foreach (QGraphicsItem *item, colliding_items) {
        Brick *brick = dynamic_cast<Brick*>(item);
        Wall *wall = dynamic_cast<Wall*>(item);
        Enemy *enemy = dynamic_cast<Enemy*>(item);
        Player *player = dynamic_cast<Player*>(item);
        Eagle *eagle = dynamic_cast<Eagle*>(item);
        Bullet *bullet = dynamic_cast<Bullet*>(item);
        if (brick && brick->isProtect() == false) {
            emit bulletHitsBrick(this, brick);
            return;
        }
        else if (brick && brick->isProtect() == true){
            emit bullet_bullet(this, bullet);
            return;
        }
        else if (eagle) {
            emit bulletHitsEagle(this, eagle);
            return;
        }
        else if (enemy && isMine() == true) {
            emit bulletHitsEnemy(this, enemy);
            return;
        }
//        else if (dynamic_cast<Enemy *>(item) && isMine() == false) {
//            emit bulletDeleted(this);
//            return;
//        }
        else if (player && isMine() == false && player->isProtect() == false) {
            emit bulletHitsPlayer(this, player);
            return;
        }
        else if (bullet){ // bullet hits bullet
            emit bullet_bullet(this, bullet);
            return;
        }
        else if (wall){
            emit bullet_bullet(this, bullet);
            return;
        }
    }

    int dx;
    dx=10*qCos(qDegreesToRadians(rotation()-90));
    int dy;
    dy=10*qSin(qDegreesToRadians(rotation()-90));
    setPos(x()+dx,y()+dy);


}

qreal Bullet::rotation() const
{
    return m_rotation;
}


void Bullet::setRotation(qreal newRotation)
{
    m_rotation = newRotation;
    //以中心點進行旋轉
    QPointF c =boundingRect().center(); //取得圖片中心點
    QTransform t; //用Qtransform此object來進行旋轉
    t.translate(c.x(),c.y());
    t.rotate(newRotation); //rotate到這個newRotation角度
    t.translate(-c.x(),-c.y());
    setTransform(t); //apply 此 transformation
}

