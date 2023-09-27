#pragma once
#include "UtilsEngine.hpp"
#include <vulkan/vulkan_core.h>
#include <vector>
#include <string>
#include <optional>
#include "Window.hpp"

namespace OwnEngine
{
	/// @brief Struct families indices graphics and components presents
	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() const
		{
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	/// @brief Struct swap chain support details verify
	struct SwapChainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	/// @brief Device class
	/// @details Create device instance vulkan physical and logical
	/// also setting default dubugger application
	class Device
	{
	public:
		/// @brief Device constructor
		/// @param window
		/// @param nameApplication
		/// @param applicationVersion
		/// @param nameEngine
		/// @param engineVersion
		Device(
			OwnEngine::Window &window,
			std::string nameApplication,
			OwnEngine::MakeVersion applicationVersion,
			std::string nameEngine,
			OwnEngine::MakeVersion engineVersion);

		/// @brief Device destructor
		~Device();

		/// @brief Setting validation layers
		const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};
		/// @brief Setting extension names
		const std::vector<const char *> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME, "VK_KHR_portability_subset"};

#ifdef NDEBUG
		const bool _enableValidationLayers = false;
#else
		const bool _enableValidationLayers = true;
#endif // NDEBUG

		VkPhysicalDeviceProperties _deviceProperties;
		VkPhysicalDeviceFeatures _deviceFeatures;

		VkDevice GetVkDevice() const { return _device; }
		VkSurfaceKHR GetVkSurface() const { return _surface; }

		SwapChainSupportDetails GetSwapChainSupport() { return QuerySwapChainSupport(_physicalDevice); }
		QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
		VkPhysicalDevice GetVkPhysicalDevice() { return _physicalDevice; }

	private:
		VkInstance _instance;
		VkPhysicalDevice _physicalDevice;
		VkDevice _device;
		VkSurfaceKHR _surface;

		VkQueue _graphicsQueue;
		VkQueue _presentQueue;

		OwnEngine::Window _window;

		VkResult VkCreateInstanceApp(
			const VkInstanceCreateInfo *pCreateInfo,
			const VkAllocationCallbacks *pAllocator,
			VkInstance *instance);

		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageSeverityFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
			void *pUserData);

		VkResult CreateDebugUtilsMessengerEXT(
			VkInstance instance,
			const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
			VkAllocationCallbacks *pAllocator,
			VkDebugUtilsMessengerEXT *pDebugMessenger);

		void DestroyDebugUtilsMessengerEXT(
			VkInstance instance,
			VkDebugUtilsMessengerEXT pDebugMessenger,
			VkAllocationCallbacks *pAllocator);

		SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

		VkDebugUtilsMessengerEXT _debugMessenger;

		const std::string _nameApplication;
		const uint32_t _applicationVersion;
		const std::string _nameEngine;
		const uint32_t _engineVersion;

		void Initialize();
		void CreateInstance();
		void SetupDebugMessenger();
		void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
		void PickPhysicalDevice();
		void CreateLogicalDevice();
		void CreateSurface();

		bool CheckValidationLayerSupport();
		bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
		bool IsDeviceSuitable(VkPhysicalDevice device);
		std::vector<const char *> GetRequiredExtensions();
		int RateDeviceSuitability(VkPhysicalDevice device);
	};
}