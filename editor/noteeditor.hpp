#ifndef NOTEEDITOR_H
#define NOTEEDITOR_H

#include "notes/note.hpp"

#include <QFrame>
#include <QTextEdit>

#include <notes/notecontext.hpp>

namespace Ui {
class NoteEditor;
}

class NoteEditor : public QFrame
{
    Q_OBJECT
    size_t noteID;
    NoteContext* context;

public:
    explicit NoteEditor(NoteContext* context, size_t noteID, QWidget *parent = nullptr);
    ~NoteEditor();

    QString getName();
    Note getNoteInfo();
    QTextEdit* getEditor();

private:
    Ui::NoteEditor *ui;
};

#endif // NOTEEDITOR_H
