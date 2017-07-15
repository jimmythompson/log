cmake_minimum_required(VERSION 3.5)

project(Log)

set(SOURCES src/Log.cpp)
set(INCLUDE_DIRECTORIES include)

include_directories(${INCLUDE_DIRECTORIES})

add_library(${PROJECT_NAME} ${SOURCES})