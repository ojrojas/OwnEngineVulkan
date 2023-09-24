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
		/// @param width 
		/// @param height 
		/// @param nameWindow 
		Window(int width, int height, std::string nameWindow);
		
		/// @brief Destructor principal window
		~Window();

		/// @brief Method tell glfw window is closed
		/// @return should window is closed
		bool ShouldWindowClose();

		/// @brief get poll events application
		void WindowPollEvents();

		/// @brief Create surface vulkan
		/// @param instance  
		/// @param surface 
		void CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

		/// @brief Get framebuffer size window
		/// @param width
		/// @param height
		void GetFramebufferSize(int *width, int *height);
		
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
