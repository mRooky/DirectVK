#include "VKSemaphore.h"
#include <cassert>

namespace VK
{
	Semaphore::Semaphore(void)
	{
	}

	Semaphore::~Semaphore(void)
	{
	}

	VkResult Semaphore::Create(Device* device, const VkSemaphoreCreateInfo* info)
	{
		mDevice = device;
		mFlags = info->flags;
		mResult = VK_SUCCESS;
		return mResult;
	}

	VkResult Semaphore::Notify(void)
	{
		mLocker.notify_all();
		return VK_SUCCESS;
	}

	VkResult Semaphore::Wait(uint64_t timeout)
	{
		std::unique_lock<std::mutex> lock(mMutex);
		if (timeout = 0)
		{
			mResult = VK_SUCCESS;
		}
		else if (timeout == UINT_MAX)
		{
			mLocker.wait(lock);
			mResult = VK_SUCCESS;
		}
		else
		{
			std::chrono::nanoseconds nano(timeout);
			std::cv_status status = mLocker.wait_for(lock, nano);
			mResult = std::cv_status::timeout == status ? VK_TIMEOUT : VK_SUCCESS;
		}
		return mResult;
	}
}