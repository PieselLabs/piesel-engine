find_package(Vulkan REQUIRED)
CPMAddPackage("gh:charles-lunarg/vk-bootstrap#v1.4.305")

add_library(vulkan_rhi api.cpp rhi.cpp device.cpp swapchain.cpp command_list.cpp sync.cpp)

target_link_libraries(vulkan_rhi PRIVATE glfw Vulkan::Vulkan vk-bootstrap)