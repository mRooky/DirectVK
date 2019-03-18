#pragma once
#include "DXResource.h"

namespace DX
{
	class Buffer : public Resource
	{
	public:
		explicit Buffer(Device* device);
		virtual ~Buffer(void) override;

	protected:
		virtual VkResult CreateInternal(void) override;

	public:
		inline VkBuffer GetVulkanBuffer(void) const { return mVulkanBuffer; }
		inline VkBufferCreateInfo GetVulkanBufferCreateInfo(void) const { return mBufferCreateInfo; }

	protected:
		VkResult BindVulkanMemory(void);
		VkResult CreateVulkanBuffer(void);

	protected:
		VkBuffer mVulkanBuffer = VK_NULL_HANDLE;
		VkBufferCreateInfo mBufferCreateInfo = {};
	};
}
