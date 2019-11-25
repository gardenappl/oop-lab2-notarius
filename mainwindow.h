#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <editor/noteeditor.h>
#include <notes/notecontext.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(NoteContext context, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void import();
    void save();

private:
    NoteEditor* open(QUrl uri);

    const QString defaultFolderName = "My Notes";

    NoteContext currentContext;


    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
