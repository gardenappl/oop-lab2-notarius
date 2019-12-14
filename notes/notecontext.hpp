#ifndef NOTECONTEXT_HPP
#define NOTECONTEXT_HPP

#include <QDateTime>
#include <QScopedPointer>
#include <QUrl>
#include <memory>
#include <vector>
#include <unordered_map>

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
     * \return whether or not the loading was successful
     */
    bool init();

    /*!
     * \brief Save the state of this context to disk.
     * \return whether or not the save was successful
     */
    bool save();

    /*!
     * Return the URL of the file which contains this particular note.
     * This assumes that the note is contained within this context.
     * \param note a note
     * \return the URL of the folder which contains this context, and the note's file name appended to it.
     */
    QString getPath(const Note& note);
    /*!
     * \brief return the URL of the folder which contains this context.
     * \return a folder URL
     */
    QString getPath();

    /*!
     * \brief return a pointer to a constant map of this context's notes
     * \return a pointer to the context's notes
     */
    const std::unordered_map<size_t, Note>* getNotes();

    /*!
     * \brief Add a note to this context. The note's name must be unique within this context.
     * \param note a new note
     * \throws std::invalid_argument if the context contains a note with the same name.
     * \returns the ID of the note within the array.
     */
    size_t addNote(Note newNote);

    /*!
     * \brief Get an instance of a Note associated with a given ID.
     * \param id an index
     * \return the associated Note
     * \throws std::invalid_argument if no note exists with such an ID
     */
    Note getNoteByID(size_t id);

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

    /*!
     * \brief Get an ID that's not taken by any Note instance.
     * \return a new ID
     */
    size_t getNextAvailableID();

private:
    /*!
     * \brief Get the path to the folder in which all Notarius contexts are stored.
     * \return the storage folder's path URL.
     */
    static QString getStorageFolderPath();

    /*!
     * \brief a list of notes, associated with an ID
     */
    std::unordered_map<size_t, Note> notes;

    /*!
     * \brief creationDate the time and date of this context's creation
     */
    QDateTime creationDate;
};

#endif // NOTECONTEXT_HPP
