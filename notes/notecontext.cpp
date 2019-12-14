#include "notecontext.hpp"

#include <QDir>

NoteContext::NoteContext(QUrl url, QString name)
    : url(url), name(name)
{}

void NoteContext::init()
{

}

QString NoteContext::getPath(Note* note)
{
    return QDir::cleanPath(url.toString() + '/' + name + '/' + note->name);
}

QString NoteContext::getPath()
{
    return QDir::cleanPath(url.toString() + '/' + name);
}

