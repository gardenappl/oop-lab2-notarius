#include "editor/editorwindow.hpp"
#include "notes/notecontext.hpp"

#include <iostream>
#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCommandLineParser parser;
    QCommandLineOption contextOption("context",
                                     QApplication::translate("main", "Open the <context>."),
                                     QApplication::translate("main", "context"));
    parser.addOption(contextOption);
    QCommandLineOption newOption("new",
                                     QApplication::translate("main", "If used with the context option, resets it's creation time."));
    parser.addOption(newOption);

    parser.process(app);

    std::cout << "Hello" << std::endl;

    NoteContext context(parser.isSet(contextOption) ? parser.value(contextOption) : "My Notes");
    if(parser.isSet(newOption))
        context.setCreationDate(QDateTime::currentDateTimeUtc());
    std::cout << "Starting in context: " << context.name.toStdString() << std::endl;
    EditorWindow window(context);
    window.show();
    return app.exec();
}
