﻿#pragma once

#include <vk_types.h>

class VulkanEngine
{
public:
	bool _isInitialized{false};
	int _frameNumber{0};
	bool stop_rendering{false};
	VkExtent2D _windowExtent{1700, 900};

	struct SDL_Window *_window{nullptr};

	static VulkanEngine &Get();

	VkInstance _instance;
	VkDebugUtilsMessengerEXT _debug_messenger;
	VkDevice _device;
	VkPhysicalDevice _chosenGPU;
	VkSurfaceKHR _surface;
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
};
