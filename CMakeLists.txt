cmake_minimum_required(VERSION 2.8.11)

project(ShowStereo)

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -Wall -g -ggdb ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin) # http://stackoverflow.com/questions/18826789/cmake-output-build-directory

# cmake error,can not find *.ui
##set(CMAKE_AUTOUIC ON)

# important
# https://stackoverflow.com/questions/19761767/qt-5-cmake-fails-with-undefined-reference-to-vtable-on-hello-world-with-inc-sr
set(CMAKE_AUTOMOC ON)
##set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

# use qt to read image
## read image
##find_package(OpenImageIO REQUIRED)
##include_directories(${OpenImageIO_INCLUDE_DIR})

## http://stackoverflow.com/questions/3201154/cmake-automatically-add-all-files-in-a-folder-to-a-target
file(GLOB ShowStereo_UI ${CMAKE_SOURCE_DIR}/ui/*)
file(GLOB ShowStereo_SRC ${CMAKE_SOURCE_DIR}/src/*)

include_directories(${ShowStereo_SRC})
include_directories(${ShowStereo_UI})

## http://stackoverflow.com/questions/29968264/linking-and-uic-order-in-a-cmake-qt-project
#qt5_wrap_cpp(ShowStereo_SRC_H ${ShowStereo_SRC})
qt5_wrap_ui(ShowStereo_UI_H ${ShowStereo_UI})

add_executable(ShowStereo ${ShowStereo_SRC} ${ShowStereo_UI_H})

target_link_libraries(ShowStereo Qt5::Core Qt5::Gui Qt5::Widgets)
##target_link_libraries(ShowStereo OpenImageIO)

## http://stackoverflow.com/questions/13429656/cmake-how-to-copy-contents-of-a-directory-into-build-directory-after-make
add_custom_command(TARGET ShowStereo POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/icons $<TARGET_FILE_DIR:ShowStereo>/icons)
