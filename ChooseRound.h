#ifndef CHOOSEROUND_H
#define CHOOSEROUND_H

#include <QWidget>
#include "ChooseScene.h"
#include "widget.h"
#include "Scene.h"
namespace Ui {
class ChooseRound;
}

class ChooseRound : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseRound(int number=1);
    void Return();
    void OpenRound1();
    void OpenRound2();
    ~ChooseRound();
    int playernumber;

private:
    Ui::ChooseRound *ui;
    ChooseScene *scene;
    Scene *gameScene;
    Widget *w;

};

#endif // CHOOSEROUND_H
