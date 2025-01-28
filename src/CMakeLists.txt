add_executable(main main.cpp)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(gfx)
add_subdirectory(app)

target_link_libraries(main app)