#pragma once
#include "VKDeviceObject.h"

namespace VK
{
	class ImageView : public DeviceObject
	{
	public:
		ImageView(void);
		virtual ~ImageView(void) override;

	public:
		VkResult Create(Device* device, const VkImageViewCreateInfo* info);

	public:
		bool IsDepthStencil(void) const;

	public:
		inline Image* GetImage(void) const { return mImage; }
		inline const D3D12_SHADER_RESOURCE_VIEW_DESC& GetResourceView(void) const { return mResourceView; }

	private:
		void CreateResourceView(void);

	protected:
		Image * mImage;
		VkImageViewType mType;
		VkFormat mFormat;
		VkImageSubresourceRange mSubresourceRange;

	protected:
		D3D12_SHADER_RESOURCE_VIEW_DESC mResourceView;
	};
}

struct VkImageView_T final : public VK::ImageView
{
	VkImageView_T(void) = default;
	virtual ~VkImageView_T(void) override final = default;
};
