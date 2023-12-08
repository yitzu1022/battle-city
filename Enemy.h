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
<<<<<<< HEAD
    qreal rotation() const;
=======
>>>>>>> ca69e8e2c571cfcdcb483cf913a4679b793fcf82

public slots: //slots function
    void move();
    void shootBullet(); // Enemy will randomly call shootBullet()

signals :

private:
    QTimer *timer ;
    QTimer *shootTimer;
    int counter ;
<<<<<<< HEAD
    qreal m_rotation;
=======
>>>>>>> ca69e8e2c571cfcdcb483cf913a4679b793fcf82


};
#endif // ENEMY_H
