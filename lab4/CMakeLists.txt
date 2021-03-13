cmake_minimum_required(VERSION 3.5.1)
project(lab4 C)

set(SRC src/main.c src/lab4_header.h src/lab4_source.c src/stack_header.h src/stack_source.c)

add_executable(${PROJECT_NAME} ${SRC})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../modules")
include(common_lab)
