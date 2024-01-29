#pragma once

#include "vk_types.h"

class VulkanEngine {
public:
  bool _isInitialized{false};
  int _frameNumber{0};
  bool stop_rendering{false};
  VkExtent2D _windowExtent{1700, 900};

  struct SDL_Window *_window{nullptr};

  static VulkanEngine &Get();

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

  // initializes everything in the engine
  void init();

  // shuts down the engine
  void cleanup();

  // draw loop
  void draw();

  // run main loop
  void run();

private:
  void init_vulkan();
  void init_swapchain();
  void init_commands();
  void init_sync_structures();

  void create_swapchain(uint32_t width, uint32_t height);
  void destroy_swapchain();
};

struct FrameData {
  VkCommandPool _commandPool;
  VkCommandBuffer _mainCommandBuffer;

  VkSemaphore _swapchainSemaphore, _renderSemaphore;
  VkFence _renderFence;
};

constexpr unsigned int FRAME_OVERLAP = 2;
