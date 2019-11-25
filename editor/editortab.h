#ifndef EDITORTAB_H
#define EDITORTAB_H

#include <QString>
#include <QUrl>



struct EditorTab
{
public:
    QUrl uri;
    QString name;

    EditorTab(QUrl uri, QString name);
};

#endif // EDITORTAB_H
