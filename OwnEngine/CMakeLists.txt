add_library(OwnEngine STATIC "Window.cpp" "Window.hpp" "Device.hpp" "Device.cpp" "UtilsEngine.hpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OwnEngine PROPERTY CXX_STANDARD 20)
endif()

include_directories(
	"D:/glfw-3.3.8.bin.WIN64/include"
	"D:/SDKVulkan/Include"
)

target_include_directories(OwnEngine PUBLIC 
	"D:/glfw-3.3.8.bin.WIN64/include"
	"D:/SDKVulkan/Include"
	"D:/glfw-3.3.8.bin.WIN64/lib-vc2022"
	"D:/SDKVulkan/Lib"
)

target_link_directories(OwnEngine PUBLIC 
	"D:/glfw-3.3.8.bin.WIN64/lib-vc2022"
	"D:/SDKVulkan/Lib"
)

target_link_libraries(OwnEngine glfw3 vulkan-1)