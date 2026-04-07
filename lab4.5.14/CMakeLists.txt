cmake_minimum_required(VERSION 3.14)
project(lab4_8 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

add_executable(lab4_8
    main.cpp
    TicketWindow.h
    TicketWindow.cpp
    Ticket.h
)

target_link_libraries(lab4_8
    PRIVATE
        Qt5::Core
        Qt5::Widgets
)
