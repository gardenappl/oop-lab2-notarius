#include "mainwindow.hpp"
#include "./ui_mainwindow.h"
#include "editor/noteeditor.hpp"

#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QStringList>
#include <QProcess>
#include <QStandardPaths>
#include <QTextStream>
#include <iostream>


MainWindow::MainWindow(NoteContext context, QWidget *parent)
    : QMainWindow(parent),
      currentContext(context),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->tabWidget);

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::import);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::save);
    connect(ui->actionNew_Context, &QAction::triggered, this, &MainWindow::createNewContext);

    std::cout << "current context name: " << context.name.toStdString() << std::endl;
    setWindowTitle("Notarius - " + context.name);
}



MainWindow::~MainWindow()
{
    delete ui;
}

NoteEditor* MainWindow::open(QUrl url)
{
    for(int i = 0; i < ui->tabWidget->count(); i++)
    {
        NoteEditor* editor = (NoteEditor*)ui->tabWidget->widget(i);
        std::cout << "Current widget URL:" << currentContext.getPath(editor->getNoteInfo()).toStdString() << std::endl;
        std::cout << "Open URL:" << url.path().toStdString() << std::endl;
        if(QUrl(currentContext.getPath(editor->getNoteInfo())) == url)
        {
            std::cout << "Equal" << std::endl;
            ui->tabWidget->setCurrentIndex(i);
            return editor;
        }
    }
    Note* note = new Note(url.fileName());
    NoteEditor* editor = new NoteEditor(note);
    ui->tabWidget->addTab(editor, editor->getName());
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    return editor;
}

void MainWindow::import()
{
    QUrl fileURL = QFileDialog::getOpenFileUrl(this, tr("Open the file"));
    QFile file(fileURL.path());
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Warning"), tr("Cannot open file: ") + file.errorString());
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();

    NoteEditor* editor = open(fileURL);
    editor->getEditor()->setText(text);
    file.close();
}

void MainWindow::save()
{
    if(ui->tabWidget->currentIndex() == -1)
        return;

    NoteEditor* currentEditor = (NoteEditor*)(ui->tabWidget->currentWidget());
    QUrl fileUrl(currentContext.getPath(currentEditor->getNoteInfo()));
    std::cout << "Saving to URL: " << fileUrl.path().toStdString() << std::endl;

    //Make sure folder exists
    QDir dirUrl(currentContext.getPath());
    dirUrl.mkpath(".");

    QFile file(fileUrl.path());
    if (!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Warning"), tr("Cannot save file: ") + file.errorString());
        return;
    }
    QTextStream out(&file);
    QString text = currentEditor->getEditor()->toPlainText();
    out << text;
    file.close();
}

void MainWindow::createNewContext()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Create new context"), tr("Enter context name: "),
                                         QLineEdit::Normal, tr("My Notes"), &ok);

    std::cout << text.toStdString() << std::endl;
    QProcess process;
    process.setProgram("notarius");
    process.setArguments(QStringList() << "--context" << text);
    process.startDetached();
}
