#ifndef CHOOSEROUND_H
#define CHOOSEROUND_H

#include <QWidget>
#include "ChooseScene.h"
#include "widget.h"

namespace Ui {
class ChooseRound;
}

class ChooseRound : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseRound(QWidget *parent = nullptr);
    void Return();
    void Close();
    ~ChooseRound();

private:
    Ui::ChooseRound *ui;
    ChooseScene *scene;
    Widget *w;

};

#endif // CHOOSEROUND_H
