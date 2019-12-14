#ifndef EDITORTAB_H
#define EDITORTAB_H

#include <QString>
#include <QUrl>



struct Note
{
public:
    QString name;

    /*!
     * \brief The default constructor, no name is specified.
     */
    Note() = default;
    /*!
     * \brief Constructs a Note object with a given name.
     * \param name
     */
    Note(QString name);
};

#endif // EDITORTAB_H
