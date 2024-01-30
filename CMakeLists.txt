# project_root/CMakeLists.txt

# Minimum required version of CMake
cmake_minimum_required(VERSION 3.8)

# Project name
project(VulkanGuide)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Include the source directory

add_subdirectory(thirdparty/vk-bootstrap)
add_subdirectory(src)



target_include_directories(VulkanGuide PRIVATE src)
target_include_directories(VulkanGuide PRIVATE thirdparty/stb_image thirdparty/Vma thirdparty/fastgltf)



file(GLOB_RECURSE GLSL_SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/shaders/*.frag"
    "${PROJECT_SOURCE_DIR}/shaders/*.vert"
    "${PROJECT_SOURCE_DIR}/shaders/*.comp"
    )

foreach(GLSL ${GLSL_SOURCE_FILES})
  message(STATUS "BUILDING SHADER")
  get_filename_component(FILE_NAME ${GLSL} NAME)
  set(SPIRV "${PROJECT_SOURCE_DIR}/shaders/${FILE_NAME}.spv")
  message(STATUS ${GLSL})
  add_custom_command(
    OUTPUT ${SPIRV}
    COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
    DEPENDS ${GLSL})
  list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
    Shaders 
    DEPENDS ${SPIRV_BINARY_FILES}
    )



# Add Vulkan libraries to your project

# Add your other CMake configurations, source files, etc.