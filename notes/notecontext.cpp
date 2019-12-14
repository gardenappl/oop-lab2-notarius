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
#include <editor/editorwindow.hpp>

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
        notes[id] = Note(note.toObject()["Name"].toString());
    }
    setCreationDate(QDateTime::fromSecsSinceEpoch(jsonData["Created"].toString().toInt()));
    return true;
}

bool NoteContext::save()
{
    std::cout << "Saving context..." << std::endl;
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
    jsonData.insert("Created", getCreationDate().toSecsSinceEpoch());

    //Make sure folder exists
    QDir dirUrl(getPath());
    dirUrl.mkpath(".");

    std::cout << "Saving context to " << (getPath() + "/context.json").toStdString() << std::endl;
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
    return QDir::cleanPath(EditorWindow::getNotesFolder() + '/' + name + '/' + note.name);
}

QString NoteContext::getPath()
{
    return QDir::cleanPath(EditorWindow::getNotesFolder() + '/' + name);
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

void NoteContext::setCreationDate(QDateTime dateTime)
{
    creationDate = dateTime;
}

QDateTime NoteContext::getCreationDate()
{
    return creationDate;
}
