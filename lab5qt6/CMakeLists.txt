cmake_minimum_required(VERSION 3.19)
project(lab5 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

qt_add_executable(lab5
    WIN32 MACOSX_BUNDLE
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
        Qt::Core
        Qt::Widgets
)
