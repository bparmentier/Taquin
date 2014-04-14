#include "mwtaquin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MWTaquin w;
    w.show();

    return a.exec();
}
