cmake_minimum_required(VERSION 2.8)
project(helloworld)
find_package (Boost COMPONENTS system)

message(${Boost_FOUND})
message(${Boost_INCLUDE_DIRS})
message(${Boost_LIBRARIES})


