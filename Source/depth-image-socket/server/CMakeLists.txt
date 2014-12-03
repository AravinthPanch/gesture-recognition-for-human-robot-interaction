# Author: Aravinth Panchadcharam
# Email: me@aravinth.info
# Date: 03/12/14.

####### SETUP #######

cmake_minimum_required(VERSION 2.6)
PROJECT(depth-image-socket-server)

set(PROJECT_BINARY_DIR "${PROJECT_SOURCE_DIR}/bin")

if( CMAKE_SYSTEM_NAME STREQUAL Darwin )
	message( "-- SYSTEM NAME IS " ${CMAKE_SYSTEM_NAME})
	set( BOOST_INCLUDE_DIR "/usr/local/Cellar/boost/1.56.0/include" )
	set( BOOST_LIBRARY "/usr/local/Cellar/boost/1.56.0/lib/libboost_system.dylib" )

elseif( CMAKE_SYSTEM_NAME STREQUAL Linux-2.6.33.9-rt31-aldebaran-rt)
	message( "-- SYSTEM NAME IS " ${CMAKE_SYSTEM_NAME})
	set( BOOST_INCLUDE_DIR "/usr/include" )
	set( BOOST_LIBRARY "/usr/lib/libboost_system.so" )	

endif()



####### BUILD #######

include_directories( ${BOOST_INCLUDE_DIR} )

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries( ${PROJECT_NAME} ${BOOST_LIBRARY})



####### POST-BUILD #######

ADD_CUSTOM_COMMAND(
		TARGET ${PROJECT_NAME}
        POST_BUILD                  
        COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_NAME} ${PROJECT_BINARY_DIR}
)