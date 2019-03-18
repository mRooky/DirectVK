#pragma once
#include "VKDeviceObject.h"
#include <vector>

namespace VK
{
	class DescriptorSetLayout : public DeviceObject
	{
	public:
		DescriptorSetLayout(void);
		virtual ~DescriptorSetLayout(void) override;

	public:
		VkResult Create(Device* device, const VkDescriptorSetLayoutCreateInfo* info);

	public:
		inline size_t GetBindingCount(void) const { return mSetLayoutBindings.size(); }
		inline const VkDescriptorSetLayoutBinding& GetBinding(uint32_t index) const { return mSetLayoutBindings.at(index); }

	protected:
		std::vector<VkDescriptorSetLayoutBinding> mSetLayoutBindings;
	};
}

struct VkDescriptorSetLayout_T final : public VK::DescriptorSetLayout
{
	VkDescriptorSetLayout_T(void) = default;
	virtual ~VkDescriptorSetLayout_T(void) override final = default;
};

