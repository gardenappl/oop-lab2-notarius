#include "mainwindow.hpp"

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

    parser.process(app);

    std::cout << "Hello" << std::endl;
    std::cout << "is context set? " << parser.isSet(contextOption) << std::endl;
    std::cout << "value? " << parser.value(contextOption).toStdString() << std::endl;

    NoteContext defaultContext(parser.isSet(contextOption) ? parser.value(contextOption) : "My Notes");
    std::cout << "Created context: " << defaultContext.name.toStdString() << std::endl;
    MainWindow w(defaultContext);
    w.show();
    return app.exec();
}
