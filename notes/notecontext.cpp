#include "notecontext.hpp"

#include <algorithm>
#include <iostream>
#include <fstream>

#include <QDir>
#include <QStandardPaths>

NoteContext::NoteContext(QString name)
    : name(name)
{}

void NoteContext::init()
{

}

void NoteContext::save()
{
    std::ofstream file;
    file.open(getPath().toStdString() + "/context.info");
    file << "Context" << std::endl;
}

QString NoteContext::getPath(Note* note)
{
    return QDir::cleanPath(getStorageFolderPath() + '/' + name + '/' + note->name);
}

QString NoteContext::getPath()
{
    return QDir::cleanPath(getStorageFolderPath() + '/' + name);
}

void NoteContext::addNote(Note newNote)
{
    for(const Note& note : notes)
    {
        if(note.name == newNote.name)
            throw std::invalid_argument("The context already contains a note with the same name.");
    }
    notes.push_back(newNote);
}

QString NoteContext::getStorageFolderPath()
{
    return QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
}

