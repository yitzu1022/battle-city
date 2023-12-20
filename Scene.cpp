#include "Scene.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <QList>
#include <QFont>
#include <stdlib.h>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QPalette>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
Scene::Scene(QObject *parent,Score *score)
    : QGraphicsScene{parent}
{
    sc = score;
    setenemy(20);
    //new出Eagle
    eagle=new Eagle();
    eagle->setPos(0-eagle->boundingRect().width()/2+2,300-eagle->boundingRect().height());
    addItem(eagle);
    eagle->setZValue(1);//使Eagle always在前景
    //建立灰色的牆
    int wall_d=0;
    for(int i=0;i<2;i++){
        wall=new Wall();
        wall->setPos(-20,-190+wall_d);
        addItem(wall);
        wall->setZValue(1);
        wall_d+=16;
    }
    //建立螢幕最左邊的牆
    wall=new Wall();
    wall->setPos(-395,0);
    wall->setScale(1.425);
    addItem(wall);
    wall->setZValue(1);
    //建立螢幕最右邊的牆
    wall=new Wall();
    wall->setPos(335,0);
    wall->setScale(1.425);
    addItem(wall);
    wall->setZValue(1);

    //建立上下各四個磚塊牆
    int brickwallFirst_x=-338;
    int brickwallFirst_y=-225;
    for(int i=0;i<2;i++){
        int Distance_between_brickwall_1=0;
        for(int j=0;j<4;j++){
            setBrickwall(brickwallFirst_x+Distance_between_brickwall_1,brickwallFirst_y,2,7);
            if(j==1){
                Distance_between_brickwall_1+=(brick->boundingRect().width()*10.5);
            }
            else{
                Distance_between_brickwall_1+=(brick->boundingRect().width()*3);
            }
        }
        brickwallFirst_y=brickwallFirst_y+brick->boundingRect().height()*4+150;
    }
    //建立最中間的H型磚塊牆
    int Distance_between_brickwall_2=0;
    for(int i=0;i<3;i++){
        int brickwall_2_num_y=0;
        int brickwall_2_first_y=0;
        if(i==1){
            brickwall_2_num_y=2;
            brickwall_2_first_y=30;
        }
        else{
            brickwall_2_num_y=7;
            brickwall_2_first_y=15;
        }
        setBrickwall(-82+Distance_between_brickwall_2,brickwall_2_first_y,2,brickwall_2_num_y);
        Distance_between_brickwall_2=Distance_between_brickwall_2+50;
    }
    //建立中間最上面的兩個磚塊牆
    int Distance_between_brickwall_3=0;
    for(int i=0;i<2;i++){
        setBrickwall(-82+Distance_between_brickwall_3,-225,2,5);
        Distance_between_brickwall_3+=50*2;
    }
    //建立H型磚塊牆上面的兩個小磚塊牆
    int Distance_between_brickwall_4=0;
    for(int i=0;i<2;i++){
        setBrickwall(-82+Distance_between_brickwall_4,-80,2,2);
        Distance_between_brickwall_4+=50*2;
    }
    //建立左邊與右邊的磚塊牆
    int Distance_between_brickwall_5=0;
    for(int i=0;i<2;i++){
        setBrickwall(-280+Distance_between_brickwall_5,-30,4,2);
        Distance_between_brickwall_5+=(brick->boundingRect().width()*12-3);
    }
    //建立最左邊與最右邊的小磚塊牆
    setBrickwall(-398,-30,2,1);
    setBrickwall(-338+brick->boundingRect().width()*16.5+60,-30,2,1);
    //用來建立eagle的堡壘
    setBrickwall(0-brick->boundingRect().width()*2-10,217,1,4);
    setBrickwall(0-brick->boundingRect().width()*2-10,197,6,1);
    setBrickwall(51,217,1,4);

    //new出player
    player = new Player();
    player->setPos(-140,250);
    addItem(player);
    player->setZValue(1);//使player always在前景

    //new出enemy
    enemyCounter = 0 ;
    spawnEnemy() ;

    timer = new QTimer() ;
    connect(timer , &QTimer::timeout , this ,&Scene::spawnEnemy );
    timer->start(2000) ;

    QGraphicsTextItem *tex = new QGraphicsTextItem("Life:");
    QFont fon("Arial",32);
    tex->setFont(fon);
    tex->setDefaultTextColor(Qt::white);
    tex->setZValue(2);
    tex->setPos(480,-50);
    addItem(tex);
    QGraphicsTextItem *texen = new QGraphicsTextItem("Enemy:");
    QFont fonen("Arial",32);
    texen->setFont(fonen);
    texen->setDefaultTextColor(Qt::white);
    texen->setZValue(2);
    texen->setPos(-600,-50);
    addItem(texen);
    setplayerlife(player);
    QPushButton *btn = new QPushButton("||");
    btn->setFixedSize(30,30);
    btn->setStyleSheet("font-size:20px ; background-color:Dark ; color:black");
    QGraphicsProxyWidget *button = addWidget(btn);
    button->setPos(480,-280);
    button->setZValue(5);
    connect(btn,&QPushButton::clicked,this,&Scene::togglePause);
    text = new QGraphicsTextItem("pause");
    QFont font("Arial",64);
    text->setFont(font);
    text->setDefaultTextColor(Qt::white);
}
//用來建造磚塊牆的function
void Scene::setBrickwall(int brickFirst_x, int brickFirst_y,int num_x,int num_y)
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

