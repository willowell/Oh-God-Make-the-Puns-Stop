cmake_minimum_required(VERSION 3.13)
project(OhGodMakeThePunsStop_version_2)

message(STATUS "Starting CMake...")

set(CMAKE_CXX_STANDARD 17)

find_package(fmt REQUIRED)

if (fmt_FOUND)

    message(STATUS "fmt_INCLUDE_DIRS: ${fmt_INCLUDE_DIRS}")

    include_directories(${fmt_INCLUDE_DIRS})

endif ()

message(STATUS "Including source tree...")

include_directories(src)

add_executable(OhGodMakeThePunsStop_version_2
        src/Auditorium.cpp
        src/Auditorium.h
        src/Exceptions.cpp
        src/Exceptions.h
        src/main.cpp
        src/Seat.cpp
        src/Seat.h
        src/Theatre.cpp
        src/Theatre.h
        src/Utilities.cpp
        src/Utilities.h
        src/Lifecycle.cpp
        src/Lifecycle.h
        assets/A1.txt
        assets/A1_backup.txt
        assets/A2.txt
        assets/A2_backup.txt
        assets/A3.txt
        assets/A3_backup.txt
        assets/requests.txt
        assets/sales_report.txt
        "TODO and Notes.txt")

if (fmt_FOUND)

    message(STATUS "Linking fmt...")

    target_link_libraries(OhGodMakeThePunsStop_version_2 fmt::fmt)

endif ()

add_subdirectory(Google_tests)