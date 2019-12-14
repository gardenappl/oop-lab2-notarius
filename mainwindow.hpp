#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <vector>
#include <editor/noteeditor.hpp>
#include <notes/notecontext.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


/*!
 * \brief The MainWindow is the actual editor window for a given note context.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Creates an editor window within the given NoteContext
     * \param context a note context that the user will be working with.
     * \param parent an optional parent widget.
     */
    MainWindow(NoteContext context, QWidget *parent = nullptr);
    ~MainWindow();

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

private:
    //NoteEditor* open(QUrl uri);

    /*!
     * \brief The name of the default context.
     */
    const QString defaultContextName = "My Notes";

    /*!
     * \brief the context which the current user is working with.
     */
    NoteContext currentContext;

    std::vector<NoteEditor*> editors;
    size_t currentEditorID;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
