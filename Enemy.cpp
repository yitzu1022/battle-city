#include "Enemy.h"
#include "Brick.h"
#include "Wall.h"
#include "Player.h"
#include "Bullet.h"
#include "Scene.h"
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include <QRandomGenerator>

Enemy::Enemy(QObject *parent)
    : QObject{parent}, shootTimer(new QTimer(this))
{
    setPixmap(QPixmap(":/images/enemy.png"));

    timer = new QTimer() ;
    //connect(發出signal的人是誰,發出甚麼訊號,誰來處理signal,用哪個slot function處理)
    connect(timer , &QTimer::timeout , this ,&Enemy::move );//把signal和slot function串接再一起
    timer->start(150);//每150ms會啟動一次timer

    //bullet shooting timer
    connect(shootTimer, &QTimer::timeout, this, &Enemy::shootBullet);
    int interval = QRandomGenerator::global()->bounded(1000, 5000); // 1 to 5 seconds
    shootTimer->start(interval);

}

qreal Enemy::rotation() const
{
    return m_rotation;
}

//轉動enemy的方向
void Enemy::setRotation(qreal newRotation)
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

void Enemy::move()
{
    int a = rand()%4 ;
    if( a == 0  && x()>(-600)) //enemy 向左
    {
        setRotation(-90);
        setPos( x()-5 ,y());
        QList<QGraphicsItem *> colliding_items = collidingItems();
        foreach (QGraphicsItem* item,colliding_items) {
            Brick *brick = dynamic_cast<Brick*>(item);
            Wall *wall = dynamic_cast<Wall*>(item);
            Enemy *otherenemy =dynamic_cast<Enemy*>(item);
            Player *player = dynamic_cast<Player*>(item);
            if(brick || wall || otherenemy||player){
                setPos(x()+5 ,y());
                return;
            }
        }
    }else if (a == 1 && y()>(-300) )//enemy 向上
    {
        setRotation(0);
        setPos(x() ,y()-5);
        QList<QGraphicsItem *> colliding_items = collidingItems();
        foreach (QGraphicsItem* item,colliding_items) {
            Brick *brick = dynamic_cast<Brick*>(item);
            Wall *wall = dynamic_cast<Wall*>(item);
            Enemy *otherenemy =dynamic_cast<Enemy*>(item);
            Player *player = dynamic_cast<Player*>(item);
            if(brick || wall || otherenemy||player){
                setPos(x() ,y()+5);
                return;
            }
        }
    }else if(a == 2 && x()<(570))//向右
    {
        setRotation(90);
        setPos( x()+5 ,y());
        QList<QGraphicsItem *> colliding_items = collidingItems();
        foreach (QGraphicsItem* item,colliding_items) {
            Brick *brick = dynamic_cast<Brick*>(item);
            Wall *wall = dynamic_cast<Wall*>(item);
            Enemy *otherenemy =dynamic_cast<Enemy*>(item);
            Player *player = dynamic_cast<Player*>(item);
            if(brick || wall || otherenemy||player){
                setPos(x()-5 ,y());
                return;
            }
        }
    }
    else if(a == 3 && y()<(270))//向下
    {
        setRotation(180);
        setPos(x() ,y()+5);
        QList<QGraphicsItem *> colliding_items = collidingItems();
        foreach (QGraphicsItem* item,colliding_items) {
            Brick *brick = dynamic_cast<Brick*>(item);
            Wall *wall = dynamic_cast<Wall*>(item);
            Enemy *otherenemy =dynamic_cast<Enemy*>(item);
            Player *player = dynamic_cast<Player*>(item);
            if(brick || wall || otherenemy||player){
                setPos(x() ,y()-5);
                return;
            }
        }
    }



}

void Enemy::shootBullet() {
    Bullet *bullet = new Bullet(false);
    Scene *scene = dynamic_cast<Scene*>(this->scene());
    connect(bullet, &Bullet::bulletHitsBrick, scene, &Scene::handleBrickDeleted);
    connect(bullet, &Bullet::bulletHitsEagle, scene, &Scene::GameEndded);
    connect(bullet, &Bullet::bulletHitsPlayer, scene, &Scene::loseOneLife);
//    connect(bullet, &Bullet::bulletDeleted, scene, &Scene::handleBulletDeleted); // Enemy's bullet hit
    connect(bullet, &Bullet::bullet_bullet, scene, &Scene::handleBulletDeleted); // bullets' hit
    bullet->setPos(pos());
    bullet->setRotation(rotation());
    scene->addItem(bullet);
}
