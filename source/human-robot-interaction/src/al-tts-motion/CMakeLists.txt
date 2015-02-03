# Author: Aravinth Panchadcharam
# Email: me@aravinth.info
# Date: 03/01/15.

####### SETUP #######
cmake_minimum_required(VERSION 2.6)
get_filename_component(FOLDER_NAME_AS_PROJECT ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${FOLDER_NAME_AS_PROJECT})

set(CMAKE_CXX_FLAGS "-stdlib=libstdc++")

set(ALCOMMON ${PROJECT_SOURCE_DIR}/lib/libalcommon.dylib)
set(ALERROR ${PROJECT_SOURCE_DIR}/lib/libalerror.dylib)
set(ALPROXY ${PROJECT_SOURCE_DIR}/lib/libalproxies.dylib)
set(ALVALUE ${PROJECT_SOURCE_DIR}/lib/libalvalue.dylib)
set(QI ${PROJECT_SOURCE_DIR}/lib/libqi.dylib)
set(QIMESSAGING ${PROJECT_SOURCE_DIR}/lib/libqimessaging.dylib)
set(QITYPE ${PROJECT_SOURCE_DIR}/lib/libqitype.dylib)
set(RTT ${PROJECT_SOURCE_DIR}/lib/librttools.dylib)


set(BOOST_SIGNAL "/usr/local/Cellar/boost/1.56.0/lib/libboost_signals.dylib")
set(BOOST_SYSTEM "/usr/local/Cellar/boost/1.56.0/lib/libboost_system.dylib")
set(BOOST_CHRONO "/usr/local/Cellar/boost/1.56.0/lib/libboost_chrono.dylib")
set(BOOST_FILE "/usr/local/Cellar/boost/1.56.0/lib/libboost_filesystem.dylib")
set(BOOST_PROGRAM "/usr/local/Cellar/boost/1.56.0/lib/libboost_program_options.dylib")
set(BOOST_REGEX "/usr/local/Cellar/boost/1.56.0/lib/libboost_regex.dylib")
set(BOOST_LOCALE "/usr/local/Cellar/boost/1.56.0/lib/libboost_locale.dylib")
set(BOOST_DATETIME "/usr/local/Cellar/boost/1.56.0/lib/libboost_date_time.dylib")
set(BOOST_THREAD "/usr/local/Cellar/boost/1.56.0/lib/libboost_thread.dylib")


set(BOOST_INCLUDE_DIR "/usr/local/Cellar/boost/1.56.0/include")
set(AL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)


####### BUILD #######
include_directories( ${BOOST_INCLUDE_DIR} ${AL_INCLUDE_DIR} )

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries( ${PROJECT_NAME} ${ALCOMMON} ${ALERROR} ${ALPROXY} ${ALVALUE} ${QI} ${QIMESSAGING} ${QITYPE} ${RTT} ${BOOST_SYSTEM})


