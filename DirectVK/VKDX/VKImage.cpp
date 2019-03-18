#include "VKImage.h"
#include "VKUtility.h"
#include "VKDevice.h"
#include <cassert>

namespace VK
{
	Image::Image(void)
	{
	}

	Image::~Image(void)
	{
	}

	VkResult Image::Create(Device* device, const VkImageCreateInfo* info)
	{
		mDevice = device;
		if (info)
		{
			mType = info->imageType;
			mFormat = info->format;
			mExtent = info->extent;
			mMipLevels = info->mipLevels;
			mArrayLayers = info->arrayLayers;
			mUsage = info->usage;
			mSamples = info->samples;
			CreateRequirements();
		}
		return mResult;
	}

	void Image::CreateResource(D3D12_HEAP_TYPE type)
	{
		mResourceDesc.MipLevels = mMipLevels;										//done
		mResourceDesc.Format = Format::GetFormat(mFormat);						//done
		mResourceDesc.Width = mExtent.width;										//done
		mResourceDesc.Height = mExtent.height;										//done
		mResourceDesc.DepthOrArraySize = max(mExtent.depth, mArrayLayers);			//done
		mResourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
		mResourceDesc.SampleDesc.Count = static_cast<UINT>(mSamples);				//done
		mResourceDesc.SampleDesc.Quality = 0;
		mResourceDesc.Dimension = Utility::GetDimension(mType);					//done

		D3D12_RESOURCE_STATES usage = D3D12_RESOURCE_STATE_COMMON;
		CD3DX12_HEAP_PROPERTIES heap_properties(type);

		if (mUsage & VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT)
		{
			mResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
			usage |= D3D12_RESOURCE_STATE_DEPTH_WRITE;
			D3D12_CLEAR_VALUE clear_value;
			clear_value.Format = mResourceDesc.Format;
			clear_value.DepthStencil.Depth = 1.0f;
			clear_value.DepthStencil.Stencil = 0;
			mDevice->GetDevice()->CreateCommittedResource(&heap_properties, D3D12_HEAP_FLAG_NONE,
				&mResourceDesc, usage, &clear_value, IID_PPV_ARGS(&mResource));
		}
		else
		{
			mDevice->GetDevice()->CreateCommittedResource(&heap_properties, D3D12_HEAP_FLAG_NONE,
				&mResourceDesc, usage, nullptr, IID_PPV_ARGS(&mResource));
		}
		mResult = VK_SUCCESS;
	}

	void Image::CreateRequirements(void)
	{
		assert(mMipLevels > 0);
		if (mMipLevels > 1)
		{
			uint32_t sum = Utility::GetMipmapSize(mExtent.width, mExtent.height, mMipLevels);
			mReauirements.size = sum * Format::GetFormatByteSize(mFormat);
		}
		else
		{
			mReauirements.size = mExtent.width * mExtent.height * Format::GetFormatByteSize(mFormat);
		}
		mReauirements.size *= max(mExtent.depth, mArrayLayers);	// all sub image

		if (mUsage & VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT)
		{
			mReauirements.memoryTypeBits = 0x00000001;			// must be device local only
		}
		else
		{
			mReauirements.memoryTypeBits = 0x00000011;			// user define
		}
		mReauirements.alignment = 0;							// maybe, for require size
		mSize = mReauirements.size;
		mResult = VK_SUCCESS;
	}
}