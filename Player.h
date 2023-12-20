#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>



class Player : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);
    qreal rotation() const;
    void setRotation(qreal newRotation);
    bool isProtect(){return protect;}
    void Protect();

signals:

private:
    qreal m_rotation;
    bool protect;
};

#endif // PLAYER_H
