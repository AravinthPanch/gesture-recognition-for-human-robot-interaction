# Author: Aravinth Panchadcharam
# Email: me@aravinth.info
# Date: 09/12/14.

cmake_minimum_required(VERSION 2.6)
project(human-robot-interaction)


####### MACROS #######
MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
        LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()


####### COMMAND LINE ARGUMENTS. Eg: -DSELECT_SUBPROJECT=ni-simple-sensor-read #######
if(SELECT_SUBPROJECT)
	message("-- SELECTED SUBPROJECT IS " ${SELECT_SUBPROJECT})
	list(APPEND SUBPROJECTSLIST ${SELECT_SUBPROJECT})
else()
	SUBDIRLIST(SUBPROJECTSLIST ${PROJECT_SOURCE_DIR}/src)	
endif()

####### FLAGS #######
add_definitions(-DBOOST_LOG_DYN_LINK)


####### SETUP #######
set(PROJECT_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(SUBPROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(NITE2_DATA_DIR "${PROJECT_SOURCE_DIR}/lib/NiTE2/NiTE2")

set(OPENNI2_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/OpenNI2)
set(NITE2_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/NiTE2)


####### OS DEPENDENCE PATH #######
if( CMAKE_SYSTEM_NAME STREQUAL Darwin )
	message("-- TARGET SYSTEM IS " ${CMAKE_SYSTEM_NAME})
	set(OPENNI2_LIBRARY ${PROJECT_SOURCE_DIR}/lib/OpenNI2/libOpenNI2.dylib)
	set(NITE2_LIBRARY ${PROJECT_SOURCE_DIR}/lib/NiTE2/libNiTE2.dylib)
	set(BOOST_INCLUDE_DIR "/usr/local/Cellar/boost/1.56.0/include")
	set(BOOST_SYSTEM "/usr/local/Cellar/boost/1.56.0/lib/libboost_system-mt.dylib")
	set(BOOST_THREAD "/usr/local/Cellar/boost/1.56.0/lib/libboost_thread-mt.dylib")
	set(BOOST_LOG "/usr/local/Cellar/boost/1.56.0/lib/libboost_log-mt.dylib")

elseif( CMAKE_SYSTEM STREQUAL Linux-2.6.33.9-rt31-aldebaran-rt)
	message( "-- TARGET SYSTEM IS " ${CMAKE_SYSTEM})
	set(OPENNI2_LIBRARY "/usr/lib/libOpenNI2.so")
	set(NITE2_LIBRARY "/usr/lib/libNiTE2.so")
	set(BOOST_INCLUDE_DIR "/usr/include/boost")
	set(BOOST_SYSTEM "/usr/lib/libboost_system-mt.so")		
	set(BOOST_THREAD "/usr/lib/libboost_thread-mt.so")
	set(BOOST_LOG "/usr/lib/libboost_log-mt.so")	

endif()


####### BUILD #######
foreach(SUBPROJECT ${SUBPROJECTSLIST})
    	message("-- PROJECT " ${SUBPROJECT} " IS ADDED TO THE BUILD LIST" )
    	add_subdirectory(${SUBPROJECT_SOURCE_DIR}/${SUBPROJECT})
endforeach()


####### POST-BUILD #######
file(COPY ${NITE2_DATA_DIR} DESTINATION ${PROJECT_BINARY_DIR})




