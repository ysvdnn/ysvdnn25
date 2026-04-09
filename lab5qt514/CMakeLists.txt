cmake_minimum_required(VERSION 3.14)
project(lab5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

qt_add_executable(lab5
    main.cpp
    mainWindow.h
    mainWindow.cpp
    passForm.h
    passForm.cpp
    passEntry.h
    passEntry.cpp
)

target_link_libraries(lab5
    PRIVATE
        Qt5::Core
        Qt5::Widgets
)
