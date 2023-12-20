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
    timer->start(300);//每300ms會啟動一次timer

    //bullet shooting timer
    connect(shootTimer, &QTimer::timeout, this, &Enemy::shootBullet);
    int interval = QRandomGenerator::global()->bounded(1000, 5000); // 1 to 5 seconds
    shootTimer->start(interval);

    rotation_timer = new QTimer();
    connect(rotation_timer, &QTimer::timeout, this, &Enemy::rotate_to);
    rotation_timer->start(3000);//不要太常轉

}

qreal Enemy::rotation() const
{
    return m_rotation;
}

void Enemy::rotate_to()
{
    int a = rand()%4;
    if (a == 0)
        setRotation(270);
    if (a == 1)
        setRotation(0);
    if (a == 2)
        setRotation(90);
    if (a == 3)
        setRotation(180);
}

void Enemy::stop10sec()
{
    timer->stop();
    QTimer::singleShot(10000, [=]() {
        timer->start();
    });
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

    if( rotation() == 270  && x()>(-600)) //enemy 向左
    {

        setPos( x()-10 ,y());
        QList<QGraphicsItem *> colliding_items = collidingItems();
        foreach (QGraphicsItem* item,colliding_items) {
            Brick *brick = dynamic_cast<Brick*>(item);
            Wall *wall = dynamic_cast<Wall*>(item);
            Enemy *otherenemy =dynamic_cast<Enemy*>(item);
            Player *player = dynamic_cast<Player*>(item);
            if(brick || wall || otherenemy||player){
                setPos(x()+10 ,y());
                rotate_to();
                return;
            }
        }
    }else if (rotation() == 0 && y()>(-300) )//enemy 向上
    {

        setPos(x() ,y()-10);
        QList<QGraphicsItem *> colliding_items = collidingItems();
        foreach (QGraphicsItem* item,colliding_items) {
            Brick *brick = dynamic_cast<Brick*>(item);
            Wall *wall = dynamic_cast<Wall*>(item);
            Enemy *otherenemy =dynamic_cast<Enemy*>(item);
            Player *player = dynamic_cast<Player*>(item);
            if(brick || wall || otherenemy||player){
                setPos(x() ,y()+10);
                rotate_to();
                return;
            }
        }
    }else if(rotation() == 90 && x()<(570))//向右
    {

        setPos( x()+10 ,y());
        QList<QGraphicsItem *> colliding_items = collidingItems();
        foreach (QGraphicsItem* item,colliding_items) {
            Brick *brick = dynamic_cast<Brick*>(item);
            Wall *wall = dynamic_cast<Wall*>(item);
            Enemy *otherenemy =dynamic_cast<Enemy*>(item);
            Player *player = dynamic_cast<Player*>(item);
            if(brick || wall || otherenemy||player){
                setPos(x()-10 ,y());
                rotate_to();
                return;
            }
        }
    }
    else if(rotation() == 180 && y()<(270))//向下
    {

        setPos(x() ,y()+10);
        QList<QGraphicsItem *> colliding_items = collidingItems();
        foreach (QGraphicsItem* item,colliding_items) {
            Brick *brick = dynamic_cast<Brick*>(item);
            Wall *wall = dynamic_cast<Wall*>(item);
            Enemy *otherenemy =dynamic_cast<Enemy*>(item);
            Player *player = dynamic_cast<Player*>(item);
            if(brick || wall || otherenemy||player){
                setPos(x() ,y()-10);
                rotate_to();
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
