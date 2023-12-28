#ifndef SCORE_H
#define SCORE_H

#include <QWidget>
#include "ScoreScene.h"
#include <QFile>
namespace Ui {
class Score;
}

class Score : public QWidget
{
    Q_OBJECT

public:
    explicit Score(QWidget *parent = nullptr);
    void setup(int Round);
    int getscore();
    void setscore(int x);
    ~Score();
    int highestR1=0;
    int highestR2=0;

private:
    Ui::Score *ui;
    int score=0;

    ScoreScene *scene;
    QGraphicsTextItem *text;
};

#endif // SCORE_H
