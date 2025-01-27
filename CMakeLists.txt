cmake_minimum_required(VERSION 3.29)

project(piesel-engine)

include(cmake/CPM.cmake)


CPMAddPackage("gh:glfw/glfw#3.4")

add_subdirectory(src)