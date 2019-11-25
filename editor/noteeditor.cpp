#include "noteeditor.hpp"
#include "ui_noteeditor.h"

NoteEditor::NoteEditor(Note *noteInfo, QWidget *parent) :
    QFrame(parent),
    noteInfo(noteInfo),
    ui(new Ui::NoteEditor)
{
    ui->setupUi(this);
}

NoteEditor::~NoteEditor()
{
    delete ui;
}

Note* NoteEditor::getNoteInfo()
{
    return noteInfo;
}

QString NoteEditor::getName()
{
    return noteInfo->name;
}

QTextEdit* NoteEditor::getEditor()
{
    return ui->textEdit;
}
