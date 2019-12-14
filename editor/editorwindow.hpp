#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <memory>
#include <vector>
#include <editor/noteeditor.hpp>
#include <notes/notecontext.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


/*!
 * \brief The EditorWindow is the actual editor window for a given note context.
 */
class EditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Creates an editor window within the given NoteContext
     * \param context a note context that the user will be working with.
     * \param parent an optional parent widget.
     */
    EditorWindow(NoteContext context, QWidget *parent = nullptr);
    ~EditorWindow();

    /*!
     * \brief Get the path to the folder in which all Notarius contexts are stored.
     * \return the storage folder's path URL.
     */
    static QString getNotesFolder();

private slots:
//    /*!
//     * \brief Open a file and import that as a note. The note's name will be the same as the file name, with a suffix
//     * appended if a note with the same name already exists within the current context.
//     */
//    void import();
    /*!
     * \brief Prompts the user to choose a name, creates an empty note of that name and adds it to the current context.
     */
    void saveCurrentNote();
    /*!
     * \brief Prompts the user to choose a name, creates an empty context with that name and opens a new instance of Notarius.
     */
    void createNewContext();
    /*!
     * \brief Prompts the user to choose a name, creates an empty note with that name and adds it to the current context.
     */
    void createNewNote();

    /*!
     * Exports the entire current note context as a single text file,
     * prompts the user to enter its file and location.
     */
    void exportContextAsFile();


private:
    /*!
     * \brief Open a tab with a TabEditor for a given Note. Will create a TabEditor object if one doesn't exist for this note.
     * \param note a note that the user wants to edit
     * \return a NoteEditor pointer
     * \throw std::invalid_argument if the current context does not contain this note
     */
    NoteEditor* open(Note& note);

    /*!
     * \brief Open a new instance of Notarius with the given context.
     * \param context the name of the context
     * \param firstTime whether this is context was just created for the first time.
     * \return a NoteEditor pointer
     */
    void openContext(QString context, bool firstTime);

    /*!
     * \brief Create a NoteEditor for a given ID and read the appropriate Note's content from disk.
     * \param id the ID of a note.
     * \return a NoteEditor pointer
     * \throw std::invalid_argument if the current context does not contain a note with this ID
     */
    NoteEditor* load(size_t id);

    /*!
     * \brief The name of the default context.
     */
    const QString defaultContextName = "My Notes";

    /*!
     * \brief the context which the current user is working with.
     */
    NoteContext currentContext;

    /*!
     * \brief contains all currently open NoteEditors
     */
    std::vector<NoteEditor*> editors;

    /*!
     * \brief Get a vector containing a few recently created/edited contexts.
     * \return a vector of names of recent contexts
     */
    QStringList getRecentContexts();

//    /*!
//     * \brief The actions of the Open Recent... menu
//     */
//    QMenu recentContextsMenu;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
