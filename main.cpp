#include "mainwindow.h"

#include <QApplication>
#include <QStandardPaths>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NoteContext defaultContext(QUrl(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)), "My Notes");
    MainWindow w(defaultContext);
    w.show();
    return a.exec();
}
