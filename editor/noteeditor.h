#ifndef NOTEEDITOR_H
#define NOTEEDITOR_H

#include "notes/note.hpp"

#include <QFrame>
#include <QTextEdit>

namespace Ui {
class NoteEditor;
}

class NoteEditor : public QFrame
{
    Q_OBJECT
    Note* noteInfo;

public:
    explicit NoteEditor(Note* noteInfo, QWidget *parent = nullptr);
    ~NoteEditor();

    QString getName();
    Note* getNoteInfo();
    QTextEdit* getEditor();

private:
    Ui::NoteEditor *ui;
};

#endif // NOTEEDITOR_H
