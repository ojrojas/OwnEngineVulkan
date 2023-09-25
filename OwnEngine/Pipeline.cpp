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

	void Pipeline::CreateGraphicsPipeline(
		const std::string vertFilePath,
		const std::string fragFilePath,
		PipelineConfigInfo& configInfo) 
	{

	}

	std::vector<char> Pipeline::ReadFile(const std::string& filePath)
	{
		std::ifstream file(filePath, std::ios::ate | std::ios::binary);

		if (!file.is_open())
			throw std::runtime_error("failed to open file");

		size_t fileSize = static_cast<size_t>(file.tellg());
		std::vector< char> buffer(fileSize);
		return buffer;
	}
}