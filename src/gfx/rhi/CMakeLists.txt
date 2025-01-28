add_subdirectory(vulkan)

add_library(rhi rhi.cpp)
target_link_libraries(rhi PRIVATE vulkan_rhi)