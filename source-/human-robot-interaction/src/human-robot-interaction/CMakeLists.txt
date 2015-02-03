# Author: Aravinth Panchadcharam
# Email: me@aravinth.info
# Date: 13/01/15.

####### SETUP #######
cmake_minimum_required(VERSION 2.6)
get_filename_component(FOLDER_NAME_AS_PROJECT ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${FOLDER_NAME_AS_PROJECT})


####### BUILD #######
include_directories( ${OPENNI2_INCLUDE_DIR} ${NITE2_INCLUDE_DIR} ${BOOST_INCLUDE_DIR})
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries( ${PROJECT_NAME} ${OPENNI2_LIBRARY} ${NITE2_LIBRARY} ${BOOST_SYSTEM} ${BOOST_THREAD} ${BOOST_LOG})




