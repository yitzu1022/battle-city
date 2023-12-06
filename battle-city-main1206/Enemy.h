#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include "Brick.h"
#include "Wall.h"



class Enemy : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Enemy(QObject *parent = nullptr);
    void setRotation(qreal newRotation);

public slots: //slots function
    void move();
signals :
    void enemyHitsTheWall (Enemy *enemy , Wall *wall ) ;
    void enemyHitsTheBrick (Enemy *enemy ,Brick *brick) ;
    void enemyHitsTheEnemy (Enemy *enemy ,Enemy *otherenemy) ;

private:
    QTimer *timer ;
    int counter ;


};
#endif // ENEMY_H
