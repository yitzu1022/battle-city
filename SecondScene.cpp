#include "SecondScene.h"
#include <QGraphicsScene>

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
