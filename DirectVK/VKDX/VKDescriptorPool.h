#pragma once
#include "VKDeviceObject.h"
#include <vector>

namespace VK
{
	class DescriptorPool : public DeviceObject
	{
	public:
		DescriptorPool(void);
		virtual ~DescriptorPool(void) override;

	public:
		VkResult Create(Device* device, const VkDescriptorPoolCreateInfo* info);

	public:
		DescriptorSet * Allocate(const VkDescriptorSetAllocateInfo* info);

	public:
		void RemoveSet(DescriptorSet* set);
		void CreateResetPipelineState(void);

	protected:
		uint32_t mMaxSets;
		std::vector<DescriptorSet*> mDescriptorSets;
		std::vector<VkDescriptorPoolSize> mDescriptorPoolSizes;
	};
}

struct VkDescriptorPool_T final : public VK::DescriptorPool
{
	VkDescriptorPool_T(void) = default;
	virtual ~VkDescriptorPool_T(void) override final = default;
};
