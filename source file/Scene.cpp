#include "Scene.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <QList>
#include <QFont>
#include <stdlib.h>
#include <QMetaType>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QPalette>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QFile>
#include <QDir>
Scene::Scene(QObject *parent,Score *score, int Round, int number)
    : QGraphicsScene{parent}
{
    sc = score;

    // new出Eagle
    eagle = new Eagle();
    eagle->setPos(0-eagle->boundingRect().width()/2+2,300-eagle->boundingRect().height());
    addItem(eagle);
    eagle->setZValue(1); //使Eagle always在前景

    // set number of player
    number_of_player = number ;
    qDebug() << "number of player" << number_of_player;
    //create a file store current data one player round 1
    QString desktopPath = QDir::homePath() + "/Desktop/";
    qDebug() << "destopPath:" << desktopPath;
    QFile fHistoryOnePlayerR1(desktopPath+"P1R1.txt");
    QFile fHistoryTwoPlayerR1(desktopPath+"P2R1.txt");
    QFile fHistoryOnePlayerR2(desktopPath+"P1R2.txt");
    QFile fHistoryTwoPlayerR2(desktopPath+"P2R2.txt");
    QString line;


    // the code below is used to check whether there is a file exist to resume the game .
    // if there is not any record , start a new game

    if (Round == 1){
        Round1Scene();
        if(number_of_player==1){
            player_1 = new Player();
            player_1->setnumber(1);
            player_2 = new Player();
            if(fHistoryOnePlayerR1.exists()){
                if (fHistoryOnePlayerR1.open(QIODevice::ReadOnly | QIODevice::Text)) {
                    QTextStream in(&fHistoryOnePlayerR1);

                    p1life = in.readLine();
                    enemylife = in.readLine();
                    player_1->resetlife(p1life.toInt());
                    setenemy(enemylife.toInt());
                    setplayerlife(player_1);

                    fHistoryOnePlayerR1.close();
                    qDebug() << "open file P1R1";
                } else {
                    qDebug() << "Failed to open the file P1R1 for reading.";
                }
            }else{
                setplayerlife(player_1);
                setenemy(20);
                qDebug() << "player1 initiated round1";
            }
        }else{
            player_1 = new Player();
            player_2 = new Player();
            player_1->setnumber(1);
            player_2->setnumber(2);
            if(fHistoryTwoPlayerR1.exists()){
                if (fHistoryTwoPlayerR1.open(QIODevice::ReadOnly | QIODevice::Text)) {
                    QTextStream in(&fHistoryTwoPlayerR1);
                    p1life = in.readLine();
                    p2life = in.readLine();
                    enemylife = in.readLine();
                    fHistoryTwoPlayerR1.close();
                    player_1->resetlife(p1life.toInt());
                    player_2->resetlife(p2life.toInt());
                    setplayerlife(player_1);
                    setplayerlife(player_2);
                    setenemy(enemylife.toInt());
                    qDebug() << "open file P2R1";
                } else {
                    qDebug() << "Failed to open the file P2R1 for reading.";
                }
            }else{
                setplayerlife(player_1);
                qDebug() << "set up player1 life round1";
                setplayerlife(player_2);
                qDebug() << "set up player2 life round1";
                setenemy(20);
            }
        }
    } else if (Round == 2){
        Round2Scene();
        if(number_of_player==1){
            player_1 = new Player();
            player_1->setnumber(1);
            player_2 = new Player();
            if(fHistoryOnePlayerR2.exists()){
                if (fHistoryOnePlayerR2.open(QIODevice::ReadOnly | QIODevice::Text)) {
                    QTextStream in(&fHistoryOnePlayerR2);

                    p1life = in.readLine();
                    enemylife = in.readLine();
                    player_1->resetlife(p1life.toInt());
                    setenemy(enemylife.toInt());
                    setplayerlife(player_1);

                    fHistoryOnePlayerR2.close();
                    qDebug() << "open file P1R2";
                } else {
                    qDebug() << "Failed to open the file P1R2 for reading.";
                }
            }else{
                setplayerlife(player_1);
                setenemy(20);
                qDebug() << "player1 initiated round2";
            }
        }else{
            player_1 = new Player();
            player_2 = new Player();
            player_1->setnumber(1);
            player_2->setnumber(2);
            if(fHistoryTwoPlayerR2.exists()){
                if (fHistoryTwoPlayerR2.open(QIODevice::ReadOnly | QIODevice::Text)) {
                    QTextStream in(&fHistoryTwoPlayerR2);

                    p1life = in.readLine();
                    p2life = in.readLine();
                    enemylife = in.readLine();
                    player_1->resetlife(p1life.toInt());
                    player_2->resetlife(p2life.toInt());
                    setplayerlife(player_1);
                    setplayerlife(player_2);
                    setenemy(enemylife.toInt());
                    fHistoryTwoPlayerR2.close();
                    qDebug() << "open file P2R2";
                } else {
                    qDebug() << "Failed to open the file P2R2 for reading.";
                }
            }else{
                setplayerlife(player_1);
                qDebug() << "set up player1 life round2";
                setplayerlife(player_2);
                qDebug() << "set up player2 life round2";
                setenemy(20);
            }
        }
    }

    if(number_of_player==1){   //one-player 模式
        //show one player life
        QGraphicsTextItem *tex = new QGraphicsTextItem("Life:");
        QFont fon("Arial",32);
        tex->setFont(fon);
        tex->setDefaultTextColor(Qt::white);
        tex->setZValue(2);
        tex->setPos(480,-150);
        addItem(tex);

        player_1->setPixmap(QPixmap(":/images/player.png").scaled(30,30,Qt::KeepAspectRatio));
        player_1->setPos(100,250);
        addItem(player_1);
        player_1->setZValue(1);//使player always在前景
    }else{    //two-player 模式
        //show player1 life
        QGraphicsTextItem *tex1 = new QGraphicsTextItem("Life1:");
        QFont fon1("Arial",32);
        tex1->setFont(fon1);
        tex1->setDefaultTextColor(Qt::white);
        tex1->setZValue(2);
        tex1->setPos(480,-150);
        addItem(tex1);

        //show player2 life
        QGraphicsTextItem *tex2 = new QGraphicsTextItem("Life2:");
        QFont fon2("Arial",32);
        tex2->setFont(fon2);
        tex2->setDefaultTextColor(Qt::white);
        tex2->setZValue(2);
        tex2->setPos(480,50);
        addItem(tex2);

        player_1->setPixmap(QPixmap(":/images/player.png").scaled(30,30,Qt::KeepAspectRatio));
        player_1->setPos(100,250);
        addItem(player_1);
        player_1->setZValue(1);//使player always在前景

        player_2->setPixmap(QPixmap(":/images/player2.png").scaled(30,30,Qt::KeepAspectRatio));
        player_2->setPos(-120,250);
        addItem(player_2);
        player_2->setZValue(1);//使player always在前景
    }

    //new出enemy
    enemyCounter = 0 ;
    enemyTotal = 0 ;
    spawnEnemy() ;

    timer = new QTimer() ;
    connect(timer , &QTimer::timeout , this ,&Scene::spawnEnemy);
    timer->start(2000) ;

    // show the text of enemy life
    QGraphicsTextItem *texen = new QGraphicsTextItem("Enemy:");
    QFont fonen("Arial",32);
    texen->setFont(fonen);
    texen->setDefaultTextColor(Qt::white);
    texen->setZValue(2);
    texen->setPos(-600,-50);
    addItem(texen);
    qDebug() << "add enemy life" ;

    // create a button to pause
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
    qDebug() << "add  pause icon " ;

    //控制player的移動
    keyRespondTimer = new QTimer();
    keyRespondTimer->start(100);
    connect(keyRespondTimer,&QTimer::timeout, this, &Scene::player_move);
    qDebug() << "player move set up " ;

    // try
    skill = new Skill();
    skill->setPos(120,250);
    connect(this, &Scene::player_tank, this, &Scene::addOneLife);
    connect(this, &Scene::player_grenade, this, &Scene::grenadeBoom);
    connect(this, &Scene::player_helmet, this, &Scene::helmetProtect);
    connect(this, &Scene::player_shovel, this, &Scene::shovelChange);
    connect(this, &Scene::player_star, this, &Scene::playergetStar);
    connect(this, &Scene::player_timer, this, &Scene::enemyStop);
    addItem(skill);
    skill->setZValue(1);
}

