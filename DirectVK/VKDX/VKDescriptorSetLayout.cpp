#include "VKDescriptorSetLayout.h"

namespace VK
{
	DescriptorSetLayout::DescriptorSetLayout(void)
	{
	}

	DescriptorSetLayout::~DescriptorSetLayout(void)
	{
	}

	VkResult DescriptorSetLayout::Create(Device* device, const VkDescriptorSetLayoutCreateInfo* info)
	{
		mDevice = device;
		mSetLayoutBindings.reserve(info->bindingCount);
		for (uint32_t i = 0; i < info->bindingCount; ++i)
		{
			const auto& binding = info->pBindings[i];
			mSetLayoutBindings.push_back(binding);
		}
		mResult = mSetLayoutBindings.size() > 0 ? VK_SUCCESS : VK_INCOMPLETE;
		return mResult;
	}
}