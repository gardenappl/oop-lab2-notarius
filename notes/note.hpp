#ifndef EDITORTAB_H
#define EDITORTAB_H

#include <QString>
#include <QUrl>



struct Note
{
public:
    QString name;

    Note() = default;
    Note(QString name);
};

#endif // EDITORTAB_H
