find_package(Vulkan REQUIRED)

add_library(vulkan_rhi api.cpp rhi.cpp device.cpp swapchain.cpp)

CPMAddPackage("gh:charles-lunarg/vk-bootstrap#v1.4.305")

target_link_libraries(vulkan_rhi PRIVATE glfw Vulkan::Vulkan vk-bootstrap)