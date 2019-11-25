#include "noteeditor.h"
#include "ui_noteeditor.h"

NoteEditor::NoteEditor(QUrl url, QWidget *parent) :
    QFrame(parent),
    tabInfo(EditorTab(url, url.fileName())),
    ui(new Ui::NoteEditor)
{
    ui->setupUi(this);
}

NoteEditor::~NoteEditor()
{
    delete ui;
}

QString NoteEditor::getName()
{
    return tabInfo.name;
}

QUrl NoteEditor::getUri()
{
    return tabInfo.uri;
}

QTextEdit* NoteEditor::getEditor()
{
    return ui->textEdit;
}
