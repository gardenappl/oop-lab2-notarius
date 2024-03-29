cmake_minimum_required(VERSION 3.5)

project(notarius LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(notarius
  main.cpp
  editor/editorwindow.cpp
  editor/editorwindow.hpp
  editor/editorwindow.ui
  editor/noteeditor.cpp
  editor/noteeditor.hpp
  editor/noteeditor.ui
  notes/notecontext.cpp
  notes/notecontext.hpp
  notes/note.cpp
  notes/note.hpp
)

target_link_libraries(notarius PRIVATE Qt5::Widgets)
