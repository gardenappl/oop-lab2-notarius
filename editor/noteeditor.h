#ifndef NOTEEDITOR_H
#define NOTEEDITOR_H

#include "editortab.h"

#include <QFrame>
#include <QTextEdit>

namespace Ui {
class NoteEditor;
}

class NoteEditor : public QFrame
{
    Q_OBJECT
    EditorTab tabInfo;

public:
    explicit NoteEditor(QUrl url, QWidget *parent = nullptr);
    ~NoteEditor();

    QUrl getUri();
    QString getName();
    QTextEdit* getEditor();

private:
    Ui::NoteEditor *ui;
};

#endif // NOTEEDITOR_H
