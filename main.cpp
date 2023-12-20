#include "widget.h"
#include "Start.h"
#include <QApplication>
#include "Score.h"

int highestscore=0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Start s;
    s.show();
    //Score s;
    //s.show();
    return a.exec();
}
