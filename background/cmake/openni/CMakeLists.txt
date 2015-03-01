cmake_minimum_required(VERSION 2.6)
PROJECT(cmakeopenni)

set(OPENNI2_INCLUDE_DIR "/Applications/OpenNI2/Include")
set(OPENNI2_LIBRARY "/Applications/OpenNI2/Redist/libOpenNI2.dylib")

include_directories( ${OPENNI2_INCLUDE_DIR} )
add_executable(cmakeopenni main.cpp)
target_link_libraries( cmakeopenni ${OPENNI2_LIBRARY} )