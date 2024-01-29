# project_root/CMakeLists.txt

# Minimum required version of CMake
cmake_minimum_required(VERSION 3.8)

# Project name
project(VulkanGuide)



# Include the source directory

add_subdirectory(thirdparty/vk-bootstrap)
add_subdirectory(src)



target_include_directories(VulkanGuide PRIVATE src)
target_include_directories(VulkanGuide PRIVATE thirdparty/stb_image thirdparty/Vma thirdparty/fastgltf)






# Add Vulkan libraries to your project

# Add your other CMake configurations, source files, etc.