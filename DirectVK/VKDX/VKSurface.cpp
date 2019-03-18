#include "VKSurface.h"

namespace VK
{
	Surface::Surface(void)
	{
	}

	Surface::~Surface(void)
	{
	}

	VkResult Surface::Create(Instance* instance, const VkWin32SurfaceCreateInfoKHR* info)
	{
		mHinstance = info->hinstance;
		mHandle = info->hwnd;
		mInstance = instance;
		::GetWindowRect(mHandle, &mRect);
		InitCapabilities();
		return mResult;
	}

	void Surface::InitCapabilities(void)
	{
		mCapabilities = {};
		mCapabilities.minImageCount = 2;
		mCapabilities.maxImageCount = 2;
		mCapabilities.currentExtent.width = mRect.right - mRect.left;
		mCapabilities.currentExtent.height = mRect.bottom - mRect.top;
		mCapabilities.minImageExtent = mCapabilities.currentExtent;
		mCapabilities.maxImageExtent = mCapabilities.currentExtent;
		mCapabilities.maxImageArrayLayers = 1;
		mCapabilities.supportedTransforms = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
		mCapabilities.currentTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
		mCapabilities.supportedCompositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR |
			VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR |
			VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR;
		mCapabilities.supportedUsageFlags = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
			VK_IMAGE_USAGE_STORAGE_BIT |
			VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
			VK_IMAGE_USAGE_TRANSFER_DST_BIT |
			VK_IMAGE_USAGE_SAMPLED_BIT;
	}

	VkResult Surface::GetCapabilities(VkSurfaceCapabilitiesKHR* capabilities) const
	{
		if (capabilities)
		{
			*capabilities = mCapabilities;
		}
		return VK_SUCCESS;
	}
}