#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include "Window.hpp"
#include <iostream>

namespace OwnEngine {

	Window::Window(int width, int height, std::string nameWindow) : _width{ width }, _height{ height }, _nameWindow{ nameWindow }
	{
		Initialize();
	}

	Window::~Window()
	{
		std::cout << "Destroy windows ownengine" << std::endl;
		glfwDestroyWindow(_window);
		glfwTerminate();
	}

	bool Window::ShouldWindowClose()
	{
		return glfwWindowShouldClose(_window);
	}

	void Window::Initialize()
	{
		std::cout << "Initilize window ownengine" << std::endl;
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		_window = glfwCreateWindow(_width, _height, _nameWindow.c_str(), nullptr, nullptr);

		//glfwMakeContextCurrent(_window);
	}

	void Window::WindowPollEvents()
	{
		glfwSwapBuffers(_window);
		glfwPollEvents();
	}

	void Window::CreateWindowSurface(VkInstance instance, VkSurfaceKHR *surface)
	{
		VkResult result = glfwCreateWindowSurface(instance, _window, nullptr, surface);
		if (result  != VK_SUCCESS)
			throw std::runtime_error("failed to create window surface");
	}
}
