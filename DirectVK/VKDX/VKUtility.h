#pragma once
#include "VKFormat.h"

namespace VK
{
	class Utility
	{
	public:
		Utility(void) = delete;
		~Utility(void) = delete;

	public:
		static D3D12_RESOURCE_DIMENSION GetDimension(VkImageType type);
		static D3D12_SRV_DIMENSION GetDimension(VkImageViewType type);
		static D3D12_INPUT_CLASSIFICATION GetInputRate(VkVertexInputRate rate);
		static uint32_t GetLog2(uint32_t value);
		static uint32_t GetMipmapLevelSize(uint32_t width, uint32_t height, uint32_t level);
		static uint32_t GetMipmapSize(uint32_t width, uint32_t height, uint32_t levels);
	};
}
