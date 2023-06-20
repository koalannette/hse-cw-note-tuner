#include "mainwindow.h"

#include <QApplication>
#include <bass.h>

int main(int argc, char *argv[])
{
    if (!BASS_Init(-1, 44100, 0, nullptr, nullptr)) {
        return 1;
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
