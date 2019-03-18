#include "VKQueueFamily.h"
#include "VKDevice.h"
#include "VKQueue.h"

namespace VK
{
	QueueFamily::QueueFamily(void)
	{
	}

	QueueFamily::~QueueFamily(void)
	{
		for (auto queue : mQueues)
		{
			delete queue;
		}
		mQueues.clear();
	}

	VkResult QueueFamily::Create(Device* device, const VkDeviceQueueCreateInfo* info)
	{
		mDevice = device;
		mFamily = info->queueFamilyIndex;
		for (uint32_t i = 0; i < info->queueCount; ++i)
		{
			Queue* queue = new Queue;
			queue->Create(mDevice, info);
			mQueues.push_back(queue);
		}
		return mResult;
	}

	void QueueFamily::InitProperties(void)
	{
		mProperties = {};
		mProperties.queueFlags = VK_QUEUE_GRAPHICS_BIT |
			VK_QUEUE_COMPUTE_BIT |
			VK_QUEUE_TRANSFER_BIT;
		mProperties.queueCount = 8;
		mProperties.timestampValidBits = 64;
		mProperties.minImageTransferGranularity = { 1, 1, 1 };
	}

	void QueueFamily::GetProperties(VkQueueFamilyProperties* properties) const
	{
		if (properties != nullptr)
		{
			*properties = mProperties;
		}
	}
}