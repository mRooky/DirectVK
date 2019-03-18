#pragma once
#include "VKDeviceObject.h"
#include <vector>

namespace VK
{
	class FrameBuffer : public DeviceObject
	{
	public:
		FrameBuffer(void);
		virtual ~FrameBuffer(void) override;

	public:
		VkResult Create(Device* device, const VkFramebufferCreateInfo* info);

	public:
		CD3DX12_CPU_DESCRIPTOR_HANDLE GetAttachmentHandle(size_t index);
		CD3DX12_CPU_DESCRIPTOR_HANDLE GetDepthStencilHandle(void);

	public:
		inline uint32_t GetLayers(void) const { return mLayers; }
		inline const VkExtent2D& GetExtent(void) const { return mExtent; }
		inline size_t GetAttachmentCount(void) const { return mAttachments.size(); }
		inline const ImageView* GetAttachment(uint32_t index) const { return mAttachments.at(index); }
		inline UINT GetDescriptorSize(void) const { return mDescriptorSize; }
		inline const ImageView* GetDepthStencil(void) const { return mDepthStencil; }

	private:
		void CreateAttachmentHeap(void);
		void CreateDepthStencilHeap(void);

	protected:
		uint32_t mLayers;
		VkExtent2D mExtent;
		RenderPass * mRenderPass;
		const ImageView* mDepthStencil;
		std::vector<const ImageView*> mAttachments;

	protected:
		UINT mDescriptorSize;
		ComPtr<ID3D12DescriptorHeap> mAttachmentHeap;
		ComPtr<ID3D12DescriptorHeap> mDepthStencilHeap;
	};
}

struct VkFramebuffer_T final : public VK::FrameBuffer
{
	VkFramebuffer_T(void) = default;
	virtual ~VkFramebuffer_T(void) override final = default;
};
