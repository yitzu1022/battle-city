#include "Bullet.h"
#include "SecondScene.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <QList>

SecondScene::SecondScene(QObject *parent)
    : QGraphicsScene{parent}
{
    //new出Eagle
    eagle=new Eagle();
    eagle->setPos(0-eagle->boundingRect().width()/2+2,300-eagle->boundingRect().height());
    addItem(eagle);
    eagle->setZValue(1);//使Eagle always在前景
    //建立灰色的牆
    int wall_d_1=0;
    for(int i=0;i<2;i++){
        wall=new Wall();
        wall->setPos(-50,-190+wall_d_1);
        wall->setScale(1.425);
        addItem(wall);
        wall->setZValue(1);
        wall_d_1+=16;
    }

    int wall_d_4=0;
    for(int i=0;i<2;i++){
        wall=new Wall();
        wall->setPos(-105,-150+wall_d_4);
        wall->setScale(1.425);
        addItem(wall);
        wall->setZValue(1);
        wall_d_4+=16;
    }
    setBrickwall(-109,-180,2,1);

    //建立螢幕最左邊的牆
    wall=new Wall();
    wall->setPos(-393,-150);
    wall->setScale(1.425);
    addItem(wall);
    wall->setZValue(1);

    //建立螢幕最右邊的牆
    int wall_d_2=0;
    for(int i=0;i<2;i++){
        wall=new Wall();
        wall->setPos(278+wall_d_2,-30);
        wall->setScale(1.425);
        addItem(wall);
        wall->setZValue(1);
        wall_d_2+=55;
    }

    setIce(-300,260,8,2);
    setBrickwall(-338,120,2,5);
    wall=new Wall();
    wall->setPos(-335,107);
    wall->setScale(1.425);
    addItem(wall);
    wall->setZValue(1);

    setBrickwall(-220,180,2,2);
    wall=new Wall();
    wall->setPos(-217,167);
    wall->setScale(1.425);
    addItem(wall);
    wall->setZValue(1);

    //建立最左邊L型磚塊牆
    setIce(-395,-20,2,4);
    setBrickwall(-340,-20,2,2);
    //建立上述最左邊L型磚塊牆旁邊的磚塊牆
    setBrickwall(-255,-20,1,5);
    setBrickwall(-230,-40,2,4);
    //建立中間的L型磚塊牆
    setBrickwall(-110,40,2,6);
    setBrickwall(-60,140,4,1);
    int wall_d_3=0;
    for(int i=0;i<2;i++){
        wall=new Wall();
        wall->setPos(-107,20+wall_d_3);
        wall->setScale(1.425);
        addItem(wall);
        wall->setZValue(1);
        wall_d_3+=22;
    }
    //建立螢幕中心的十字草地牆
    setGrasswall(-50,20,7,4);
    setGrasswall(10,-20,2,2);
    setGrasswall(10,86,2,3);
    //建立螢幕中心的L型河流
    setIce(-50,-63,11,2);
    setRiver(97,-22,4,8);
    setRiver(142,200,2,6);
    //建立螢幕右下角的十字草地牆
    setGrasswall(185,150,10,5);
    setIce(290,110,3,2);
    setIce(290,240,3,3);
    setBrickwall(288,30,2,3);
    setBrickwall(330,30,2,1);
    setBrickwall(330,-80,2,2);
    setBrickwall(10,-133,2,3);
    setBrickwall(-109,-320,2,3);
    setBrickwall(70,-320,2,9);
    setIce(200,-320,3,10);
    setBrickwall(-290,-183,2,6);
    setBrickwall(-395,-100,2,2);
    //建立螢幕左上角之river
    setIce(-228,-300,2,3);
    setRiver(-228,-200,2,7);
    setRiver(-187,-95,3,2);
    //用來建立eagle的堡壘
    setBrickwall(0-brick->boundingRect().width()*2-10,217,1,4);
    setBrickwall(0-brick->boundingRect().width()*2-10,197,6,1);
    setBrickwall(51,217,1,4);

    //new出player
    number_of_player=2; //1代表1player 2代表2player
    if(number_of_player==1){   //one-player 模式
        player_1 = new Player();
        player_2 = new Player();
        player_1->setPos(-120,250);
        addItem(player_1);
        player_1->setZValue(1);//使player always在前景
    }else{    //teo-player 模式
        player_1 = new Player();
        player_1->setPos(100,250);
        addItem(player_1);
        player_1->setZValue(1);//使player always在前景

        player_2 = new Player();
        player_2->setPos(-120,250);
        addItem(player_2);
        player_2->setZValue(1);//使player always在前景
    }

    keyRespondTimer = new QTimer();  //控制player的移動
    keyRespondTimer->start(100);
    connect(keyRespondTimer,&QTimer::timeout, this, &SecondScene::player_move);
}
//用來建造磚塊牆的function
void SecondScene::setBrickwall(int brickFirst_x, int brickFirst_y,int num_x,int num_y)
{
    for(int i=0;i<num_x;i++){
        int d=0;
        for(int j=0;j <num_y;j++){
            brick=new Brick();
            brick->setPos(brickFirst_x,brickFirst_y+d);
            d=d+brick->boundingRect().height()-17;
            addItem(brick);
            brick->setZValue(1);
        }
        brickFirst_x=brickFirst_x+brick->boundingRect().width()-10;
    }

}
void SecondScene::setGrasswall(int grassFirst_x, int grassFirst_y, int num_x, int num_y)
{
    for(int i=0;i<num_x;i++){
        int d=0;
        for(int j=0;j <num_y;j++){
            grass=new Grass();
            grass->setPos(grassFirst_x,grassFirst_y+d);
            d=d+grass->boundingRect().height();
            addItem(grass);
            grass->setZValue(3);
        }
        grassFirst_x=grassFirst_x+grass->boundingRect().width();
    }
}
void SecondScene::setRiver(int riverFirst_x, int riverFirst_y, int num_x, int num_y)
{
    for(int i=0;i<num_x;i++){
        int d=0;
        for(int j=0;j <num_y;j++){
            river=new River();
            river->setPos(riverFirst_x,riverFirst_y+d);
            d=d+river->boundingRect().height();
            addItem(river);
            river->setZValue(1);
        }
        riverFirst_x=riverFirst_x+river->boundingRect().width();
    }
}

