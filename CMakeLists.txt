cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME hinan)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

include_directories("./inc")
set(TS_FILES lang/${PROJECT_NAME}_ja_JP.ts)

# Add headers what written "Q_OBJECT"
qt_wrap_cpp(HEADERS
  inc/cpp_reader.h
)
set(PROJECT_SOURCES ${HEADERS} ${TS_FILES}
  src/main.cpp
  src/cpp_reader.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable( ${PROJECT_NAME} ${PROJECT_SOURCES} )
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} )
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
