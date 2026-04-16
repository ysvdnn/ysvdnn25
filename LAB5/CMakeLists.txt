cmake_minimum_required(VERSION 3.19)
project(lab5_2 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

qt_add_executable(lab5_2
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainWindow.h
    mainWindow.cpp
    npcForm.h
    npcForm.cpp
    npc.h
    npc.cpp
)

target_link_libraries(lab5_2
    PRIVATE
        Qt::Core
        Qt::Widgets
)
