#ifndef NOTECONTEXT_HPP
#define NOTECONTEXT_HPP

#include <QScopedPointer>
#include <QUrl>
#include <memory>

#include <notes/note.hpp>



struct NoteContext
{
public:
    /*!
     * \brief the directory in which this context's notes are stored.
     */
    QUrl url;
    /*!
     * \brief the display name of the context.
     */
    QString name;
    /*!
     * \brief a list of notes
     */
    std::vector<Note> notes;

    NoteContext(QUrl url, QString name);
    ~NoteContext() = default;

    /*!
     * \brief populate the NoteContext's fields based on the data that's stored on the device.
     */
    void init();
    /*!
     * \brief return the URL of the file which contains this particular note.
     * This assumes that the note is contained within this context.
     * \param note a note
     * \return the URL of the folder which contains this context, and the note's file name appended to it.
     */
    QString getPath(Note* note);
    /*!
     * \brief return the URL of the folder which contains this context.
     * \return a folder URL
     */
    QString getPath();
};

#endif // NOTECONTEXT_HPP
