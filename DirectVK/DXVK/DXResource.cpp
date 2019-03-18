#include "DXResource.h"
#include "DXDevice.h"
#include "DXAdapter.h"
#include <cassert>

namespace DX
{
	Resource::Resource(Device* device):
		Memory(device)
	{
	}

	Resource::~Resource(void)
	{
		assert(false);
	}

	HRESULT Resource::Create(const D3D12_HEAP_PROPERTIES *pHeapProperties,
		D3D12_HEAP_FLAGS HeapFlags,
		const D3D12_RESOURCE_DESC *pDesc,
		D3D12_RESOURCE_STATES InitialResourceState,
		const D3D12_CLEAR_VALUE *pOptimizedClearValue)
	{
		mResourceDesc = *pDesc;
		mHeapProperties = *pHeapProperties;
		mClearValue = *pOptimizedClearValue;
		mResourceStates = InitialResourceState;
		mHeapFlags = HeapFlags;
		VkResult result = CreateInternal();
		return Device::GetResult(result);
	}

	HRESULT STDMETHODCALLTYPE Resource::Map(
		UINT Subresource,
		_In_opt_  const D3D12_RANGE *pReadRange,
		_Outptr_opt_result_bytebuffer_(_Inexpressible_("Dependent on resource"))  void **ppData)
	{
		assert(mVulkanMemory != VK_NULL_HANDLE);
		auto vulkan_device = mDevice->GetVulkanDevice();
		auto size = pReadRange->End - pReadRange->Begin;
		void* data = nullptr;
		VkImageAspectFlags image_aspect_flags = VK_IMAGE_ASPECT_COLOR_BIT;
		VkResult result = vkMapMemory(vulkan_device, mVulkanMemory, pReadRange->Begin, size, image_aspect_flags, &data);
		assert(result == VK_SUCCESS && data != nullptr);
		*ppData = data;
		return Device::GetResult(result);
	}

	void STDMETHODCALLTYPE Resource::Unmap(
		UINT Subresource,
		_In_opt_  const D3D12_RANGE *pWrittenRange)
	{
		assert(pWrittenRange != nullptr);
		assert(mVulkanMemory != VK_NULL_HANDLE);
		auto vulkan_device = mDevice->GetVulkanDevice();
		vkUnmapMemory(vulkan_device, mVulkanMemory);
		VkMappedMemoryRange mapped_memory_range = {};
		mapped_memory_range.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
		mapped_memory_range.memory = mVulkanMemory;
		mapped_memory_range.offset = pWrittenRange->Begin;
		mapped_memory_range.size = pWrittenRange->End - pWrittenRange->Begin;
		vkFlushMappedMemoryRanges(vulkan_device, 1, &mapped_memory_range);
	}

	HRESULT STDMETHODCALLTYPE Resource::WriteToSubresource(
		UINT DstSubresource,
		_In_opt_  const D3D12_BOX *pDstBox,
		_In_  const void *pSrcData,
		UINT SrcRowPitch,
		UINT SrcDepthPitch)
	{
		assert(false);
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE Resource::ReadFromSubresource(
		_Out_  void *pDstData,
		UINT DstRowPitch,
		UINT DstDepthPitch,
		UINT SrcSubresource,
		_In_opt_  const D3D12_BOX *pSrcBox)
	{
		assert(false);
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE Resource::GetHeapProperties(
		_Out_opt_  D3D12_HEAP_PROPERTIES *pHeapProperties,
		_Out_opt_  D3D12_HEAP_FLAGS *pHeapFlags)
	{
		*pHeapFlags = mHeapFlags;
		*pHeapProperties = mHeapProperties;
		return S_OK;
	}
}