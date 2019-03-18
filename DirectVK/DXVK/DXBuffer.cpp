#include "DXBuffer.h"
#include "DXDevice.h"
#include "DXAdapter.h"
#include <cassert>

namespace DX
{
	Buffer::Buffer(Device* device):
		Resource(device)
	{
	}
	
	Buffer::~Buffer(void)
	{
	}

	VkResult Buffer::CreateInternal(void)
	{
		VkResult result = VK_INCOMPLETE;
		result = CreateVulkanBuffer();
		assert(result == VK_SUCCESS);
		result = AllocateVulkanMemory();
		assert(result == VK_SUCCESS);
		result = BindVulkanMemory();
		assert(result == VK_SUCCESS);
		return result;
	}

	VkResult Buffer::BindVulkanMemory(void)
	{
		assert(mVulkanBuffer != VK_NULL_HANDLE);
		assert(mVulkanMemory != VK_NULL_HANDLE);
		auto vulkan_device = mDevice->GetVulkanDevice();
		VkResult result = vkBindBufferMemory(vulkan_device, mVulkanBuffer, mVulkanMemory, 0);
		return result;
	}

	VkResult Buffer::CreateVulkanBuffer(void)
	{
		auto vulkan_device = mDevice->GetVulkanDevice();

		VkBufferCreateInfo buffer_create_info = {};
		assert(false);

		VkResult result = vkCreateBuffer(vulkan_device, &buffer_create_info, nullptr, &mVulkanBuffer);
		return result;
	}
}