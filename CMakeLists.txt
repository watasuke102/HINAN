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
set(AS_ADD_ON /usr/share/angelscript/add_on)

include_directories("./inc" ${AS_ADD_ON})
set(TS_FILES lang/${PROJECT_NAME}_ja_JP.ts)

# Add headers what written "Q_OBJECT"
qt_wrap_cpp(HEADERS
  inc/program_reader.h
  inc/core.h
)
set(PROJECT_SOURCES ${HEADERS} ${TS_FILES}
  src/main.cpp
  src/core.cpp
  src/program_reader.cpp
  ${AS_ADD_ON}/scriptbuilder/scriptbuilder.cpp
  ${AS_ADD_ON}/scriptstdstring/scriptstdstring.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable( ${PROJECT_NAME} ${PROJECT_SOURCES} )
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} )
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  Qt${QT_VERSION_MAJOR}::Widgets
  -langelscript
)
