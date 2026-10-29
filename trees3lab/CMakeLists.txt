cmake_minimum_required(VERSION 3.16)
project(lab3_binary_tree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)


# Qt6, а если его нет - Qt5
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(lab3
    main.cpp
    MainWindow.cpp
    MainWindow.h
    TreeWidget.h
    Binarytree.cpp
    Binarytree.h
)
target_link_libraries(lab3 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

configure_file(${CMAKE_SOURCE_DIR}/tree.txt ${CMAKE_BINARY_DIR}/tree.txt COPYONLY)
