#pragma once
#include "VKDispatchable.h"
#include <vector>

namespace VK
{
	class Resource;
	class Device : public Dispatchable
	{
		friend class PhysicalDevice;
	public:
		Device(void);
		virtual ~Device(void) override;

	public:
		VkResult Create(PhysicalDevice* physical, const VkDeviceCreateInfo* info);
		VkResult GetDeviceQueue(uint32_t family, uint32_t index, VkQueue* queues);

	public:
		Buffer * CreateBuffer(const VkBufferCreateInfo* info);
		Image * CreateImage(const VkImageCreateInfo* info);

	public:
		void RemoveResource(Resource* resource);

	public:
		inline ID3D12Device* GetDevice(void) const { return mDevice.Get(); }
		inline PhysicalDevice* GetPhysicalDevice(void) const { return mPhysicalDevice; }

	private:
		void CreateQueue(const VkDeviceCreateInfo* info);

	protected:
		ComPtr<ID3D12Device> mDevice;
		D3D_FEATURE_LEVEL mFeatureLevel;

	protected:
		PhysicalDevice * mPhysicalDevice;
		std::vector<Resource*> mResources;
		std::vector<QueueFamily*> mQueueFamilies;

	};
}

struct VkDevice_T final : public VK::Device
{
	VkDevice_T(void) = default;
	virtual ~VkDevice_T(void) final override = default;
};
