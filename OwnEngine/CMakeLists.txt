add_library(OwnEngine STATIC "Window.cpp" "Window.hpp" "Device.hpp" "Device.cpp" "UtilsEngine.hpp" "SwapChain.cpp" "SwapChain.hpp" "Pipeline.cpp" "Pipeline.hpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET OwnEngine PROPERTY CXX_STANDARD 20)
endif()

if(WIN32)
	message(STATUS "configuring paths to windows")
	set(GLFW_DIR_INCLUDES "${GLFW_PATH_WIN}/include")
	set(GLFW_DIR_LIBS "${GLFW_PATH_WIN}/lib-vc2022")
	set(VULKAN_DIR_INCLUDES "${VULKAN_PATH_WIN}/include")
	set(VULKAN_DIR_LIBS "${VULKAN_PATH_WIN}/lib")
else()
	message(STATUS "configuring paths to unix based systems")
	set(GLFW_DIR_INCLUDES "${GLFW_PATH}/include")
	set(GLFW_DIR_LIBS "${GLFW_PATH}/lib")
	set(VULKAN_DIR_INCLUDES "${VULKAN_PATH}/include/vulkan")
	set(VULKAN_DIR_LIBS "${VULKAN_PATH}/lib")
endif()

set(STATUS "Including directories ${GLFW_DIR_INCLUDES} - ${VULKAN_DIR_INCLUDES}")
include_directories(
	"${GLFW_DIR_INCLUDES}"
	"${VULKAN_DIR_INCLUDES}"
)

set(STATUS "Including target directories:")
set(STATUS "${GLFW_DIR_INCLUDES}")
set(STATUS "${VULKAN_DIR_INCLUDES}")
set(STATUS "${GLFW_DIR_LIBS}")
set(STATUS "${VULKAN_DIR_LIBS}")

target_include_directories(OwnEngine PUBLIC 
	"${GLFW_DIR_INCLUDES}"
	"${VULKAN_DIR_INCLUDES}"
	"${GLFW_DIR_LIBS}"
	"${VULKAN_DIR_LIBS}"
)

set(STATUS "Including libs directories:")
set(STATUS ${GLFW_DIR_LIBS})
set(STATUS ${VULKAN_DIR_LIBS})

target_link_directories(OwnEngine PUBLIC 
	"${GLFW_DIR_LIBS}"
	"${VULKAN_DIR_LIBS}"
)

if(WIN32)
	set(STATUS "Including libraries:")
	set(STATUS "${OwnEngine}, glfw3 vulkan-1")
	target_link_libraries(OwnEngine glfw3 vulkan-1)
elseif(APPLE)
	set(STATUS "Including libraries:")
	set(STATUS "${OwnEngine}, glfw.3 vulkan")
	target_link_libraries(OwnEngine glfw.3 vulkan.1)
else(UNIX)
	set("there is no implementation or configuration")
endif()