cmake_minimum_required(VERSION 3.0) 

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
 
project(Project)

include_directories(include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Project_SOURCE_DIR}/bin)

set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


add_executable(Main main.cpp
Constants.h 
Solder.h 
Solder.cpp 
Factory.cpp 
Factory.h 
Army.cpp 
Army.h
help.txt
)

install(TARGETS Main RUNTIME DESTINATION bin)