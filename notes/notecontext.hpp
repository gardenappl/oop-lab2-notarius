#ifndef NOTECONTEXT_HPP
#define NOTECONTEXT_HPP

#include <QScopedPointer>
#include <QUrl>
#include <memory>

#include <notes/note.hpp>



struct NoteContext
{
public:
    QUrl url;
    QString name;
    //QVector<QScopedPointer<Note>> notes;

    NoteContext(QUrl url, QString name);
    ~NoteContext() = default;

    void init();
    /*!
     * \brief getUrl return the URL of the file which contains this particular note.
     * This assumes that the note is contained within this context.
     * \param note a note
     * \return the URL of the folder which contains this context, and the note's file name appended to it.
     */
    QUrl getUrl(Note* note);
    /*!
     * \brief getUrl return the URL of the folder which contains this context.
     * \return a folder URL
     */
    QUrl getUrl();
};

#endif // NOTECONTEXT_HPP
