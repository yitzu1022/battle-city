#ifndef SECONDWIDGET_H
#define SECONDWIDGET_H

#include <QWidget>
#include <SecondScene.h>
namespace Ui {
class SecondWidget;
}

class SecondWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SecondWidget(QWidget *parent = nullptr);
    ~SecondWidget();

private:
    Ui::SecondWidget *ui;
    SecondScene *scene;
};

#endif // SECONDWIDGET_H
