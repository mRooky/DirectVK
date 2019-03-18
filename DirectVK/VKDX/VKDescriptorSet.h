#pragma once
#include "VKDeviceObject.h"
#include <vector>

namespace VK
{
	class DescriptorSet : public DeviceObject
	{
		friend class DescriptorPool;
	protected:
		DescriptorSet(void);
		virtual ~DescriptorSet(void) override;

	public:
		VkResult Create(Device* device, const VkDescriptorSetAllocateInfo* info);

	public:
		VkResult Write(VkDescriptorType type, uint32_t binding, uint32_t count, const VkDescriptorBufferInfo* buffer_infos);
		VkResult Write(VkDescriptorType type, uint32_t binding, uint32_t count, const VkDescriptorImageInfo* image_infos);

	public:
		inline DescriptorPool* GetDescriptorPool(void) const { return mDescriptorPool; }

	private:
		void CreateDescriptorHeap(void);

	protected:
		DescriptorPool * mDescriptorPool;
		std::vector<DescriptorSetLayout*> mLayouts;

	protected:
		typedef ComPtr<ID3D12DescriptorHeap> DescriptorHeapPtr;
		std::vector<DescriptorHeapPtr> mDescriptorHeaps;
	};
}

struct VkDescriptorSet_T final : public VK::DescriptorSet
{
private:
	VkDescriptorSet_T(void) = default;
	virtual ~VkDescriptorSet_T(void) override final = default;
};
