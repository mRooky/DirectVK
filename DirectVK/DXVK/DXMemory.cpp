#include "DXMemory.h"
#include "DXDevice.h"
#include "DXAdapter.h"
#include <cassert>

namespace DX
{
	Memory::Memory(Device* device):
		Object(device)
	{
	}

	Memory::~Memory(void)
	{
		auto vk_device = mDevice->GetVulkanDevice();
		vkFreeMemory(vk_device, mVulkanMemory, nullptr);
		mDevice = nullptr;
		mVulkanMemory = VK_NULL_HANDLE;
	}

	VkResult Memory::AllocateVulkanMemory(void)
	{
		auto vulkan_device = mDevice->GetVulkanDevice();
		VkDeviceSize memory_size = GetVulkanMemorySize();
		VkMemoryPropertyFlags memory_property_flags = GetMemoryPropertyFlags(mHeapProperties.Type);
		uint32_t memory_type_index = mDevice->GetAdapter()->GetMemoryTypeIndex(memory_property_flags);

		VkMemoryAllocateInfo memory_allocate_info = {};
		memory_allocate_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO;
		memory_allocate_info.allocationSize = memory_size;
		memory_allocate_info.memoryTypeIndex = memory_type_index;

		VkResult result = vkAllocateMemory(vulkan_device, &memory_allocate_info, nullptr, &mVulkanMemory);

		return result;
	}

	VkDeviceSize Memory::GetVulkanMemorySize(void) const
	{
		VkDeviceSize memory_size = 0;
		switch (mResourceDesc.Dimension)
		{
		case D3D12_RESOURCE_DIMENSION_BUFFER:
			memory_size = mResourceDesc.Width;
			break;
		case D3D12_RESOURCE_DIMENSION_TEXTURE1D:
			break;
		case D3D12_RESOURCE_DIMENSION_TEXTURE2D:
			break;
		case D3D12_RESOURCE_DIMENSION_TEXTURE3D:
			break;
		default:
			assert(false);
			break;
		}
		assert(memory_size != 0);
		return memory_size;
	}

	VkMemoryPropertyFlags Memory::GetMemoryPropertyFlags(D3D12_HEAP_TYPE type)
	{
		VkMemoryPropertyFlags flags = 0;
		switch (type)
		{
		case D3D12_HEAP_TYPE_DEFAULT:
			flags |= VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
			break;
		case D3D12_HEAP_TYPE_UPLOAD:
			flags |= VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
			flags |= VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
			break;
		case D3D12_HEAP_TYPE_READBACK:
			flags |= VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
			flags |= VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
			break;
		case D3D12_HEAP_TYPE_CUSTOM:
			assert(false);
			break;
		default:
			assert(false);
			break;
		}
		return flags;
	}
}