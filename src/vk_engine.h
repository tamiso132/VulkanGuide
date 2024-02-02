#pragma once

#include "../thirdparty/Vma/vk_mem_alloc.h"
#include "loader/vk_loader.h"
#include "vk_descriptors.h"
#include "vk_types.h"
#include "vulkan/vulkan_core.h"

struct ComputePushConstants {
  glm::vec4 data1;
  glm::vec4 data2;
  glm::vec4 data3;
  glm::vec4 data4;
};

struct ComputeEffect {
  const char *name;

  VkPipeline pipeline;
  VkPipelineLayout layout;

  ComputePushConstants data;
};

struct DeletionQueue {
  std::deque<std::function<void()>> deletors;

  void push_function(std::function<void()> &&function) {
    deletors.push_back(function);
  }

  void flush() {
    // reverse iterate the deletion queue to execute all the functions
    for (auto it = deletors.rbegin(); it != deletors.rend(); it++) {
      (*it)(); // call functors
    }

    deletors.clear();
  }
};

constexpr unsigned int FRAME_OVERLAP = 2;
struct FrameData {
  VkCommandPool _commandPool;
  VkCommandBuffer _mainCommandBuffer;

  VkSemaphore _swapchainSemaphore, _renderSemaphore;
  VkFence _renderFence;

  DeletionQueue _deletionQueue;
};

class VulkanEngine {
public:
  bool _isInitialized{false};
  int _frameNumber{0};
  bool stop_rendering{false};
  VkExtent2D _windowExtent{1700, 900};

  struct SDL_Window *_window{nullptr};

  static VulkanEngine &Get();

  // initializes everything in the engine
  void init();

  // shuts down the engine
  void cleanup();

  // draw loop
  void draw();

  // run main loop
  void run();

  GPUMeshBuffers uploadMesh(std::span<uint32_t> indices,
                            std::span<Vertex> vertices);

private:
  // basic pieces
  VkInstance _instance;
  VkDebugUtilsMessengerEXT _debug_messenger;
  VkDevice _device;
  VkPhysicalDevice _chosenGPU;
  VkSurfaceKHR _surface;

  // swapchain
  VkSwapchainKHR _swapchain;
  VkFormat _swapchain_image_format;

  std::vector<VkImage> _swapchain_images;
  std::vector<VkImageView> _swapchain_image_views;
  VkExtent2D _swapchain_extent;

  // Frame stuff
  FrameData _frames[FRAME_OVERLAP];
  FrameData &get_current_frame() {
    return _frames[_frameNumber % FRAME_OVERLAP];
  };

  VkQueue _graphicQueue;
  uint32_t _graphicQueueFamily;

  DeletionQueue _mainDeletionQueue;
  VmaAllocator _allocator;
  AllocatedImage _drawImage;
  VkExtent2D _drawExtent;

  DescriptorAllocator globalDescriptorAllocator;

  VkDescriptorSet _drawImageDescriptors;
  VkDescriptorSetLayout _drawImageDescriptorLayout;

  VkFence _immFence;
  VkCommandBuffer _immCommandBuffer;
  VkCommandPool _immCommandPool;

  std::vector<ComputeEffect> backgroundEffects;
  int currentBackgroundEffect{0};

  VkPipelineLayout _trianglePipelineLayout;
  VkPipeline _trianglePipeline;

  VkPipelineLayout _meshPipelineLayout;
  VkPipeline _meshPipeline;

  GPUMeshBuffers rectangle;
  std::vector<std::shared_ptr<MeshAsset>> testMeshes;

  void init_vulkan();
  void init_swapchain();
  void init_commands();
  void init_sync_structures();
  void init_descriptors();
  void init_pipelines();
  void init_background_pipelines();
  void init_triangle_pipeline();
  void init_imgui();
  void init_mesh_pipeline();
  void init_default_data();

  void create_swapchain(uint32_t width, uint32_t height);
  AllocatedBuffer create_buffer(size_t allocSize, VkBufferUsageFlags usage,
                                VmaMemoryUsage memoryUsage);

  void draw_background(VkCommandBuffer cmd);
  void draw_geometry(VkCommandBuffer cmd);
  void draw_imgui(VkCommandBuffer cmd, VkImageView targetImageView);
  void immediate_submit(std::function<void(VkCommandBuffer cmd)> &&function);

  void destroy_swapchain();
  void destroy_buffer(const AllocatedBuffer &buffer);
};
