#pragma once
#include <vulkan/vulkan_core.h>
#include <vector>
#include "Device.hpp"

namespace OwnEngine
{
	/// @Brief SwapChain class
	class SwapChain
	{
	public:
		SwapChain(OwnEngine::Device &device, VkExtent2D windowExtent);
		~SwapChain();
	private:

		OwnEngine::Device &_device;
		VkExtent2D _windowExtent;
		VkSwapchainKHR _swapChain;

		std::vector<VkImage> _swapChainImages;
		VkFormat _swapChainImageFormat;
		VkExtent2D _swapChainExtent;
		std::vector<VkImageView> _swapChainImageViews;

		void Initialize();
		void CreateSwapChain();
		void CreateImageViews();

		VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> availableFormats);
		VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	};
}
