#pragma once
#include <string>
#include "Device.hpp"

namespace OwnEngine {

	struct PipelineConfigInfo {
		PipelineConfigInfo() = default;
		PipelineConfigInfo(const PipelineConfigInfo&) = delete;
		PipelineConfigInfo& operator=(const PipelineConfigInfo&) = delete;
	};

	class Pipeline
	{
	public:
		Pipeline(
			OwnEngine::Device& device,
			const std::string vertFilePath,
			const std::string fragFilePath,
			PipelineConfigInfo& configInfo);
		~Pipeline();


	private:
		OwnEngine::Device& _device;

		static std::vector<char>ReadFile(const std::string& filePath);

		void CreateGraphicsPipeline(
			const std::string vertFilePath,
			const std::string fragFilePath,
			PipelineConfigInfo& configInfo);

		void CreateShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

		VkShaderModule _fragShaderModule;
		VkShaderModule _vertShaderModule;

	};
}
