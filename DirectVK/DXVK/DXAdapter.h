#pragma once
#include "DXHeader.h"
namespace DX
{
	class Adapter
	{
	public:
		Adapter(void);
		~Adapter(void);

	public:
		uint32_t GetMemoryTypeIndex(VkMemoryPropertyFlags flags);

	public:
		inline VkPhysicalDevice GetVulkanPhysicalDevice(void) const { return mVulkanPhysicalDevice; }

	protected:
		VkPhysicalDevice mVulkanPhysicalDevice = VK_NULL_HANDLE;
	};
}
