cmake_minimum_required(VERSION 3.15)
project(OhGodMakeThePunsStop_version_2)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.71.0 COMPONENTS system filesystem REQUIRED)

if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()

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
        assets/A1.txt
        assets/A1_backup.txt
        assets/A2.txt
        assets/A2_backup.txt
        assets/A3.txt
        assets/A3_backup.txt
        assets/requests.txt
        assets/sales_report.txt
        "TODO and Notes.txt")

if(Boost_FOUND)

    target_link_libraries(OhGodMakeThePunsStop_version_2 ${Boost_LIBRARIES})

endif()