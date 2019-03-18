#include "VKImageView.h"
#include "VKImage.h"
#include "VKUtility.h"
#include <vector>
#include <algorithm>

namespace VK
{
	ImageView::ImageView(void)
	{
	}

	ImageView::~ImageView(void)
	{
	}

	VkResult ImageView::Create(Device* device, const VkImageViewCreateInfo* info)
	{
		mDevice = device;
		mImage = info->image;
		mType = info->viewType;
		mFormat = info->format;
		mSubresourceRange = info->subresourceRange;
		CreateResourceView();
		return mResult;
	}

	void ImageView::CreateResourceView(void)
	{
		mResourceView = {};
		mResourceView.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		mResourceView.Format = Format::GetFormat(mFormat);
		mResourceView.ViewDimension = Utility::GetDimension(mType);
		mResourceView.Texture2D.MipLevels = mImage->GetMipLevels();
		mResult = VK_SUCCESS;
	}

	bool ImageView::IsDepthStencil(void) const
	{
		static const std::vector<VkFormat> format_list =
		{
			VK_FORMAT_D16_UNORM,
			VK_FORMAT_D24_UNORM_S8_UINT,
			VK_FORMAT_X8_D24_UNORM_PACK32,
			VK_FORMAT_D32_SFLOAT,
			VK_FORMAT_S8_UINT
		};
		auto iterator = std::find(format_list.begin(), format_list.end(), mFormat);
		return iterator != format_list.end();
	}
}