find_package(Vulkan REQUIRED)

add_library(vulkan_rhi api.cpp rhi.cpp)

target_link_libraries(vulkan_rhi PRIVATE glfw Vulkan::Vulkan)