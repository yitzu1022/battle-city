#ifndef ENEMYLIFE_H
#define ENEMYLIFE_H

#include <QWidget>
namespace Ui {
class EnemyLife;
}

class EnemyLife : public QWidget
{
    Q_OBJECT

public:
    explicit EnemyLife(QWidget *parent = nullptr);
    ~EnemyLife();
    int getlife();
    void setlife(int x);
    void time();
private:
    Ui::EnemyLife *ui;
    int life=20;
};

#endif // ENEMYLIFE_H
