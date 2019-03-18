#include "VKDescriptorPool.h"
#include "VKDescriptorSet.h"
#include <algorithm>
#include <cassert>

namespace VK
{
	DescriptorPool::DescriptorPool(void)
	{
	}

	DescriptorPool::~DescriptorPool(void)
	{
		for (auto set : mDescriptorSets)
		{
			delete set;
		}
		mDescriptorSets.clear();
	}

	VkResult DescriptorPool::Create(Device* device, const VkDescriptorPoolCreateInfo* info)
	{
		mDevice = device;
		mMaxSets = info->maxSets;
		mDescriptorPoolSizes.reserve(info->poolSizeCount);
		for (uint32_t i = 0; i < info->poolSizeCount; ++i)
		{
			const auto& pool_size = info->pPoolSizes[i];
			mDescriptorPoolSizes.push_back(pool_size);
		}
		mResult = mDescriptorPoolSizes.size() > 0 ? VK_SUCCESS : VK_INCOMPLETE;
		return mResult;
	}

	void DescriptorPool::RemoveSet(DescriptorSet* set)
	{
		auto iterator = std::find(mDescriptorSets.begin(), mDescriptorSets.end(), set);
		if (iterator != mDescriptorSets.end())
		{
			mDescriptorSets.erase(iterator);
			delete set;
		}
		else
		{
			assert(false && "DescriptorSet not Allocate form this Pool !");
		}
	}

	DescriptorSet * DescriptorPool::Allocate(const VkDescriptorSetAllocateInfo* info)
	{
		DescriptorSet * set = new DescriptorSet;
		VkResult result = set->Create(mDevice, info);
		assert(result == VK_SUCCESS);
		mDescriptorSets.push_back(set);
		return set;
	}
}