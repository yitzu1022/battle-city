#include "Enemy.h"
#include "Brick.h"
#include "Wall.h"
#include "Player.h"
#include "Bullet.h"
#include "Scene.h"
#include "River.h"
#include "Ice.h"
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include <QRandomGenerator>

Enemy::Enemy(QObject *parent,int kind)
    : QObject{parent}, shootTimer(new QTimer(this))
{
    if(kind == 0)
    {
        setPixmap(QPixmap(":/images/enemy.png").scaled(25,25,Qt::KeepAspectRatio));
        kindof = 0;
    }
    if(kind == 1)
    {
        setPixmap(QPixmap(":/images/Armor_tank.png").scaled(30,30,Qt::KeepAspectRatio));
        kindof = 1;
    }
    if(kind == 2)
    {
        setPixmap(QPixmap(":/images/Fast_tank.png").scaled(30,30,Qt::KeepAspectRatio));
        kindof = 2 ;
    }
    if(kind == 3)
    {
        setPixmap(QPixmap(":/images/Power_tank.png").scaled(30,30,Qt::KeepAspectRatio));
        kindof = 3 ;
    }
    if(kind == 4)
    {
        setPixmap(QPixmap(":/images/Special_enemy.png").scaled(30,30,Qt::KeepAspectRatio));
        kindof =4;
    }
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


void Enemy::stop()
{
    timer->stop();
    shootTimer->stop();
    rotation_timer->stop();
}

void Enemy::start()
{
    timer->start();
    shootTimer->start();
    rotation_timer->start();
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
    QList<QGraphicsItem *> colliding_items = collidingItems();
    foreach (QGraphicsItem* item,colliding_items) {
        Brick *brick = dynamic_cast<Brick*>(item);
        River *river = dynamic_cast<River*>(item);
        Wall *wall = dynamic_cast<Wall*>(item);
        Enemy *otherenemy =dynamic_cast<Enemy*>(item);
        Player *player = dynamic_cast<Player*>(item);
    if(!isPaused){
        if( kindof == 2 ) //fast
        {
            if( rotation() == 270  && x()>(-450) ) //enemy 向左
            {
                setPos(x()-15 ,y());
                if(brick || wall || otherenemy||player||river){
                    setPos(x()+10 ,y());
                    rotate_to();
                    return;
                }
            }else if (rotation() == 0 && y()>(-300) )//enemy 向上
            {

                setPos(x() ,y()-15);
                if(brick || wall || otherenemy||player||river){
                    setPos(x() ,y()+10);
                    rotate_to();
                    return;
                }
            }else if(rotation() == 90 && x()<(420))//向右
            {

                setPos( x()+15 ,y());
                if(brick || wall || otherenemy||player||river){
                    setPos(x()-10 ,y());
                    rotate_to();
                    return;
                }
            }
            else if(rotation() == 180 && y()<(270))//向下
            {

                setPos(x() ,y()+15);
                if(brick || wall || otherenemy||player||river){
                    setPos(x() ,y()-10);
                    rotate_to();
                    return;
                }
            }
        }
        else
        {
            if( rotation() == 270  && x()>(-450) ) //enemy 向左
            {

                setPos( x()-5 ,y());
                if(brick || wall || otherenemy||player||river){
                   setPos(x()+10 ,y());
                    rotate_to();
                    return;
                }
            }else if (rotation() == 0 && y()>(-300) )//enemy 向上
            {

            setPos(x() ,y()-5);
                if(brick || wall || otherenemy||player||river){
                    setPos(x() ,y()+10);
                    rotate_to();
                    return;
                }
            }else if(rotation() == 90 && x()<(420))//向右
            {

                setPos( x()+5 ,y());
                if(brick || wall || otherenemy||player||river){
                    setPos(x()-10 ,y());
                    rotate_to();
                    return;
                }
            }
            else if(rotation() == 180 && y()<(270))//向下
            {

                setPos(x() ,y()+5);
                if(brick || wall || otherenemy||player||river){
                    setPos(x() ,y()-10);
                    rotate_to();
                    return;
                }
            }
        }
    }
    }
}


void Enemy::shootBullet() {
    Bullet *bullet = new Bullet(false);
    if (kindof == 3)
        bullet ->timer->start(25) ;
    Scene *scene = dynamic_cast<Scene*>(this->scene());
    connect(bullet, &Bullet::bulletHitsBrick, scene, &Scene::handleBrickDeleted);
    connect(bullet, &Bullet::bulletHitsEagle, scene, &Scene::GameEndded);
    connect(bullet, &Bullet::bulletHitsPlayer, scene, &Scene::loseOneLife);
//    connect(bullet, &Bullet::bulletDeleted, scene, &Scene::handleBulletDeleted); // Enemy's bullet hit
    connect(bullet, &Bullet::bullet_bullet, scene, &Scene::handleBulletDeleted); // bullets' hit
    connect(scene, &Scene::bulletStop, bullet, &Bullet::stop);
    connect(scene, &Scene::bulletStart, bullet, &Bullet::start);
    bullet->setPos(pos());
    bullet->setRotation(rotation());
    bullet->setZValue(10);
    scene->addItem(bullet);
}
