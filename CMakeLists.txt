cmake_minimum_required(VERSION 3.16)

project(TidalAnalysisAndPredictionSystem
    VERSION 2.0.0
    LANGUAGES CXX
    DESCRIPTION "Tidal analysis and prediction system"
)

set(VERSIONINFO_FILE_DESCRIPTION ${PROJECT_DESCRIPTION})
set(VERSIONINFO_PRODUCT_NAME "Tidal Analysis And Prediction System")

# Enable C++20 globally (it's downgraded in some modules, but this is the default)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Charts Concurrent Positioning PrintSupport)

file(GLOB _HEADERS_PUBLIC
    "*.h"
    "include/*.h"
    "include/*/*.h"
)

file(GLOB _SOURCES
    "*.cpp"
    #"src/*.h"
    "src/*.cpp"
    #"src/*/*.h"
    "src/*/*.cpp"
    "include/*.cpp"
    "include/*/*.cpp"
    #"src/*/*.h"
    "src/*/*.cpp"
    "*.qrc"
)

file(GLOB _QML_SOURCES
    "*.qml"
    "qml/*.qml"
    "qml/*/*.qml"
)

#add_library(${PROJECT_NAME} SHARED
#    ${_HEADERS_PUBLIC}
#    ${_SOURCES}
#    ${_SHADER_SOURCES}
#    ${_QML_SOURCES}
#    ${CMAKE_CURRENT_BINARY_DIR}/res/version.rc
#)

# target_include_directories(${PROJECT_NAME}
#     PUBLIC
#         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#         #$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include> # FIXME this is for *_export.h
#         #$<INSTALL_INTERFACE:include>
#     PRIVATE
#         ${CMAKE_CURRENT_SOURCE_DIR}/src
# )

add_executable(${PROJECT_NAME}
    ${_HEADERS_PUBLIC}
    ${_SOURCES}
    ${_QML_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  Qt::Concurrent
  Qt::Core
  Qt::Charts
  Qt::Gui
  Qt::Widgets
  Qt::Positioning
  Qt::PrintSupport
)


