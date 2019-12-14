#include "noteeditor.hpp"
#include "ui_noteeditor.h"

NoteEditor::NoteEditor(NoteContext *context, size_t noteID, QWidget *parent) :
    QFrame(parent),
    noteID(noteID),
    context(context),
    ui(new Ui::NoteEditor)
{
    ui->setupUi(this);
}

NoteEditor::~NoteEditor()
{
    delete ui;
}

Note NoteEditor::getNoteInfo()
{
    return context->getNoteByID(noteID);
}

QString NoteEditor::getName()
{
    return getNoteInfo().name;
}

QTextEdit* NoteEditor::getEditor()
{
    return ui->textEdit;
}
