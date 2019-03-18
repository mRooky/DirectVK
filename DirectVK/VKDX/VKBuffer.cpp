#include "VKBuffer.h"
#include "VKDevice.h"
#include "VKFormat.h"
#include "VKDeviceMemory.h"

namespace VK
{

	Buffer::Buffer(void)
	{
	}

	Buffer::~Buffer(void)
	{
	}

	VkResult Buffer::Create(Device* device, const VkBufferCreateInfo* info)
	{
		mDevice = device;
		mSize = info->size;
		mUsage = info->usage;
		CreateRequirements();
		return mResult;
	}

	void Buffer::CreateRequirements(void)
	{
		mReauirements.size = mSize;
		mReauirements.memoryTypeBits = 0x00000001;
		if ((mUsage & VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT) == 0)
		{
			mReauirements.memoryTypeBits |= 0x00000002;
		}
		mReauirements.alignment = 0;
		mResult = VK_SUCCESS;
	}

	void Buffer::CreateResource(D3D12_HEAP_TYPE type)
	{
		CD3DX12_HEAP_PROPERTIES heap_properties(type);
		mResourceDesc = CD3DX12_RESOURCE_DESC::Buffer(mSize);
		D3D12_RESOURCE_STATES usage = D3D12_RESOURCE_STATE_GENERIC_READ;
		HRESULT result = mDevice->GetDevice()->CreateCommittedResource(&heap_properties,
			D3D12_HEAP_FLAG_NONE, &mResourceDesc, usage, nullptr, IID_PPV_ARGS(&mResource));
		mResult = SUCCEEDED(result) ? VK_SUCCESS : VK_INCOMPLETE;
	}

	D3D12_VERTEX_BUFFER_VIEW Buffer::GetVertexView(void) const
	{
		D3D12_VERTEX_BUFFER_VIEW vertex_buffer_view = {};
		if (mMemory != nullptr)
		{
			vertex_buffer_view.BufferLocation = mResource->GetGPUVirtualAddress() + mOffset;
			vertex_buffer_view.StrideInBytes = 0;	//deffered setting in DXCmdBindVertexBuffers from pipeline
			vertex_buffer_view.SizeInBytes = static_cast<UINT>(mSize);
		}
		return vertex_buffer_view;
	}

	D3D12_INDEX_BUFFER_VIEW Buffer::GetIndexView(void) const
	{
		D3D12_INDEX_BUFFER_VIEW index_buffer_view = {};
		if (mMemory != nullptr)
		{
			index_buffer_view.BufferLocation = mResource->GetGPUVirtualAddress() + mOffset;
			index_buffer_view.Format = Format::GetFormat(mFormat);
			index_buffer_view.SizeInBytes = static_cast<UINT>(mSize);
		}
		return index_buffer_view;
	}

	D3D12_SHADER_RESOURCE_VIEW_DESC Buffer::GetResourceView(void) const
	{
		D3D12_SHADER_RESOURCE_VIEW_DESC resource_view_desc = {};
		if (mMemory != nullptr)
		{
			resource_view_desc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
			resource_view_desc.Format = DXGI_FORMAT_UNKNOWN;
			resource_view_desc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
			resource_view_desc.Buffer.FirstElement = mResource->GetGPUVirtualAddress() + mOffset;
			resource_view_desc.Buffer.NumElements = 0;						//error
			resource_view_desc.Buffer.StructureByteStride = 0;				//error
			resource_view_desc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
		}
		return resource_view_desc;
	}

	D3D12_CONSTANT_BUFFER_VIEW_DESC Buffer::GetConstView(void) const
	{
		D3D12_CONSTANT_BUFFER_VIEW_DESC const_buffer_view = {};
		if (mMemory != nullptr)
		{
			const_buffer_view.BufferLocation = mResource->GetGPUVirtualAddress() + mOffset;
			const_buffer_view.SizeInBytes = (static_cast<UINT>(mSize) + 255) & ~255;
		}
		return const_buffer_view;
	}
}
