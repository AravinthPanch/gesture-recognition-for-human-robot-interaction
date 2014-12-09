# Author: Aravinth Panchadcharam
# Email: me@aravinth.info
# Date: 09/12/14.

####### SETUP #######
cmake_minimum_required(VERSION 2.6)
get_filename_component(FOLDER_NAME_AS_PROJECT ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${FOLDER_NAME_AS_PROJECT})


####### BUILD #######
include_directories( ${OPENNI2_INCLUDE_DIR} ${NITE2_INCLUDE_DIR})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries( ${PROJECT_NAME} ${OPENNI2_LIBRARY} ${NITE2_LIBRARY})
