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

    /*!
     * \brief Get the name of the note that's opened in this editor.
     * \return name of the note
     */
    QString getName();
    /*!
     * \brief Get an instance of the note that's opened in this editor.
     * \return the note instance
     */
    Note getNoteInfo();
    /*!
     * \brief Get an instance of the QTextEdit widget that's used by this editor.
     * \return the widget
     */
    QTextEdit* getEditor();

private:
    Ui::NoteEditor *ui;
};

#endif // NOTEEDITOR_H
