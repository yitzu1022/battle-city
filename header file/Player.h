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
    void setlife(); // minus one life
    void resetlife(int plife);
    void addlife();
    int getlife();
    void setnumber(int n);
    int getnumber();

signals:

private:
    qreal m_rotation;
    bool protect = false;
    int life=3;
    int number; //註明是player1還是2
};

#endif // PLAYER_H
