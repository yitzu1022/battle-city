#ifndef CHOOSEROUND_H
#define CHOOSEROUND_H

#include <QWidget>
#include "ChooseScene.h"
#include "widget.h"
#include "Secondwidget.h"
namespace Ui {
class ChooseRound;
}

class ChooseRound : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseRound(int number=1);
    void Return();
    void Close();
    void OpenSecond();
    ~ChooseRound();
    int playernumber;

private:
    Ui::ChooseRound *ui;
    ChooseScene *scene;
    Widget *w;
    SecondWidget *s;

};

#endif // CHOOSEROUND_H
