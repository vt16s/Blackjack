#include "mainwindow.h"
#include <QSound>
#include <QApplication>

int main(int argc, char *argv[])
{
    // Random generator initialization
    srand(static_cast<unsigned int>(time(0)));
    rand();

    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    QSound::play(":/wav/sound/begin.wav");
    QApplication::processEvents();

    return a.exec();
}
