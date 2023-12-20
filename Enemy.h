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
    qreal rotation() const;
    void rotate_to();
    void stop10sec();

public slots: //slots function
    void move();
    void shootBullet(); // Enemy will randomly call shootBullet()

signals :

private:
    QTimer *timer ;
    QTimer *shootTimer;
    QTimer *rotation_timer;
    int counter ;
    qreal m_rotation;


};
#endif // ENEMY_H
