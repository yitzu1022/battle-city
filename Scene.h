#ifndef SCENE_H
#define SCENE_H
#include <QGraphicsScene>
#include <QObject>
#include "Eagle.h"
#include "Brick.h"
#include "Wall.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    void setBrickwall(int brickFirst_x,int brickFirst_y,int num_x,int num_y);

signals:

private:
    Eagle *eagle;
    Brick *brick;
    Brick *brickFirst;
    Wall *wall;

};

#endif // SCENE_H
