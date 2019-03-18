#include "VKFrameBuffer.h"
#include "VKImageView.h"
#include "VKRenderPass.h"
#include "VKDevice.h"
#include "VKImage.h"
#include <cassert>

namespace VK
{
	FrameBuffer::FrameBuffer(void)
	{
		mAttachments.clear();
	}

	FrameBuffer::~FrameBuffer(void)
	{
		mAttachments.clear();
	}

	VkResult FrameBuffer::Create(Device* device, const VkFramebufferCreateInfo* info)
	{
		mDevice = device;
		mRenderPass = info->renderPass;
		assert(info->attachmentCount > 0);
		for (uint32_t i = 0; i < info->attachmentCount; i++)
		{
			auto attachment = info->pAttachments[i];
			if (attachment->IsDepthStencil())
			{
				mDepthStencil = attachment;
			}
			else
			{
				mAttachments.push_back(attachment);
			}
		}
		mLayers = info->layers;
		mExtent.width = info->width;
		mExtent.height = info->height;
		CreateAttachmentHeap();
		CreateDepthStencilHeap();
		return mResult;
	}

	void FrameBuffer::CreateAttachmentHeap(void)
	{
		D3D12_DESCRIPTOR_HEAP_DESC heap_desc = {};
		heap_desc.NumDescriptors = static_cast<UINT>(mAttachments.size());
		heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		HRESULT result = mDevice->GetDevice()->CreateDescriptorHeap(&heap_desc, IID_PPV_ARGS(&mAttachmentHeap));
		ThrowIfFailed(result);
		mResult = SUCCEEDED(result) ? VK_SUCCESS : VK_INCOMPLETE;
		mDescriptorSize = mDevice->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		CD3DX12_CPU_DESCRIPTOR_HANDLE handle(mAttachmentHeap->GetCPUDescriptorHandleForHeapStart());
		for (UINT i = 0; i < mAttachments.size(); ++i)
		{
			Image* image = mAttachments.at(i)->GetImage();
			auto render_target = image->GetResource();
			mDevice->GetDevice()->CreateRenderTargetView(render_target, nullptr, handle);
			handle.Offset(1, mDescriptorSize);
		}
	}

	void FrameBuffer::CreateDepthStencilHeap(void)
	{
		if (mDepthStencil != nullptr)
		{
			D3D12_DESCRIPTOR_HEAP_DESC heap_desc = {};
			heap_desc.NumDescriptors = 1;
			heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
			heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
			HRESULT result = mDevice->GetDevice()->CreateDescriptorHeap(&heap_desc, IID_PPV_ARGS(&mDepthStencilHeap));
			ThrowIfFailed(result);
			mResult = SUCCEEDED(result) ? VK_SUCCESS : VK_INCOMPLETE;
			mDescriptorSize = mDevice->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
			CD3DX12_CPU_DESCRIPTOR_HANDLE handle(mDepthStencilHeap->GetCPUDescriptorHandleForHeapStart());
			Image* image = mDepthStencil->GetImage();
			auto render_target = image->GetResource();
			mDevice->GetDevice()->CreateDepthStencilView(render_target, nullptr, handle);
		}
	}

	CD3DX12_CPU_DESCRIPTOR_HANDLE FrameBuffer::GetAttachmentHandle(size_t index)
	{
		CD3DX12_CPU_DESCRIPTOR_HANDLE handle(mAttachmentHeap->GetCPUDescriptorHandleForHeapStart());
		handle.Offset(static_cast<INT>(index), mDescriptorSize);
		return handle;
	}

	CD3DX12_CPU_DESCRIPTOR_HANDLE FrameBuffer::GetDepthStencilHandle(void)
	{
		CD3DX12_CPU_DESCRIPTOR_HANDLE handle(mDepthStencilHeap->GetCPUDescriptorHandleForHeapStart());
		return handle;
	}
}