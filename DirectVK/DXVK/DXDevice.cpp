#include "DXDevice.h"
#include <cassert>

namespace DX
{
	Device::Device(Adapter* adapter):
		mAdapter(adapter)
	{
		assert(mAdapter != nullptr);
	}

	Device::~Device(void)
	{
		mAdapter = nullptr;
	}

	HRESULT STDMETHODCALLTYPE Device::CreateCommittedResource(
		_In_  const D3D12_HEAP_PROPERTIES *pHeapProperties,
		D3D12_HEAP_FLAGS HeapFlags,
		_In_  const D3D12_RESOURCE_DESC *pDesc,
		D3D12_RESOURCE_STATES InitialResourceState,
		_In_opt_  const D3D12_CLEAR_VALUE *pOptimizedClearValue,
		REFIID riidResource,
		_COM_Outptr_opt_  void **ppvResource)
	{
		assert(false);
		return S_OK;
	}

	HRESULT Device::GetResult(VkResult result)
	{
		assert(false);
		return S_OK;
	}
}