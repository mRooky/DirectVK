#include "DXTexture.h"
#include "DXDevice.h"
#include <cassert>

namespace DX
{
	Texture::Texture(Device* device):
		Resource(device)
	{
	}

	Texture::~Texture(void)
	{
	}

	VkResult Texture::CreateInternal(void)
	{
		VkResult result = VK_INCOMPLETE;
		result = CreateVulkanImage();
		assert(result == VK_SUCCESS);
		result = AllocateVulkanMemory();
		assert(result == VK_SUCCESS);
		result = BindVulkanMemory();
		assert(result == VK_SUCCESS);
		return result;
	}

	VkResult Texture::BindVulkanMemory(void)
	{
		assert(mVulkanImage!= VK_NULL_HANDLE);
		assert(mVulkanMemory != VK_NULL_HANDLE);
		auto vulkan_device = mDevice->GetVulkanDevice();
		VkResult result = vkBindImageMemory(vulkan_device, mVulkanImage, mVulkanMemory, 0);
		return result;
	}

	VkResult Texture::CreateVulkanImage(void)
	{
		auto vulkan_device = mDevice->GetVulkanDevice();
		VkImageCreateInfo image_create_info = {};
		assert(false);
		VkResult result = vkCreateImage(vulkan_device, &image_create_info, nullptr, &mVulkanImage);
		return result;
	}
}