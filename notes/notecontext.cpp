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

QString NoteContext::getPath(const Note& note)
{
    return QDir::cleanPath(getStorageFolderPath() + '/' + name + '/' + note.name);
}

QString NoteContext::getPath()
{
    return QDir::cleanPath(getStorageFolderPath() + '/' + name);
}

size_t NoteContext::addNote(Note newNote)
{
    for(const auto& note : notes)
    {
        if(note.second.name == newNote.name)
            throw std::invalid_argument("The context already contains a note with the same name.");
    }
    size_t newID = getNextAvailableID();
    notes[newID] = newNote;
    return newID;
}

Note NoteContext::getNoteByID(size_t id)
{
    return notes.at(id);
}

QString NoteContext::getStorageFolderPath()
{
    return QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
}

size_t NoteContext::getNextAvailableID()
{
    size_t newID = 0;
    while(notes.count(newID) != 0)
        newID++;
    return newID;
}

