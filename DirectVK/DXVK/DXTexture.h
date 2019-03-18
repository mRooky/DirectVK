#pragma once

#include "DXResource.h"

namespace DX
{
	class Texture : public Resource
	{
	public:
		explicit Texture(Device* device);
		virtual ~Texture(void) override;

	protected:
		virtual VkResult CreateInternal(void) override;

	protected:
		VkResult BindVulkanMemory(void);
		VkResult CreateVulkanImage(void);

	protected:
		VkImage mVulkanImage = VK_NULL_HANDLE;
	};
}
