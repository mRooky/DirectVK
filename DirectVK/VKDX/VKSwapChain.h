#pragma once
#include "VKDeviceObject.h"
#include <vector>

namespace VK
{
	class Swapchain : public DeviceObject
	{
	public:
		Swapchain(void);
		virtual ~Swapchain(void) override;

	public:
		VkResult Create(Device* device, const VkSwapchainCreateInfoKHR* info);
		VkResult GetImages(uint32_t* count, VkImage* images) const;
		VkResult Present(UINT interval, UINT flags);

	public:
		uint32_t AcquireNextIndex(uint64_t timeout, Semaphore* semaphore, Fence* fence);

	public:
		inline Image * GetImage(uint32_t index) const { return mImages.at(index); }
		inline uint32_t GetCurrentIndex(void) const { return mCurrentIndex; }

	private:
		void FillImage(uint32_t count);

	protected:
		VkQueue mQueue;
		Surface * mSurface;
		std::vector<Image*> mImages;
		uint32_t mCurrentIndex;

	protected:
		ComPtr<IDXGISwapChain4> mSwapChian;
	};
}

struct VkSwapchainKHR_T final : public VK::Swapchain
{
	VkSwapchainKHR_T(void) = default;
	virtual ~VkSwapchainKHR_T(void) override final = default;
};
