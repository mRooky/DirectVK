#include "VKDescriptorSet.h"
#include "VKDescriptorPool.h"
#include "VKDescriptorSetLayout.h"
#include "VKDevice.h"
#include "VKSampler.h"
#include "VKImageView.h"
#include "VKImage.h"
#include "VKBuffer.h"
#include <cassert>

namespace VK
{
	DescriptorSet::DescriptorSet(void)
	{
	}

	DescriptorSet::~DescriptorSet(void)
	{
	}

	VkResult DescriptorSet::Create(Device* device, const VkDescriptorSetAllocateInfo* info)
	{
		mDevice = device;
		mDescriptorPool = info->descriptorPool;
		for (uint32_t i = 0; i < info->descriptorSetCount; ++i)
		{
			auto set_layout = info->pSetLayouts[i];
			mLayouts.push_back(set_layout);
		}
		CreateDescriptorHeap();
		return mResult;
	}

	void DescriptorSet::CreateDescriptorHeap(void)
	{
		D3D12_DESCRIPTOR_HEAP_DESC heap_desc = {};
		mDescriptorHeaps.reserve(mLayouts.size());
		for (uint32_t i = 0; i < mLayouts.size(); ++i)
		{
			DescriptorSetLayout* layout = mLayouts.at(i);
			DescriptorHeapPtr heap_ptr;
			heap_desc.NumDescriptors = static_cast<UINT>(layout->GetBindingCount());
			heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
			heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
			mDevice->GetDevice()->CreateDescriptorHeap(&heap_desc, IID_PPV_ARGS(&heap_ptr));
			mDescriptorHeaps.push_back(heap_ptr);
		}
		mResult = VK_SUCCESS;
	}

	VkResult DescriptorSet::Write(VkDescriptorType type, uint32_t binding, uint32_t count, const VkDescriptorBufferInfo* buffer_infos)
	{
		assert(binding < mDescriptorHeaps.size());
		auto binding_heap = mDescriptorHeaps.at(binding);
		CD3DX12_CPU_DESCRIPTOR_HANDLE handle(binding_heap->GetCPUDescriptorHandleForHeapStart());
		UINT descriptor_size = mDevice->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		for (uint32_t i = 0; i < count; ++i)
		{
			const VkDescriptorBufferInfo& buffer_info = buffer_infos[i];
			Buffer* buffer = buffer_info.buffer;
			VkDeviceSize offset = buffer_info.offset;
			VkDeviceSize range = buffer_info.range;
			D3D12_SHADER_RESOURCE_VIEW_DESC desc = buffer->GetResourceView();
			desc.Buffer.FirstElement += offset;
			mDevice->GetDevice()->CreateShaderResourceView(buffer->GetResource(), &desc, handle);
			handle.Offset(1, descriptor_size);
		}
		return mResult;
	}

	VkResult DescriptorSet::Write(VkDescriptorType type, uint32_t binding, uint32_t count, const VkDescriptorImageInfo* image_infos)
	{
		assert(binding < mDescriptorHeaps.size());
		auto binding_heap = mDescriptorHeaps.at(binding);
		CD3DX12_CPU_DESCRIPTOR_HANDLE handle(binding_heap->GetCPUDescriptorHandleForHeapStart());
		UINT descriptor_size = mDevice->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		for (uint32_t i = 0; i < count; ++i)
		{
			const VkDescriptorImageInfo& image_info = image_infos[i];
			Sampler* sampler = image_info.sampler;
			ImageView* view = image_info.imageView;
			Image* image = view->GetImage();
			VkImageLayout layout = image_info.imageLayout;
			D3D12_SHADER_RESOURCE_VIEW_DESC desc = view->GetResourceView();
			mDevice->GetDevice()->CreateShaderResourceView(image->GetResource(), &desc, handle);
			handle.Offset(1, descriptor_size);
		}
		return mResult;
	}
}