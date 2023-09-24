#pragma once
#include <vulkan/vulkan_core.h>
#include <GLFW/glfw3.h>
#include <string>

namespace OwnEngine {

	/// @brief Window 
	/// @details Window create instance glfw
	class Window
	{
	public:

		/// @brief Constructor create principal window
		/// @param width size width principal window
		/// @param height size height principal window
		/// @param nameWindow name principal window
		Window(int width, int height, std::string nameWindow);
		
		/// @brief Destructor principal window
		~Window();

		/// @brief Method tell glfw window is closed
		/// @return 
		bool ShouldWindowClose();
		/// @brief get poll events application
		void WindowPollEvents();
		/// @brief Create surface vulkan
		/// @param instance Instance vulkan 
		/// @param surface Surface vulkan application
		void CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
		
	private:
		/// @brief Instance window glfw
		GLFWwindow* _window;

		/// @brief size const width of principal window
		const int _width;
		/// @brief size const height of principal window
		const int _height;
		/// @brief name const principal window
		const std::string _nameWindow;

		/// @brief Initialize components and hints glfw
		void Initialize();
	};
}
