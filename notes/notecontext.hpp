#ifndef NOTECONTEXT_HPP
#define NOTECONTEXT_HPP

#include <QDateTime>
#include <QScopedPointer>
#include <QUrl>
#include <memory>

#include <notes/note.hpp>



struct NoteContext
{
public:
    /*!
     * \brief the display name of the context.
     */
    QString name;
    /*!
     * \brief A default constructor with no display name or URL.
     */
    NoteContext() = default;

    /*!
     * \brief Create a NoteContext with a given display name.
     * \param name the display name of the context.
     */
    NoteContext(QString name);
    ~NoteContext() = default;

    /*!
     * \brief Populate the NoteContext's fields based on the data that's stored on the device.
     */
    void init();

    /*!
     * \brief Save the state of this context to disk.
     */
    void save();

    /*!
     * Return the URL of the file which contains this particular note.
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

    /*!
     * \brief Add a note to this context. The note's name must be unique within this context.
     * \param note a new note
     * \throws std::invalid_argument if the context contains a note with the same name.
     */
    void addNote(Note newNote);

    /*!
     * \brief Set the date of this context's creation.
     * \param dateTime the creation date
     */
    void setCreationDate(QDateTime dateTime);
    /*!
     * \brief Get the date of this context's creation.
     * \return the creation date
     */
    QDateTime getCreationDate();

private:
    /*!
     * \brief Get the path to the folder in which all Notarius contexts are stored.
     * \return the storage folder's path URL.
     */
    static QString getStorageFolderPath();

    /*!
     * \brief a list of notes
     */
    std::vector<Note> notes;

    QDateTime creationDate;
};

#endif // NOTECONTEXT_HPP
