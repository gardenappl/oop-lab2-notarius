#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <editor/noteeditor.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void import();
    void save();

private:
    NoteEditor* open(QUrl uri);

    const QString defaultFolderName = "My Notes";
    Ui::MainWindow *ui;
    QUrl currentWorkspaceFolder;
};
#endif // MAINWINDOW_H
