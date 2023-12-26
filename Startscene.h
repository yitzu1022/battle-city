#ifndef STARTSCENE_H
#define STARTSCENE_H

#include <QObject>
#include <QGraphicsScene>
class StartScene : public QGraphicsScene
{
   Q_OBJECT
public:
    StartScene(QObject *parent = nullptr);
public slots:
    void CloseScene();
};

#endif // STARTSCENE_H
