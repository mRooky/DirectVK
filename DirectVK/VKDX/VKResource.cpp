#include "VKResource.h"
#include "VKDeviceMemory.h"
#include "VKDevice.h"
#include "VKPhysicalDevice.h"
#include <cassert>

namespace VK
{
	Resource::Resource(void)
	{
		mResourceDesc = {};
	}

	Resource::~Resource(void)
	{
		mMemory = nullptr;
	}

	VkResult Resource::BindDeviceMemory(DeviceMemory* memory, VkDeviceSize offset)
	{
		assert(mMemory == nullptr);
		if (memory != nullptr)
		{
			mMemory = memory;
			mOffset = offset;
			uint32_t type_index = mMemory->GetMemoryTypeIndex();
			D3D12_HEAP_TYPE heap_type = mDevice->GetPhysicalDevice()->GetHeapType(type_index);
			CreateResource(heap_type);
			UINT64 real_size = GetRequiredIntermediateSize(mResource.Get(), 0, 1);
			assert(mSize == real_size);
			mResult = memory->AttachResource(this);
		}
		return mResult;
	}

	void Resource::GetMemoryRequirements(VkMemoryRequirements* requirements) const
	{
		if (requirements != nullptr)
		{
			*requirements = mReauirements;
		}
	}

	D3D12_RESOURCE_ALLOCATION_INFO Resource::GetAllocationInfo(void) const
	{
		auto device = mDevice->GetDevice();
		D3D12_RESOURCE_ALLOCATION_INFO info = device->GetResourceAllocationInfo(0, 1, &mResourceDesc);
		return info;
	}

	bool Resource::Contain(VkDeviceSize offset, VkDeviceSize size) const
	{
		return mOffset <= offset && mSize >= size;
	}

	void Resource::Barrarier(ID3D12GraphicsCommandList* command_list, D3D12_RESOURCE_STATES state)
	{
		if (mState != state)
		{
			D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(mResource.Get(), mState, state);
			command_list->ResourceBarrier(1, &barrier);
			mState = state;
		}
	}
}