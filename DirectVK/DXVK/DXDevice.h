#pragma once

#include "DXHeader.h"

namespace DX
{
	class Adapter;
	class Device : public ID3D12Device
	{
	public:
		explicit Device(Adapter* adapter);
		virtual ~Device(void);

	public:
		virtual HRESULT STDMETHODCALLTYPE CreateCommittedResource(
			_In_  const D3D12_HEAP_PROPERTIES *pHeapProperties,
			D3D12_HEAP_FLAGS HeapFlags,
			_In_  const D3D12_RESOURCE_DESC *pDesc,
			D3D12_RESOURCE_STATES InitialResourceState,
			_In_opt_  const D3D12_CLEAR_VALUE *pOptimizedClearValue,
			REFIID riidResource,
			_COM_Outptr_opt_  void **ppvResource) override;

	public:
		inline Adapter* GetAdapter(void) const { return mAdapter; }
		inline VkDevice GetVulkanDevice(void) const { return mVulkanDevice; }

	public:
		static HRESULT GetResult(VkResult result);

	protected:
		Adapter* mAdapter = nullptr;
		VkDevice mVulkanDevice = VK_NULL_HANDLE;
	};
}