void SecondScene::setIce(int IceFirst_x, int IceFirst_y, int num_x, int num_y)
{
    for(int i=0;i<num_x;i++){
        int d=0;
        for(int j=0;j <num_y;j++){
            ice=new Ice();
            ice->setPos(IceFirst_x,IceFirst_y+d);
            d=d+ice->boundingRect().height();
            addItem(ice);
            ice->setZValue(1);
        }
        IceFirst_x=IceFirst_x+ice->boundingRect().width();
    }
}


//控制上下左右鍵使player可以上下左右移動(並且不可以撞到磚塊或牆壁)
void SecondScene::player_move()
{
    QPointF pos_1 = player_1->pos();
    QPointF pos_2 = player_2->pos();
    foreach (int key, keys) {
        switch (key) {
        case Qt::Key_Left:{
            if(pos_1.x()>(-450)){
                player_1->setRotation(270);
                player_1->setPos(pos_1+QPointF(-5,0));

                QList<QGraphicsItem *> colliding_items_ice = player_1->collidingItems();
                foreach (QGraphicsItem* item,colliding_items_ice) {
                    Ice *ice = dynamic_cast<Ice*>(item);
                    if(ice){
                        player_1->setPos(pos_1+QPointF(-20,0));
                    }
                }
            }
            break;}
        case Qt::Key_Right:{
            if(pos_1.x()<(420)){
                player_1->setRotation(90);
                player_1->setPos(pos_1+QPointF(5,0));

                QList<QGraphicsItem *> colliding_items_ice = player_1->collidingItems();
                foreach (QGraphicsItem* item,colliding_items_ice) {
                    Ice *ice = dynamic_cast<Ice*>(item);
                    if(ice){
                        player_1->setPos(pos_1+QPointF(20,0));
                    }
                }
            }
            break;}
        case Qt::Key_Up:{
            if(pos_1.y()>(-300)){
                player_1->setRotation(0);
                player_1->setPos(pos_1+QPointF(0,-5));

                QList<QGraphicsItem *> colliding_items_ice = player_1->collidingItems();
                foreach (QGraphicsItem* item,colliding_items_ice) {
                    Ice *ice = dynamic_cast<Ice*>(item);
                    if(ice){
                        player_1->setPos(pos_1+QPointF(0,-20));
                    }
                }
            }
            break;}
        case Qt::Key_Down:{
            if(pos_1.y()<(270)){
                player_1->setRotation(180);
                player_1->setPos(pos_1+QPointF(0,5));

                QList<QGraphicsItem *> colliding_items_ice = player_1->collidingItems();
                foreach (QGraphicsItem* item,colliding_items_ice) {
                    Ice *ice = dynamic_cast<Ice*>(item);
                    if(ice){
                        player_1->setPos(pos_1+QPointF(0,20));
                    }
                }
            }
            break;}
        case Qt::Key_A:{
            if(number_of_player==2 && pos_2.x()>(-450)){  //有兩個player時才會進入此條件
                player_2->setRotation(270);
                player_2->setPos(pos_2+QPointF(-5,0));

                QList<QGraphicsItem *> colliding_items_ice = player_2->collidingItems();
                foreach (QGraphicsItem* item,colliding_items_ice) {
                    Ice *ice = dynamic_cast<Ice*>(item);
                    if(ice){
                        player_2->setPos(pos_2+QPointF(-20,0));
                    }
                }
            }
            break;}
        case Qt::Key_D:{
            if(number_of_player==2 && pos_2.x()<(420)){                 //有兩個player時才會進入此條件
                player_2->setRotation(90);
                player_2->setPos(pos_2+QPointF(5,0));

                QList<QGraphicsItem *> colliding_items_ice = player_2->collidingItems();
                foreach (QGraphicsItem* item,colliding_items_ice) {
                    Ice *ice = dynamic_cast<Ice*>(item);
                    if(ice){
                        player_2->setPos(pos_2+QPointF(20,0));
                    }
                }
            }
            break;}
        case Qt::Key_W:{                                          //有兩個player時才會進入此條件
            if(number_of_player==2 && pos_2.y()>(-300)){
                player_2->setRotation(0);
                player_2->setPos(pos_2+QPointF(0,-5));

                QList<QGraphicsItem *> colliding_items_ice = player_2->collidingItems();
                foreach (QGraphicsItem* item,colliding_items_ice) {
                    Ice *ice = dynamic_cast<Ice*>(item);
                    if(ice){
                        player_2->setPos(pos_2+QPointF(0,-20));
                    }
                }
            }
            break;}
        case Qt::Key_S:{
            if(number_of_player==2 && pos_2.y()<(270)){                //有兩個player時才會進入此條件
                player_2->setRotation(180);
                player_2->setPos(pos_2+QPointF(0,5));

                QList<QGraphicsItem *> colliding_items_ice = player_2->collidingItems();
                foreach (QGraphicsItem* item,colliding_items_ice) {
                    Ice *ice = dynamic_cast<Ice*>(item);
                    if(ice){
                        player_2->setPos(pos_2+QPointF(0,20));
                    }
                }
            }
            break;}
        case Qt::Key_Space:{
            Bullet *bullet = new Bullet(true);
            //connect(bullet, &Bullet::bulletHitsBrick, this, &Scene::handleBrickDeleted);
            //connect(bullet, &Bullet::bulletHitsEagle, this, &Scene::GameEndded);
            //connect(bullet, &Bullet::bulletHitsEnemy, this, &Scene::enemyDestroy);
            //connect(bullet, &Bullet::bullet_bullet, this, &Scene::handleBulletDeleted);
            bullet->setPos(player_1->pos());
            bullet->setRotation(player_1->rotation());
            addItem(bullet);
            break;
        }
        case Qt::Key_Shift:{
            if(number_of_player==2){                                 //有兩個player時才會進入此條件
                Bullet *bullet = new Bullet(true);
                //connect(bullet, &Bullet::bulletHitsBrick, this, &Scene::handleBrickDeleted);
                //connect(bullet, &Bullet::bulletHitsEagle, this, &Scene::GameEndded);
                //connect(bullet, &Bullet::bulletHitsEnemy, this, &Scene::enemyDestroy);
                //connect(bullet, &Bullet::bullet_bullet, this, &Scene::handleBulletDeleted);
                bullet->setPos(player_2->pos());
                bullet->setRotation(player_2->rotation());
                addItem(bullet);
            }

            break;
        }
        default:
            break;
        }
        QList<QGraphicsItem *> colliding_items_1 = player_1->collidingItems();
        foreach (QGraphicsItem* item,colliding_items_1) {
            Brick *brick = dynamic_cast<Brick*>(item);
            Wall *wall = dynamic_cast<Wall*>(item);
            Enemy *enemy = dynamic_cast<Enemy*>(item);
            River *river = dynamic_cast<River*>(item);
            if(brick || wall || enemy||river){
                player_1->setPos(pos_1);
                return;
            }
            if(ice){

            }
        }
        if(number_of_player==2){                                       //有兩個player時才會進入此條件
            QList<QGraphicsItem *> colliding_items_2 = player_2->collidingItems();
            foreach (QGraphicsItem* item,colliding_items_2) {
                Brick *brick = dynamic_cast<Brick*>(item);
                Wall *wall = dynamic_cast<Wall*>(item);
                Enemy *enemy = dynamic_cast<Enemy*>(item);
                River *river = dynamic_cast<River*>(item);
                if(brick || wall || enemy ||river){
                    player_2->setPos(pos_2);
                    return;
                }
            }
        }
  }
}

void SecondScene::keyPressEvent(QKeyEvent *event){  //當按鍵按下
    if(!event->isAutoRepeat())
        keys.append(event->key());  //若非長按時自動觸發的按下，就將key值加入容器
    if(!keyRespondTimer->isActive())
        keyRespondTimer->start(100);  //若定時器不在運行，就啟動它
}

void SecondScene::keyReleaseEvent(QKeyEvent *event){ //當按鍵釋放
    if(!event->isAutoRepeat())
        keys.removeAll(event->key());  //若非長按時自動觸發的釋放，就將key值從容器中刪除
    if(keys.isEmpty())
        keyRespondTimer->stop(); //若容器空了，則關閉定時器
}
