cmake_minimum_required(VERSION 3.5)

project(SmartCalc_v1.0 VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        gnu/main.cpp
        gnu/window.cpp
        gnu/window.h
        gnu/window.ui
        calclib/calc.c
        calclib/calc.h
        calclib/parser.c
        calclib/parser.h
        calclib/stack.c
        calclib/stack.h
        banklib/credit.c
        banklib/credit.h
        banklib/deposit.c
        banklib/deposit.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SmartCalc_v1.0
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(SmartCalc_v1.0
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(SmartCalc_v1.0 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

#add_executable(
#    WIN32_EXECUTABLE
#)

set_target_properties(SmartCalc_v1.0 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SmartCalc_v1.0)
endif()
