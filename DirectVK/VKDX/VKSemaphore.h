#pragma once
#include "VKDeviceObject.h"
#include <mutex>
#include <condition_variable>

namespace VK
{
	class Semaphore : public DeviceObject
	{
	public:
		Semaphore(void);
		virtual ~Semaphore(void) override;

	public:
		VkResult Create(Device* device, const VkSemaphoreCreateInfo* info);

	public:
		VkResult Notify(void);
		VkResult Wait(uint64_t timeout = UINT64_MAX);

	protected:
		std::mutex mMutex;
		VkSemaphoreCreateFlags mFlags;
		std::condition_variable mLocker;
	};
}

struct VkSemaphore_T final : public VK::Semaphore
{
	VkSemaphore_T(void) = default;
	virtual ~VkSemaphore_T(void) final override = default;
};
