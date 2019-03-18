#pragma once
#include "VKDeviceObject.h"
#include <vector>
#include <mutex>

namespace VK
{
	class Resource;
	class DeviceMemory : public DeviceObject
	{
	public:
		DeviceMemory(void);
		virtual ~DeviceMemory(void) override;

	public:
		VkResult Allocate(Device* device, const VkMemoryAllocateInfo* info);

	public:
		void* Map(VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags = 0);
		void Unmap(void);

	public:
		VkResult AttachResource(Resource* resource);
		void RemoveResource(Resource* resource);

	public:
		inline uint32_t GetMemoryTypeIndex(void) const { return mTypeIndex; }

	private:
		bool GetMapResource(VkDeviceSize offset, VkDeviceSize size);

	protected:
		VkDeviceSize mSize;
		uint32_t mTypeIndex;
		uint32_t mMemoryTypeFlags;

	protected:
		Resource * mMappedReaource;
		std::vector<Resource*> mResources;

	protected:
		CD3DX12_RANGE mRange;
	};
}

struct VkDeviceMemory_T final : public VK::DeviceMemory
{
	VkDeviceMemory_T(void) = default;
	virtual ~VkDeviceMemory_T(void) override final = default;
};

