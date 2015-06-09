# Author: Aravinth Panchadcharam
# Email: me@aravinth.info
# Date: 13/01/15.

####### SETUP #######
cmake_minimum_required(VERSION 2.6)
get_filename_component(FOLDER_NAME_AS_PROJECT ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${FOLDER_NAME_AS_PROJECT})


####### BUILD #######
include_directories( ${WEBSOCKET_INCLUDE} ${Boost_INCLUDE_DIRS})
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries( ${BOOST_THREAD} ${BOOST_LOG} ${BOOST_SYSTEM})
