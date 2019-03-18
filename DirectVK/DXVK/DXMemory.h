#pragma once
#include "DXObject.h"

namespace DX
{
	class Memory : public Object
	{
	public:
		explicit Memory(Device* device);
		virtual ~Memory(void);

	public:
		inline VkDeviceMemory GetVulkanDeviceMemory(void) const { return mVulkanMemory; }

	public:
		static VkMemoryPropertyFlags GetMemoryPropertyFlags(D3D12_HEAP_TYPE type);

	protected:
		VkResult AllocateVulkanMemory(void);

	protected:
		VkDeviceSize GetVulkanMemorySize(void) const;

	protected:
		VkDeviceMemory mVulkanMemory = VK_NULL_HANDLE;

	protected:
		D3D12_CLEAR_VALUE mClearValue = {};
		D3D12_RESOURCE_DESC mResourceDesc = {};
		D3D12_RESOURCE_STATES mResourceStates = {};
		D3D12_HEAP_PROPERTIES mHeapProperties = {};
		D3D12_HEAP_FLAGS mHeapFlags = D3D12_HEAP_FLAG_NONE;
	};
}
