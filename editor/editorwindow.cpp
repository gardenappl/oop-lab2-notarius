#include "./editorwindow.hpp"
#include "./ui_editorwindow.h"
#include "editor/noteeditor.hpp"

#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QStringList>
#include <QProcess>
#include <QStandardPaths>
#include <QTextStream>
#include <iostream>


EditorWindow::EditorWindow(NoteContext context, QWidget *parent)
    : QMainWindow(parent),
      currentContext(context),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->tabWidget);

    //connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::import);
    connect(ui->actionSave, &QAction::triggered, this, &EditorWindow::saveCurrentNote);
    connect(ui->actionNew_Context, &QAction::triggered, this, &EditorWindow::createNewContext);
    connect(ui->actionNew_Note, &QAction::triggered, this, &EditorWindow::createNewNote);
    connect(ui->actionExport_Context_as_File, &QAction::triggered, this, &EditorWindow::exportContextAsFile);


    QStringList recentContexts = getRecentContexts();
    std::cout << "Contexts: " << recentContexts.size() << std::endl;
    for(int i = 0; i < recentContexts.size(); i++)
    {
        std::cout << recentContexts[i].toStdString() << std::endl;
        ui->menuOpen_Recent->addAction(new QAction(recentContexts[i]));
        connect(ui->menuOpen_Recent->actions()[i], &QAction::triggered, this,
                [=](){ openContext(recentContexts[i], false); });
    }


    setWindowTitle("Notarius - " + currentContext.name);
    currentContext.init();
    const auto* notes = currentContext.getNotes();
    std::cout << "Notes count: " << notes->size() << std::endl;
    for(const auto& pair : *notes)
    {
        std::cout << "Reading..." << QString::number(pair.first).toStdString() << std::endl;
        std::cout << "Name: ";
        std::cout.flush();
        std::cout << currentContext.getNoteByID(pair.first).name.toStdString() << std::endl;
        NoteEditor* editor = load(pair.first);
        ui->tabWidget->addTab(editor, editor->getName());
        editors.push_back(editor);
    }
    std::cout << "Read." << std::endl;
}



EditorWindow::~EditorWindow()
{
    for(const auto& editor: editors)
        delete editor;
    delete ui;
}

NoteEditor* EditorWindow::open(Note& note)
{
    for(int i = 0; i < ui->tabWidget->count(); i++)
    {
        NoteEditor* editor = (NoteEditor*)ui->tabWidget->widget(i);
        if(editor->getNoteInfo().name == note.name)
        {
            std::cout << "Equals" << std::endl;
            ui->tabWidget->setCurrentIndex(i);
            return editor;
        }
    }
    for(const auto& pair : *currentContext.getNotes())
    {
        if(pair.second.name == note.name)
            return load(pair.first);
    }
    throw std::invalid_argument("The current context does not contain this note");
}

void EditorWindow::openContext(QString context, bool firstTime)
{
    QProcess process;
    process.setProgram("notarius");
    QStringList arguments;
    arguments << "--context" << context;
    if(firstTime)
        arguments << "--new";
    process.setArguments(arguments);
    process.startDetached();
}

NoteEditor* EditorWindow::load(size_t id)
{
    NoteEditor* newEditor = new NoteEditor(&currentContext, id);

    QFile file(currentContext.getPath(currentContext.getNoteByID(id)));
    if(!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Warning"), tr("Cannot open file: ") + file.errorString());
    }
    QTextStream in(&file);

    QString text = in.readAll();
    newEditor->getEditor()->setText(text);

    ui->tabWidget->addTab(newEditor, newEditor->getName());
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    editors.push_back(newEditor);
    return newEditor;
}

//void MainWindow::import()
//{
//    QUrl fileURL = QFileDialog::getOpenFileUrl(this, tr("Open the file"));
//    QFile file(fileURL.path());
//    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
//        QMessageBox::warning(this, tr("Warning"), tr("Cannot open file: ") + file.errorString());
//        return;
//    }
//    QTextStream in(&file);
//    QString text = in.readAll();

//    NoteEditor* editor = open(fileURL);
//    editor->getEditor()->setText(text);
//    file.close();
//}

void EditorWindow::saveCurrentNote()
{
    if(!currentContext.save())
    {
        QMessageBox::warning(this, tr("Warning"), tr("Unable to save context"));
    }

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

void EditorWindow::createNewContext()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Create new context"), tr("Enter context name: "),
                                         QLineEdit::Normal, tr("My Notes"), &ok);

    if(!ok)
        return;

    std::cout << text.toStdString() << std::endl;
    openContext(text, true);
}

void EditorWindow::createNewNote()
{
    QString suggestedName = tr("Note ") + QString::number(currentContext.getNextAvailableID() + 1);
    bool ok;
    QString noteName = QInputDialog::getText(this, tr("Create new note"), tr("Enter note name: "),
                                         QLineEdit::Normal, suggestedName, &ok);

    if(!ok)
        return;

    Note newNote(noteName);
    size_t id = currentContext.addNote(newNote);
    NoteEditor* newEditor = new NoteEditor(&currentContext, id);
    editors.push_back(newEditor);
    ui->tabWidget->addTab(newEditor, newEditor->getName());
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
}

void EditorWindow::exportContextAsFile()
{
    QUrl fileUrl = QFileDialog::getSaveFileUrl(this, tr("Create a file to import to..."));
    if(fileUrl.isEmpty())
        return;
    QFile file(fileUrl.path());
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Warning"), tr("Cannot open file: ") + file.errorString());
        return;
    }
    QTextStream out(&file);

    QDir contextsDir = QDir(currentContext.getPath());
    QFileInfoList fileList = contextsDir.entryInfoList(QDir::Files, QDir::Time);
    for(int i = 0; i < fileList.size(); i++)
    {
        std::cout << fileList[i].filePath().toStdString() << std::endl;
        if(fileList[i].fileName() != "context.json")
        {
            out << "=====================\n";
            out << fileList[i].fileName() << ", " << fileList[i].metadataChangeTime().toString() << '\n';
            out << "=====================\n\n";

            QFile readFile(fileList[i].filePath());
            if (!readFile.open(QIODevice::ReadOnly | QFile::Text)) {
                QMessageBox::warning(this, tr("Warning"), tr("Cannot open file: ") + file.errorString());
                return;
            }
            out << readFile.readAll() << "\n\n";
        }
    }
}

QString EditorWindow::getNotesFolder()
{
    return QDir::cleanPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Notarius");
}

QStringList EditorWindow::getRecentContexts()
{
    QDir contextsDir = QDir(getNotesFolder());
    QStringList list = contextsDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Time);
    while(list.size() > 5)
        list.removeLast();
    return list;
}
