# Author: Aravinth Panchadcharam
# Email: me@aravinth.info
# Date: 09/12/14.

cmake_minimum_required(VERSION 2.6)
project(human-robot-interaction)


####### FIND DEPENDENCIES #######
find_package (Boost REQUIRED COMPONENTS system thread log)
if(!Boost_FOUND)
message(SEND_ERROR "Boost Libray is not found. Please Install it.")  
endif()


if(CMAKE_SYSTEM_NAME STREQUAL Darwin)
	message("-- TARGET SYSTEM IS " ${CMAKE_SYSTEM_NAME})
	set(OPENNI2_LIBRARY ${PROJECT_SOURCE_DIR}/lib/OpenNI2/libOpenNI2.dylib)
	set(NITE2_LIBRARY ${PROJECT_SOURCE_DIR}/lib/NiTE2/libNiTE2.dylib)

elseif(CMAKE_SYSTEM_NAME STREQUAL Linux)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)     	
    	message("-- TARGET SYSTEM IS 64 Bit " ${CMAKE_SYSTEM_NAME})
		set(OPENNI2_LIBRARY ${PROJECT_SOURCE_DIR}/lib/OpenNI2/libOpenNI2.so)
		set(NITE2_LIBRARY ${PROJECT_SOURCE_DIR}/lib/NiTE2/libNiTE2.so)
	else()
    	message("-- TARGET SYSTEM IS 32 Bit " ${CMAKE_SYSTEM_NAME})
    	set(OPENNI2_LIBRARY ${PROJECT_SOURCE_DIR}/lib/OpenNI2/libOpenNI2-32.so)
		set(NITE2_LIBRARY ${PROJECT_SOURCE_DIR}/lib/NiTE2/libNiTE2-32.so)    	
	endif()

endif() 


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


####### COMMAND LINE ARGUMENTS. Eg: -DSELECT_SUBPROJECT=human-robot-interaction #######
if(SELECT_SUBPROJECT)
	message("-- SELECTED SUBPROJECT IS " ${SELECT_SUBPROJECT})
	list(APPEND SUBPROJECTSLIST ${SELECT_SUBPROJECT})
else()
	#SUBDIRLIST(SUBPROJECTSLIST ${PROJECT_SOURCE_DIR}/src)	
  list(APPEND SUBPROJECTSLIST ${PROJECT_NAME})
endif()


####### SETUP #######
set(CONFIG_FILE ${PROJECT_SOURCE_DIR}/../config/hri.json)
set(PROJECT_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(SUBPROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(NITE2_DATA_DIR "${PROJECT_SOURCE_DIR}/lib/NiTE2/NiTE2")
set(OPENNI2_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/OpenNI2)
set(NITE2_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/NiTE2)
set(UTILS_INCLUDE ${PROJECT_SOURCE_DIR}/include)


####### FLAGS #######
add_definitions(-DBOOST_LOG_DYN_LINK)


####### BUILD #######
foreach(SUBPROJECT ${SUBPROJECTSLIST})
    	message("-- PROJECT " ${SUBPROJECT} " IS ADDED TO THE BUILD LIST" )
    	add_subdirectory(${SUBPROJECT_SOURCE_DIR}/${SUBPROJECT})
endforeach()


####### POST-BUILD #######
file(COPY ${NITE2_DATA_DIR} DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ${CONFIG_FILE} DESTINATION ${PROJECT_BINARY_DIR})





