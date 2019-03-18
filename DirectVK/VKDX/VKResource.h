#pragma once
#include "VKDeviceObject.h"

namespace VK
{
	class Resource : public DeviceObject
	{
		friend class Device;
		friend class Swapchain;
		friend class DeviceMemory;
	protected:
		Resource(void);
		virtual ~Resource(void) override;

	public:
		VkResult BindDeviceMemory(DeviceMemory* memory, VkDeviceSize offset);
		void GetMemoryRequirements(VkMemoryRequirements* requirements) const;
		D3D12_RESOURCE_ALLOCATION_INFO GetAllocationInfo(void) const;
		void Barrarier(ID3D12GraphicsCommandList* command_list, D3D12_RESOURCE_STATES state);

	public:
		bool Contain(VkDeviceSize offset, VkDeviceSize size) const;

	public:
		inline VkDeviceSize GetSize(void) const { return mSize; }
		inline VkDeviceSize GetOffset(void) const { return mOffset; }
		inline ID3D12Resource* GetResource(void) const { return mResource.Get(); }
		D3D12_RESOURCE_STATES GetResourceState(void) const { return mState; }

	protected:
		virtual void CreateRequirements(void) = 0;
		virtual void CreateResource(D3D12_HEAP_TYPE type) = 0;

	protected:
		DeviceMemory * mMemory;
		VkDeviceSize mSize;
		VkDeviceSize mOffset;
		VkDeviceSize mAlignment;
		VkFormat mFormat;
		VkMemoryRequirements mReauirements;

	protected:
		CD3DX12_RESOURCE_DESC mResourceDesc;
		ComPtr<ID3D12Resource> mResource;
		D3D12_RESOURCE_STATES mState;
	};
}