void Scene::Round1Scene(){
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
    setEagleBrickWall();

}

void Scene::Round2Scene()
{
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
    setEagleBrickWall();
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

void Scene::setGrasswall(int grassFirst_x, int grassFirst_y, int num_x, int num_y)
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

void Scene::setRiver(int riverFirst_x, int riverFirst_y, int num_x, int num_y)
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

void Scene::setIce(int IceFirst_x, int IceFirst_y, int num_x, int num_y)
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

void Scene::setEagleBrickWall()
{
    QList<double> x = {0-brick->boundingRect().width()*2-10, 0-brick->boundingRect().width()*2-10, 51};
    QList<double> y = {217, 197, 217};
    QList<int> w = {1, 6, 1};
    QList<int> h = {4, 1, 4};
    for (int j = 0; j < 3; j++){
        double brickFirst_x = x[j];
        double brickFirst_y = y[j];
        int num_x = w[j];
        int num_y = h[j];
        for(int i=0;i<num_x;i++){
            int d=0;
            for(int j=0;j <num_y;j++){
                brick=new Brick();
                eagleBrick.append(brick);
                brick->setPos(brickFirst_x,brickFirst_y+d);
                d = d+brick->boundingRect().height()-17;
                addItem(brick);
                brick->setZValue(1);
            }
            brickFirst_x=brickFirst_x+brick->boundingRect().width()-10;
        }
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
    // this class is used to set up the display of player's life
    int m;
    m = player->getlife();
    if(player->getnumber()==1){
        textlifep1 = new QGraphicsTextItem(QString::number(m));
        QFont fontp1("Arial",32);
        textlifep1->setFont(fontp1);
        textlifep1->setDefaultTextColor(Qt::white);
        textlifep1->setPos(500,-100);
        textlifep1->setZValue(2);
        addItem(textlifep1);
        qDebug() << "set up player 1 life successfully";
    }else{
        textlifep2 = new QGraphicsTextItem(QString::number(m));
        QFont fontp2("Arial",32);
        textlifep2->setFont(fontp2);
        textlifep2->setDefaultTextColor(Qt::white);
        textlifep2->setPos(500,100);
        textlifep2->setZValue(5);
        addItem(textlifep2);
        qDebug() << "set up player 2 life successfully";
    }
}

void Scene::handleBrickDeleted(Bullet *bullet, Brick *brick){
    removeItem(bullet);
    delete bullet;
    removeItem(brick);
    delete brick;
}

void Scene::GameEndded(Bullet *bullet, Eagle *eagle) // if bullet shot eagle
{
    removeItem(bullet);
    delete bullet;
    removeItem(eagle);
    delete eagle;
    emit gameover();
    clear();
}

void Scene::enemyDestroy(Bullet *bullet, Enemy *enemy)
{
    if(enemy-> kindof == 4){
        Skill *skill = new Skill();
        skill->setPos(enemy->pos());
        connect(this, &Scene::player_tank, this, &Scene::addOneLife);
        connect(this, &Scene::player_grenade, this, &Scene::grenadeBoom);
        connect(this, &Scene::player_helmet, this, &Scene::helmetProtect);
        connect(this, &Scene::player_shovel, this, &Scene::shovelChange);
        connect(this, &Scene::player_star, this, &Scene::playergetStar);
        connect(this, &Scene::player_timer, this, &Scene::enemyStop);
        addItem(skill);
        skill->setZValue(1);
    }

    removeItem(bullet);
    delete bullet;

    if(enemy-> kindof == 1)//是armor坦克
    {
        armorlife--; //起始4條命 減1條
        if(armorlife !=0) //如果命還沒被減完就直接return，如果被減完，才會發生下面的事被delete
            return;
    }

    removeItem(enemy);
    delete enemy;

    enemyslain++;
    removeItem(textenemylife);
    setenemy(20-enemyslain);
    sc->setscore(enemyslain*100);
    qDebug() << "score:" << sc->getscore();
    qDebug() << "Enemyslain:"<<enemyslain;
    enemyCounter --;
    if(enemyslain == 20){
        emit gameover();
        clear();
    }
}

void Scene::loseOneLife(Bullet *bullet, Player *player)
{
    removeItem(bullet);
    delete bullet;

    qDebug() << "remove one life";

    if(player->getnumber()==1){
        player->setPos(100,250);
        player->setRotation(0);
        removeItem(textlifep1);
    }
    else{
        player->setPos(-120,250);
        player->setRotation(0);
        removeItem(textlifep2);
    }
    if(player->getlife()==0){
        emit gameover();
        clear();
    }
    player->setlife();
    setplayerlife(player);

}

void Scene::handleBulletDeleted(Bullet *bullet)
{
    removeItem(bullet);
    delete bullet;
}

void Scene::addOneLife(Player *player)
{
    player->addlife();
    if(player->getnumber()==1){
        removeItem(textlifep1);
    }else{
        removeItem(textlifep2);
    }
    setplayerlife(player);
}

void Scene::grenadeBoom()
{
    qDebug() << "Enemies:";
    int k = enemyslain;

    for(int i = enemies.length(); i > k; i--){
        Enemy *enemy = enemies[i-1];
        removeItem(enemy);
        delete enemy;
        qDebug() << i;
        enemyslain++;
        enemyCounter--;
        if(enemyslain == 20){
            break;
        }
    }
    removeItem(textenemylife);
    setenemy(20-enemyslain);
    sc->setscore(enemyslain*100);
    if(enemyslain == 20){
        emit gameover();
        clear();
    }

    update();
}

void Scene::helmetProtect(Player *player)
{
    player->setPixmap(QPixmap(":/images/protect.png").scaled(30,30,Qt::KeepAspectRatio));
    player->Protect();
    QTimer::singleShot(10000, [=]() {
        player->setPixmap(QPixmap(":/images/player.png").scaled(30,30,Qt::KeepAspectRatio));
    });
}

void Scene::shovelChange()
{
    for(Brick* brick : eagleBrick){
        // Check if the pointer is not null
        if(brick){
            brick -> setWall();
        }
    }
}

void Scene::playergetStar()
{
    bullet_faster = true;
    QTimer::singleShot(10000, [=]() {
        bullet_faster = false;
    });
}

void Scene::enemyStop()
{
    timerSkill = true;
    for(int i = enemies.length(); i > enemyslain; i--){
        Enemy *enemy = enemies[i-1];
        enemy ->stop();
    }
    QTimer::singleShot(10000, [=]() {
        timerSkill = false;
        for(int i = enemies.length(); i > enemyslain; i--){
            Enemy *enemy = enemies[i-1];
            enemy ->start();
        }
    });
}
//控制上下左右鍵使player可以上下左右移動(並且不可以撞到磚塊或牆壁)
void Scene::player_move()
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
            if(number_of_player==2 &&pos_2.x()>(-450)){                    //有兩個player時才會進入此條件
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
            if(number_of_player==2 && pos_2.x()<(420)){                      //有兩個player時才會進入此條件
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
        case Qt::Key_W:{
            if(number_of_player==2 &&pos_2.y()>(-300)){                       //有兩個player時才會進入此條件
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
            if(number_of_player==2 && pos_2.y()<(270)){                        //有兩個player時才會進入此條件
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
            if (bullet_faster == true){
                bullet ->timer->start(25) ;
            }
            connect(bullet, &Bullet::bulletHitsBrick, this, &Scene::handleBrickDeleted);
            connect(bullet, &Bullet::bulletHitsEagle, this, &Scene::GameEndded);
            connect(bullet, &Bullet::bulletHitsEnemy, this, &Scene::enemyDestroy);
            connect(bullet, &Bullet::bullet_bullet, this, &Scene::handleBulletDeleted);
            connect(this, &Scene::bulletStop, bullet, &Bullet::stop);
            connect(this, &Scene::bulletStart, bullet, &Bullet::start);
            bullet->setPos(player_1->pos());
            bullet->setRotation(player_1->rotation());
            bullet->setZValue(10);
            addItem(bullet);
            break;
        }
        case Qt::Key_Shift:{
            if(number_of_player==2){                     //有兩個player時才會進入此條件
                Bullet *bullet = new Bullet(true);
                if (bullet_faster == true){
                    bullet ->timer->start(25) ;
                }
                connect(bullet, &Bullet::bulletHitsBrick, this, &Scene::handleBrickDeleted);
                connect(bullet, &Bullet::bulletHitsEagle, this, &Scene::GameEndded);
                connect(bullet, &Bullet::bulletHitsEnemy, this, &Scene::enemyDestroy);
                connect(bullet, &Bullet::bullet_bullet, this, &Scene::handleBulletDeleted);
                connect(this, &Scene::bulletStop, bullet, &Bullet::stop);
                connect(this, &Scene::bulletStart, bullet, &Bullet::start);
                bullet->setPos(player_2->pos());
                bullet->setRotation(player_2->rotation());
                bullet->setZValue(10);
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
            Skill *skill = dynamic_cast<Skill*>(item);
            River *river = dynamic_cast<River*>(item);
            Player *player = dynamic_cast<Player*>(item);
            if(brick || wall || enemy ||river ||player){
                player_1->setPos(pos_1);
                //return;
            }else if (skill){ //grenade, helmet, shovel, star, tank, timer
                if (skill->getSkillType() == "grenade"){
                    emit player_grenade();
                }else if(skill->getSkillType() == "helmet"){
                    emit player_helmet(player_1);
                }else if(skill->getSkillType() == "shovel"){
                    emit player_shovel();
                }else if(skill->getSkillType() == "star"){
                    emit player_star();
                }else if(skill->getSkillType() == "tank"){
                    emit player_tank(player_1);
                }else if(skill->getSkillType() == "timer"){
                    emit player_timer();
                }else{
                    qDebug("skillType error");
                }
            removeItem(skill);
            delete skill;
        }
        if(number_of_player==2){                                //有兩個player時才會進入此條件
            QList<QGraphicsItem *> colliding_items_2 = player_2->collidingItems();
            foreach (QGraphicsItem* item,colliding_items_2) {
                Brick *brick = dynamic_cast<Brick*>(item);
                Wall *wall = dynamic_cast<Wall*>(item);
                Enemy *enemy = dynamic_cast<Enemy*>(item);
                Skill *skill = dynamic_cast<Skill*>(item);
                River *river = dynamic_cast<River*>(item);
                Player *player = dynamic_cast<Player*>(item);
                if(brick || wall || enemy || river || player) {
                    qDebug()<<"player";
                    player_2->setPos(pos_2);
                    //return;
                }else if (skill){ //grenade, helmet, shovel, star, tank, timer
                if (skill->getSkillType() == "grenade"){
                    emit player_grenade();
                }else if(skill->getSkillType() == "helmet"){
                    emit player_helmet(player_2);
                }else if(skill->getSkillType() == "shovel"){
                    emit player_shovel();
                }else if(skill->getSkillType() == "star"){
                    emit player_star();
                }else if(skill->getSkillType() == "tank"){
                    emit player_tank(player_2);
                }else if(skill->getSkillType() == "timer"){
                    emit player_timer();
                }else{
                    qDebug("skillType error");
                }
                removeItem(skill);
                delete skill;
                }
            }
        }
    }
}
}

void Scene::togglePause()
{
    // when the pause button is clicked , this class will be called to stop all the
    // animation and keypressevent of player , enemy and bullet
    isPaused = !isPaused;
    if (isPaused) {
        text->setPos(0,0);
        text->setZValue(5);
        addItem(text);
        qDebug("Game paused");
        // stop all
        keyRespondTimer->stop();
        timer->stop();
        emit bulletStop();
        for(int i = enemies.length(); i > enemyslain; i--){
        Enemy *enemy = enemies[i-1];
        enemy ->stop();
        }
    } else {
        // start all
        keyRespondTimer->start();
        timer->start();
        removeItem(text);
        qDebug("Game Resumed");
        emit bulletStart();
        for(int i = enemies.length(); i > enemyslain; i--){
            Enemy *enemy = enemies[i-1];
            enemy ->start();
        }
    }
}

void Scene::saveNowData(int Round)
{
    //this class is used to record the player's life and enenmy's life when player decides to quit during the game.
    QString desktopPath = QDir::homePath() + "/Desktop/";
    qDebug() << "destopPath:" << desktopPath;
    QFile fHistoryOnePlayerR1(desktopPath+"P1R1.txt");
    QFile fHistoryTwoPlayerR1(desktopPath+"P2R1.txt");
    QFile fHistoryOnePlayerR2(desktopPath+"P1R2.txt");
    QFile fHistoryTwoPlayerR2(desktopPath+"P2R2.txt");
    QString line;
    //the code below will distinguish the round and player at first then record the data into designated text file
    if(Round == 1){
        if(number_of_player==1){
            if (fHistoryOnePlayerR1.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
                QTextStream stream(&fHistoryOnePlayerR1);
                stream << player_1->getlife() << "\n";
                stream << (20-enemyslain) << "\n";
                fHistoryOnePlayerR1.close();

                qDebug() << "P1R1 stores successfully";
            } else {
                qDebug() << "P1R1 Failed to store the data";
            }
        }else{
            if (fHistoryTwoPlayerR1.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
                QTextStream stream(&fHistoryTwoPlayerR1);
                stream << player_1->getlife() << "\n";
                stream << player_2->getlife() << "\n";
                stream << (20-enemyslain) << "\n";
                fHistoryTwoPlayerR1.close();

                qDebug() << "P2R1 stores successfully";
            } else {
                qDebug() << "P2R1 Failed to store the data";
            }
        }
    }
    else{
        if(number_of_player==1){
            if (fHistoryOnePlayerR2.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
                QTextStream stream(&fHistoryOnePlayerR2);
                stream << player_1->getlife() << "\n";
                stream << (20-enemyslain) << "\n";
                fHistoryOnePlayerR2.close();

                qDebug() << "P1R2 stores successfully";
            } else {
                qDebug() << "P1R2 Failed to store the data";
            }
        }else{
            if (fHistoryTwoPlayerR2.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
                QTextStream stream(&fHistoryTwoPlayerR2);
                stream << player_1->getlife() << "\n";
                stream << player_2->getlife() << "\n";
                stream << (20-enemyslain) << "\n";
                fHistoryTwoPlayerR2.close();

                qDebug() << "P2R2 stores successfully";
            } else {
                qDebug() << "P2R2 Failed to store the data";
            }
        }
}
}
void Scene::spawnEnemy()
{
    int a = rand() % 12;
    if(!isPaused){
        if(enemyslain >= 17) //擊殺20個enemy就獲勝，所以擊殺16個enemy之後就不新增enemy了
            return;
        if(enemyCounter >= 4) //同時在場的enemy最多4個
            return;

        enemyTotal++;

        if (enemyTotal % 4 != 0) //不是SpecialEnemy，有可能為一般enemy、armor_tank、fast_tank、power_tank，使一般enemy的出現機率為75%
        {
            if(a == 0) // armor
            {
                enemyCounter++;
                Enemy *enemy = new Enemy(nullptr,1);
                enemies.append(enemy);
                enemy->setPos(rand()%870-450 , -250 );
                addItem(enemy);
                enemy->setZValue(1);//使enemy always在前景
                qDebug() << "Counter:"<<enemyCounter;
            }
            else if(a == 1) // fast
            {
                enemyCounter++;
                Enemy *enemy = new Enemy(nullptr,2);
                enemies.append(enemy);
                enemy->setPos(rand()%870-450 , -250 );
                addItem(enemy);
                enemy->setZValue(1);//使enemy always在前景
                qDebug() << "Counter:"<<enemyCounter;
            }
            else if(a == 2) // power
            {
                enemyCounter++;
                Enemy *enemy = new Enemy(nullptr,3);
                enemies.append(enemy);
                enemy->setPos(rand()%870-450 , -250 );
                addItem(enemy);
                enemy->setZValue(1);//使enemy always在前景
                qDebug() << "Counter:"<<enemyCounter;
            }
            else // 一般
            {
                enemyCounter++;
                Enemy *enemy = new Enemy(nullptr,0);
                enemies.append(enemy);
                enemy->setPos(rand()%870-450 , -250 );
                addItem(enemy);
                enemy->setZValue(1);//使enemy always在前景
                qDebug() << "Counter:"<<enemyCounter;
            }

        }
        if (enemyTotal % 4 == 0)//是SpecialEnemy
        {
            enemyCounter++;
            Enemy *enemy = new Enemy(nullptr,4);
            enemies.append(enemy);
            enemy->setPos(rand()%870-450 , -250 );
            addItem(enemy);
            enemy->setZValue(1);//使enemy always在前景
            qDebug() << "Counter:"<<enemyCounter;
        }
        qDebug() << "enemyTotal:"<<enemyTotal;
    }

}


void Scene::keyPressEvent(QKeyEvent *event){  //當按鍵按下
    if(!isPaused){
        if(!event->isAutoRepeat())
            keys.append(event->key());  //若非長按時自動觸發的按下，就將key值加入容器
        if(!keyRespondTimer->isActive())
            keyRespondTimer->start(100);  //若定時器不在運行，就啟動它
    }
}

void Scene::keyReleaseEvent(QKeyEvent *event){ //當按鍵釋放
    if(!isPaused){
        if(!event->isAutoRepeat())
        {keys.removeAll(event->key());}  //若非長按時自動觸發的釋放，就將key值從容器中刪除
        if(keys.isEmpty())
        {keyRespondTimer->stop();} //若容器空了，則關閉定時器
    }
}

