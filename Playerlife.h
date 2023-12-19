#ifndef PLAYERLIFE_H
#define PLAYERLIFE_H

#include <QWidget>

namespace Ui {
class PlayerLife;
}

class PlayerLife : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerLife(QWidget *parent = nullptr);
    ~PlayerLife();
    int getlife();
    void setlife(int x);

private:
    Ui::PlayerLife *ui;
    int life;
};

#endif // PLAYERLIFE_H
