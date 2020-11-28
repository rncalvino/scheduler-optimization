#set(CMAKE_VERBOSE_MAKEFILE ON)

project (CriticalPath CXX)

cmake_minimum_required(VERSION 3.0)

add_compile_options(-std=c++14)
add_compile_options(-Wall -Wextra -pedantic -Werror)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED OFF)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.67.0 COMPONENTS program_options graph thread REQUIRED) 

find_package(PkgConfig)
pkg_check_modules(Graphviz_Package ${REQUIRED} libgvc libcdt libcgraph)

find_library(Graphviz_GVC_LIBRARY NAMES gvc HINTS ${Graphviz_Package_LIBDIR} ${Graphviz_Package_LIBRARY_DIRS})
find_library(Graphviz_CDT_LIBRARY NAMES cdt HINTS ${Graphviz_Package_LIBDIR} ${Graphviz_Package_LIBRARY_DIRS})
find_library(Graphviz_CGRAPH_LIBRARY NAMES cgraph HINTS ${Graphviz_Package_LIBDIR} ${Graphviz_Package_LIBRARY_DIRS})

set(Graphviz_LIBRARIES "${Graphviz_GVC_LIBRARY}" "${Graphviz_CDT_LIBRARY}" "${Graphviz_CGRAPH_LIBRARY}")

include_directories(${Boost_INCLUDE_DIRS}) 
add_executable(CriticalPath ${SOURCES})
target_link_libraries(CriticalPath ${Boost_LIBRARIES} ${Graphviz_LIBRARIES})

