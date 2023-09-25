#include "SwapChain.hpp"
#include <limits>
#include <algorithm>

namespace OwnEngine
{
	SwapChain::SwapChain(OwnEngine::Device &device, VkExtent2D windowExtent) : _device{ device }, _windowExtent{ windowExtent }
	{
		Initialize();
	}

	SwapChain::~SwapChain()
	{
		for (auto imageView : _swapChainImageViews)
			vkDestroyImageView(_device.GetVkDevice(), imageView, nullptr);
		vkDestroySwapchainKHR(_device.GetVkDevice(), _swapChain, nullptr);

	}

	void SwapChain::Initialize()
	{
		CreateSwapChain();
	}

	VkSurfaceFormatKHR SwapChain::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> availableFormats)
	{
		for (const auto& availableFormat : availableFormats)
		{
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
				return availableFormat;
		}

		return availableFormats.at(0);
	}

	VkPresentModeKHR SwapChain::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
	{
		for (const auto& availablePresentMode : availablePresentModes)
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
				return availablePresentMode;

		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D SwapChain::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
	{
		if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
			return capabilities.currentExtent;
		else
		{
			VkExtent2D actualExtent = _windowExtent;

			actualExtent.width = std::clamp(
				actualExtent.width,
				capabilities.minImageExtent.width,
				capabilities.maxImageExtent.width
			);

			actualExtent.height = std::clamp(
				actualExtent.height,
				capabilities.minImageExtent.height,
				capabilities.maxImageExtent.height
			);

			return actualExtent;
		}
	}

	void SwapChain::CreateSwapChain()
	{
		SwapChainSupportDetails swapChainSupport = _device.GetSwapChainSupport();
		VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
		VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
		VkExtent2D extent = ChooseSwapExtent(swapChainSupport.capabilities);

		uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

		if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
			imageCount = swapChainSupport.capabilities.maxImageCount;

		VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = _device.GetVkSurface();
		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		QueueFamilyIndices indices = _device.FindQueueFamilies(_device.GetVkPhysicalDevice());
		uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

		if (indices.graphicsFamily != indices.presentFamily)
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount = 0;
			createInfo.pQueueFamilyIndices = nullptr;
		}

		createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;
		createInfo.oldSwapchain = VK_NULL_HANDLE;

		if (vkCreateSwapchainKHR(_device.GetVkDevice(), &createInfo, nullptr, &_swapChain) != VK_SUCCESS)
			throw std::runtime_error("failes to create swap chain");

		vkGetSwapchainImagesKHR(_device.GetVkDevice(), _swapChain, &imageCount, nullptr);
		_swapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(_device.GetVkDevice(), _swapChain, &imageCount, _swapChainImages.data());

		_swapChainImageFormat = surfaceFormat.format;
		_swapChainExtent = extent;
	}

	void SwapChain::CreateImageViews()
	{
		_swapChainImageViews.resize(_swapChainImages.size());
		for (size_t i = 0; i < _swapChainImages.size(); i++)
		{
			VkImageViewCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			createInfo.image = _swapChainImages[i];
			
			createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			createInfo.format = _swapChainImageFormat;

			createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

			createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.baseMipLevel = 0;
			createInfo.subresourceRange.levelCount = 1;
			createInfo.subresourceRange.baseArrayLayer = 0;
			createInfo.subresourceRange.layerCount = 1;

			if (vkCreateImageView(_device.GetVkDevice(), &createInfo, nullptr, &_swapChainImageViews[i]) != VK_SUCCESS)
				throw std::runtime_error("failed to create image views");





		}
	}
}