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
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
  welcomewindow.cpp
  welcomewindow.h
  welcomewindow.ui
  editor/noteeditor.cpp
  editor/noteeditor.h
  editor/noteeditor.ui
  editor/editortab.cpp
  editor/editortab.h
)

target_link_libraries(notarius PRIVATE Qt5::Widgets)
