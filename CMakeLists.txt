# project_root/CMakeLists.txt

# Minimum required version of CMake
cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")


# Project name
project(VulkanGuide)



# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

# Set the default build type if not specified
# Include the source directory



add_subdirectory(thirdparty/vk-bootstrap)
add_subdirectory(src)
add_subdirectory(thirdparty/imgui)
add_subdirectory(thirdparty/fastgltf)


target_include_directories(VulkanGuide PRIVATE src)
target_include_directories(VulkanGuide PRIVATE thirdparty/stb_image thirdparty/Vma thirdparty/fastgltf/include thirdparty/imgui)
