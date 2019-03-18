#pragma once

#include "DXMemory.h"

namespace DX
{
	class Resource : public Memory, public ID3D12Resource
	{
	public:
		explicit Resource(Device* device);
		virtual ~Resource(void);

	public:
		HRESULT Create(const D3D12_HEAP_PROPERTIES *pHeapProperties,
			D3D12_HEAP_FLAGS HeapFlags,
			const D3D12_RESOURCE_DESC *pDesc,
			D3D12_RESOURCE_STATES InitialResourceState,
			const D3D12_CLEAR_VALUE *pOptimizedClearValue);

	public:
		virtual HRESULT STDMETHODCALLTYPE Map(
			UINT Subresource,
			_In_opt_  const D3D12_RANGE *pReadRange,
			_Outptr_opt_result_bytebuffer_(_Inexpressible_("Dependent on resource"))  void **ppData) override;

		virtual void STDMETHODCALLTYPE Unmap(
			UINT Subresource,
			_In_opt_  const D3D12_RANGE *pWrittenRange) override;
		virtual D3D12_RESOURCE_DESC STDMETHODCALLTYPE GetDesc(void) override { return mResourceDesc; }

		virtual HRESULT STDMETHODCALLTYPE WriteToSubresource(
			UINT DstSubresource,
			_In_opt_  const D3D12_BOX *pDstBox,
			_In_  const void *pSrcData,
			UINT SrcRowPitch,
			UINT SrcDepthPitch) override;

		virtual HRESULT STDMETHODCALLTYPE ReadFromSubresource(
			_Out_  void *pDstData,
			UINT DstRowPitch,
			UINT DstDepthPitch,
			UINT SrcSubresource,
			_In_opt_  const D3D12_BOX *pSrcBox) override;

		virtual HRESULT STDMETHODCALLTYPE GetHeapProperties(
			_Out_opt_  D3D12_HEAP_PROPERTIES *pHeapProperties,
			_Out_opt_  D3D12_HEAP_FLAGS *pHeapFlags) override;

	protected:
		virtual VkResult CreateInternal(void) = 0;

	protected:
		D3D12_CPU_DESCRIPTOR_HANDLE mDescriptorHandle = {};
		
	};
}
