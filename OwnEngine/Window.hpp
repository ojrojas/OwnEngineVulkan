#pragma once
#include <vulkan/vulkan_core.h>
#include <GLFW/glfw3.h>
#include <string>

namespace OwnEngine {

	class Window
	{
	public:
		Window(int width, int height, std::string nameWindow);
		~Window();

		bool ShouldWindowClose();
		void WindowPollEvents();
		void CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
	private:
		GLFWwindow* _window;

		const int _width;
		const int _height;
		const std::string _nameWindow;

		void Initialize();
	};
}
