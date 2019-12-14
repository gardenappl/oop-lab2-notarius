#include "notecontext.hpp"

#include <algorithm>
#include <iostream>
#include <fstream>

#include <QDir>
#include <QStandardPaths>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QApplication>
#include <QJsonDocument>

NoteContext::NoteContext(QString name)
    : name(name)
{}

bool NoteContext::init()
{
    QFile loadFile(QDir::cleanPath(getPath() + "/context.json"));
    if(!loadFile.open(QIODevice::ReadOnly))
        return false;

    QByteArray saveData = loadFile.readAll();

    QJsonDocument doc(QJsonDocument::fromJson(saveData));
    QJsonObject jsonData = doc.object();
    QJsonArray notesArray = jsonData["Notes"].toArray();
    for(const auto& note : notesArray)
    {
        size_t id = note.toObject()["ID"].toString().toInt();
        std::cout << "ID: " << id << std::endl;
        notes[id] = Note(note.toObject()["Name"].toString());
    }
    std::cout << "[init]Notes count: " << notes.size() << std::endl;
    return true;
}

bool NoteContext::save()
{
    QJsonObject jsonData;
    QJsonArray notesArray;
    for(const auto& note : notes)
    {
        QJsonObject noteObject;
        noteObject.insert("ID", QString::number(note.first));
        noteObject.insert("Name", note.second.name);
        notesArray.push_back(noteObject);
    }
    jsonData.insert("Notes", notesArray);
    QFile saveFile(QDir::cleanPath(getPath() + "/context.json"));
    if(!saveFile.open(QIODevice::WriteOnly))
    {
        return false;
    }
    QJsonDocument doc(jsonData);
    saveFile.write(doc.toJson());
    return true;
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

const std::unordered_map<size_t, Note>* NoteContext::getNotes()
{
    return &notes;
}
