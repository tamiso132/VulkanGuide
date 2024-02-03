

# Add source to this project's executable.
set(SOURCE_FILES
  main.cpp
  vk_types.h
  vk_initializers.cpp
  vk_initializers.h
  vk_images.h
  vk_images.cpp 
  vk_descriptors.h
  vk_descriptors.cpp
  vk_pipelines.h
  vk_pipelines.cpp
  vk_engine.h
  vk_engine.cpp
  loader/vk_loader.h
  loader/vk_loader.cpp
  camera.cpp
  camera.h
  meshes.cpp
  meshes.h
)



find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)
find_package(SDL2 REQUIRED)
find_package(fmt CONFIG REQUIRED)




add_executable(VulkanGuide ${SOURCE_FILES})

# Link the Vulkan library
target_link_libraries(VulkanGuide PRIVATE Vulkan::Vulkan)
target_link_libraries(VulkanGuide PRIVATE vk-bootstrap::vk-bootstrap)

target_link_libraries(VulkanGuide PRIVATE ${SDL2_LIBRARIES})
target_link_libraries(VulkanGuide PRIVATE fmt::fmt)

target_link_libraries(VulkanGuide PRIVATE fastgltf::fastgltf)


target_compile_options(VulkanGuide PRIVATE -w)
target_include_directories(VulkanGuide PRIVATE loader)
