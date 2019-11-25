#include "notecontext.hpp"

#include <QDir>

NoteContext::NoteContext(QUrl url, QString name)
    : url(url), name(name)
{}

QUrl NoteContext::getUrl(Note* note)
{
    return QUrl(QDir::cleanPath(url.toString() + '/' + name + '/' + note->name));
}

QUrl NoteContext::getUrl()
{
    return QUrl(QDir::cleanPath(url.toString() + '/' + name));
}

