#include "VKDeviceMemory.h"
#include "VKResource.h"
#include "VKDevice.h"
#include "VKPhysicalDevice.h"
#include <iostream>
#include <cassert>

namespace VK
{
	DeviceMemory::DeviceMemory(void) :
		mTypeIndex(UINT_MAX), mMappedReaource(nullptr)
	{
	}

	DeviceMemory::~DeviceMemory(void)
	{
		//assert(mResources.size() == 0);
	}

	VkResult DeviceMemory::Allocate(Device* device, const VkMemoryAllocateInfo* info)
	{
		mDevice = device;
		mTypeIndex = info->memoryTypeIndex;
		mSize = info->allocationSize;
		PhysicalDevice* physical = device->GetPhysicalDevice();
		VkPhysicalDeviceMemoryProperties properties = {};
		physical->GetMemoryProperties(&properties);
		mMemoryTypeFlags = properties.memoryTypes[mTypeIndex].propertyFlags;
		mResult = VK_SUCCESS;
		return mResult;
	}

	VkResult DeviceMemory::AttachResource(Resource* resource)
	{
		auto iterator = std::find(mResources.begin(), mResources.end(), resource);
		if (iterator == mResources.end())
		{
			mResources.push_back(resource);
			mResult = VK_SUCCESS;
		}
		return mResult;
	}

	void DeviceMemory::RemoveResource(Resource* resource)
	{
		auto iterator = std::find(mResources.begin(), mResources.end(), resource);
		if (iterator != mResources.end())
		{
			mResources.erase(iterator);
		}
	}

	void* DeviceMemory::Map(VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags)
	{
		assert(mMappedReaource == nullptr);
		UINT8* data = nullptr;
		bool find = GetMapResource(offset, size);
		if (find && mMappedReaource != nullptr)
		{
			VkDeviceSize real_offset = offset - mMappedReaource->GetOffset();
			mRange = CD3DX12_RANGE(real_offset, real_offset + size);
			mMappedReaource->GetResource()->Map(0, &mRange, reinterpret_cast<void**>(&data));
		}
		else
		{
			std::cout << "can not find resource suit for it !" << std::endl;
		}
		return data;
	}

	void DeviceMemory::Unmap(void)
	{
		assert(mMappedReaource != nullptr);
		mMappedReaource->GetResource()->Unmap(0, &mRange);
		mMappedReaource = nullptr;
	}

	bool DeviceMemory::GetMapResource(VkDeviceSize offset, VkDeviceSize size)
	{
		for (auto resource : mResources)
		{
			bool contain = resource->Contain(offset, size);
			if (contain)
			{
				assert(mMappedReaource == nullptr);
				mMappedReaource = resource;
				return true;
			}
		}
		return false;
	}
}