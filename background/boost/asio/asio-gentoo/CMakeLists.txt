cmake_minimum_required(VERSION 2.6)
PROJECT(asio-gentoo)

set(BOOST_INCLUDE_DIR "~/boost/build/include")
set(BOOST_LIBRARY "~/boost/build/lib/")

include_directories( ${BOOST_INCLUDE_DIR} )

add_executable( ${PROJECT} main.cpp )

target_link_libraries( ${PROJECT} ${BOOST_LIBRARY} )