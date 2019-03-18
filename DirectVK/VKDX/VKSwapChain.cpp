#include "VKSwapchain.h"
#include "VKSurface.h"
#include "VKImage.h"
#include "VKUtility.h"
#include "VKDevice.h"
#include "VKQueue.h"
#include "VKPhysicalDevice.h"
#include "VKInstance.h"
#include "VKSemaphore.h"
#include <cassert>

namespace VK
{
	Swapchain::Swapchain(void)
	{
	}

	Swapchain::~Swapchain(void)
	{
		for (auto image : mImages)
		{
			mDevice->RemoveResource(image);
		}
		mImages.clear();
	}

	VkResult Swapchain::Create(Device* device, const VkSwapchainCreateInfoKHR* info)
	{
		mDevice = device;
		mDevice->GetDeviceQueue(0, 0, &mQueue);
		mSurface = info->surface;
		DXGI_SWAP_CHAIN_DESC1 swapchain_desc = {};
		swapchain_desc.BufferCount = info->minImageCount;
		swapchain_desc.Width = info->imageExtent.width;
		swapchain_desc.Height = info->imageExtent.height;
		swapchain_desc.Format = Format::GetFormat(info->imageFormat);
		swapchain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapchain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapchain_desc.SampleDesc.Count = 1;

		Instance* instance = mDevice->GetPhysicalDevice()->GetInstance();

		ComPtr<IDXGISwapChain1> swapchian;
		HRESULT result = instance->GetFactory()->CreateSwapChainForHwnd(mQueue->GetCommandQueue(),
			mSurface->GetHwnd(), &swapchain_desc, nullptr, nullptr, &swapchian);
		if (SUCCEEDED(result))
		{
			result = swapchian.As(&mSwapChian);
		}

		FillImage(info->minImageCount);

		assert(SUCCEEDED(result));
		mResult = SUCCEEDED(result) ? VK_SUCCESS : VK_INCOMPLETE;
		return mResult;
	}

	void Swapchain::FillImage(uint32_t count)
	{
		mImages.reserve(count);
		for (uint32_t i = 0; i < count; ++i)
		{
			ComPtr<ID3D12Resource> target;
			mSwapChian->GetBuffer(i, IID_PPV_ARGS(&target));
			Image* image = mDevice->CreateImage(nullptr);
			image->mState = D3D12_RESOURCE_STATE_PRESENT;
			image->mResource = target;
			mImages.push_back(image);
		}
	}

	VkResult Swapchain::GetImages(uint32_t* count, VkImage* images) const
	{
		uint32_t size = static_cast<uint32_t>(mImages.size());
		if (images == nullptr)
		{
			*count = size;
			return VK_SUCCESS;
		}

		*count = min(*count, size);
		for (uint32_t i = 0; i < *count; ++i)
		{
			Image* image = mImages.at(i);
			images[i] = static_cast<VkImage>(image);
		}
		return VK_SUCCESS;
	}

	uint32_t Swapchain::AcquireNextIndex(uint64_t timeout, Semaphore* semaphore, Fence* fence)
	{
		mCurrentIndex = mSwapChian->GetCurrentBackBufferIndex();
		semaphore->Notify();
		return mCurrentIndex;
	}

	VkResult Swapchain::Present(UINT interval, UINT flags)
	{
		HRESULT result = mSwapChian->Present(interval, flags);
		mResult = SUCCEEDED(result) ? VK_SUCCESS : VK_INCOMPLETE;
		return mResult;
	}
}