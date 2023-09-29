#include "Pipeline.hpp"
#include <fstream>

namespace OwnEngine {
	Pipeline::Pipeline(
		OwnEngine::Device& device,
		const std::string vertFilePath,
		const std::string fragFilePath,
		PipelineConfigInfo& configInfo) : _device{ device }
	{
		CreateGraphicsPipeline(vertFilePath, fragFilePath, configInfo);
	}

	Pipeline::~Pipeline()
	{
		vkDestroyShaderModule(_device.GetVkDevice(), _fragShaderModule, nullptr);
		vkDestroyShaderModule(_device.GetVkDevice(), _vertShaderModule, nullptr);
	}

	void Pipeline::CreateGraphicsPipeline(
		const std::string vertFilePath,
		const std::string fragFilePath,
		PipelineConfigInfo& configInfo) 
	{
		auto vertShaderCode = ReadFile(vertFilePath);
		auto fragShaderCode = ReadFile(fragFilePath);

		CreateShaderModule(vertShaderCode, &_vertShaderModule);
		CreateShaderModule(fragShaderCode, &_fragShaderModule);

		VkPipelineShaderStageCreateInfo shaderStageCreateInfos[2];
		shaderStageCreateInfos[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shaderStageCreateInfos[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
		shaderStageCreateInfos[0].module = _vertShaderModule;
		shaderStageCreateInfos[0].pName = "main";
		shaderStageCreateInfos[0].flags = 0;
		shaderStageCreateInfos[0].pNext = nullptr;
		shaderStageCreateInfos[0].pSpecializationInfo = nullptr;

		shaderStageCreateInfos[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shaderStageCreateInfos[0].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		shaderStageCreateInfos[0].module = _fragShaderModule;
		shaderStageCreateInfos[0].pName = "main";
		shaderStageCreateInfos[0].flags = 0;
		shaderStageCreateInfos[0].pNext = nullptr;
		shaderStageCreateInfos[0].pSpecializationInfo = nullptr;
	}

	std::vector<char> Pipeline::ReadFile(const std::string& filePath)
	{
		std::ifstream file(filePath, std::ios::ate | std::ios::binary);

		if (!file.is_open())
			throw std::runtime_error("failed to open file");

		size_t fileSize = static_cast<size_t>(file.tellg());
		std::vector< char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);
		file.close();

		return buffer;
	}

	void Pipeline::CreateShaderModule(const std::vector<char>& code, VkShaderModule *shaderModule)
	{
		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = code.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

		if (vkCreateShaderModule(_device.GetVkDevice(), &createInfo, nullptr, shaderModule))
			throw std::runtime_error("failed to create shader module");
	}
}