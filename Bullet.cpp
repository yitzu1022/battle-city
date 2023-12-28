#include "Bullet.h"
#include "Player.h"

#include <QGraphicsScene>

Bullet::Bullet(bool isMyBullet): isMyBullet(isMyBullet)
{
    //set bullet picture
    setPixmap(QPixmap(":/images/bullet.png").scaled(25,25,Qt::KeepAspectRatio));

    //timer for bullet move()
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Bullet::move);
    timer->start(50);
}

void Bullet::move() {
    // Check if the bullet is out of the scene
    if (scene() == nullptr || !scene()->sceneRect().contains(pos())) {
        // Remove the bullet from the scene first
        scene()->removeItem(this);
        delete this;
        return;
    }

    // If the bullet collides either Brick, Wall, Eagle, Enemy or Player, sent signal
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
        else if (brick && brick->isProtect() == true){ // if brick isProtect, it is seen as wall and can't be destroy
            emit bullet_bullet(this, bullet);
            return;
        }
        else if (eagle) {
            emit bulletHitsEagle(this, eagle);
            return;
        }
        else if (enemy && isMine() == true) { // if bullet that hit the enemy is shot by player
            emit bulletHitsEnemy(this, enemy);
            return;
        }
        else if (player && isMine() == false && player->isProtect() == false) { // if bullet that hit the player is shot by enemy and player is not Protected
            emit bulletHitsPlayer(this, player);
            return;
        }
        else if (bullet){ // bullet hits bullet
            emit bullet_bullet(this, bullet);
            return;
        }
        else if (wall){ //bullet hits wall is same as bullet hit bullet (only bullet should be destroy)
            emit bullet_bullet(this, bullet);
            return;
        }
    }

    // get bullet fly
    int dx;
    dx=speed*qCos(qDegreesToRadians(rotation()-90));
    int dy;
    dy=speed*qSin(qDegreesToRadians(rotation()-90));
    setPos(x()+dx,y()+dy);


}

void Bullet::stop()
{
    timer->stop();
    qDebug() << "bullet stop";
}

void Bullet::start()
{
    timer->start();
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

