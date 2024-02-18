#ifndef START_H
#define START_H

#include <QWidget>
#include "Startscene.h"
#include "ChooseRound.h"
namespace Ui {
class Start;
}

class Start : public QWidget
{
    Q_OBJECT

public:
    explicit Start(QWidget *parent = nullptr);
    void Close();
    void Close2();
    ~Start();
    ChooseRound *c;


private:
    Ui::Start *ui;
    StartScene *scene;


};

#endif // START_H