void Scene::setenemy(int x)
{
    textenemylife = new QGraphicsTextItem(QString::number(x));
    QFont font("Arial",32);
    textenemylife->setFont(font);
    textenemylife->setDefaultTextColor(Qt::white);
    textenemylife->setPos(-550,0);
    textenemylife->setZValue(2);
    addItem(textenemylife);
}

void Scene::setplayerlife(Player *player)
{

    int m;
    m = player->getlife();
    textlife = new QGraphicsTextItem(QString::number(m));
    QFont font("Arial",32);
    textlife->setFont(font);
    textlife->setDefaultTextColor(Qt::white);
    textlife->setPos(500,0);
    textlife->setZValue(2);
    addItem(textlife);
}


void Scene::handleBrickDeleted(Bullet *bullet, Brick *brick){
    removeItem(bullet);
    delete bullet;
    removeItem(brick);
    delete brick;
}

void Scene::GameEndded(Bullet *bullet, Eagle *eagle)
{
    emit gameover();
}

void Scene::enemyDestroy(Bullet *bullet, Enemy *enemy)
{
    removeItem(bullet);
    delete bullet;
    removeItem(enemy);
    delete enemy;
    enemyslain++;
    setenemy(20-enemyslain);
    sc->setscore(enemyslain*100);
    qDebug() << "score:" << sc->getscore();
    qDebug() << "Enemyslain:"<<enemyslain;
    enemyCounter --;
    spawnEnemy();
    if(enemyslain++ == 20){
        emit gameover();
    }
}

void Scene::loseOneLife(Bullet *bullet, Player *player)
{
    removeItem(bullet);
    removeItem(textlife);
    delete bullet;
    player->setlife();
    setplayerlife(player);
    player->setPos(-140,250);
    if(player->getlife()==0){
        emit gameover();
    }

}

void Scene::handleBulletDeleted(Bullet *bullet)
{
    removeItem(bullet);
    delete bullet;
}

void Scene::togglePause()
{
    isPaused = !isPaused;
    if (isPaused) {
        text->setPos(0,0);
        text->setZValue(5);
        addItem(text);
        qDebug("Game paused");
    } else {
        removeItem(text);
        qDebug("Game Resumed");
    }
}

void Scene::spawnEnemy()
{
    if(!isPaused){
        if(enemyslain >= 17) //擊殺20個enemy就獲勝，所以擊殺16個enemy之後就不新增enemy了
            return;
        if(enemyCounter >= 4) //同時在場的enemy最多4個
            return;
        Enemy *enemy = new Enemy();
        enemy->setPos(rand()%1170-600 , -250 );
        addItem(enemy);
        enemy->setZValue(1);//使enemy always在前景
        enemyCounter++;
        qDebug() << "Counter:"<<enemyCounter;
    }

}

//控制上下左右鍵使player可以上下左右移動(並且不可以撞到磚塊或牆壁)
void Scene::keyPressEvent(QKeyEvent *event){
    if(!isPaused){
        QPointF pos = player->pos();
        if(event->key() == Qt::Key_Left && pos.x()>(-600)){
            player->setRotation(270);
            player->setPos(pos+QPointF(-5,0));
        }else if(event->key() == Qt::Key_Right && pos.x()<(570)){
            player->setRotation(90);
            player->setPos(pos+QPointF(5,0));
        }else if(event->key() == Qt::Key_Up && pos.y()>(-300)){
            player->setRotation(0);
            player->setPos(pos+QPointF(0,-5));
        }else if(event->key() == Qt::Key_Down && pos.y()<(270)){
            player->setRotation(180);
            player->setPos(pos+QPointF(0,5));
        }else if (event->key() == Qt::Key_Space) {
            Bullet *bullet = new Bullet(true);
            connect(bullet, &Bullet::bulletHitsBrick, this, &Scene::handleBrickDeleted);
            connect(bullet, &Bullet::bulletHitsEagle, this, &Scene::GameEndded);
            connect(bullet, &Bullet::bulletHitsEnemy, this, &Scene::enemyDestroy);
            connect(bullet, &Bullet::bullet_bullet, this, &Scene::handleBulletDeleted);
            bullet->setPos(player->pos());
            bullet->setRotation(player->rotation());
            addItem(bullet);
        }

        QList<QGraphicsItem *> colliding_items = player->collidingItems();
        foreach (QGraphicsItem* item,colliding_items) {
            Brick *brick = dynamic_cast<Brick*>(item);
            Wall *wall = dynamic_cast<Wall*>(item);
            Enemy *enemy = dynamic_cast<Enemy*>(item);
            if(brick || wall || enemy){
                player->setPos(pos);
                return;
            }
        }
    }
}

