#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>
#include <QTextStream>
#include <iostream>

#include <editor/noteeditor.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->tabWidget);

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::import);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::save);
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
        if(editor->getUri() == url)
        {
            ui->tabWidget->setCurrentIndex(i);
            return editor;
        }
    }
    NoteEditor* editor = new NoteEditor(url);
    ui->tabWidget->addTab(editor, editor->getName());
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    return editor;
}

void MainWindow::import()
{
    QUrl fileURL = QFileDialog::getOpenFileUrl(this, tr("Open the file"));
    QFile file(fileURL.path());
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
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
    QUrl fileUrl(currentEditor->getUri());
    std::cout << "Saving to URL: " << fileUrl.path().toStdString() << std::endl;
    QFile file(fileUrl.path());
    if (!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    QString text = currentEditor->getEditor()->toPlainText();
    out << text;
    file.close();
}
