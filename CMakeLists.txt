# Copyright (c) 2018-2020 Viktor Kireev
# Distributed under the MIT License

cmake_minimum_required(VERSION 3.13...3.14.2)

project(CppOtl CXX)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE include)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include)
