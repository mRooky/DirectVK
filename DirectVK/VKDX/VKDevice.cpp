#include "VKDevice.h"
#include "VKPhysicalDevice.h"
#include "VKQueueFamily.h"
#include "VKQueue.h"
#include "VKBuffer.h"
#include "VKImage.h"
#include <cassert>
#include <algorithm>

namespace VK
{
	Device::Device(void)
	{
		mFeatureLevel = D3D_FEATURE_LEVEL_11_0;
		mResources.clear();
	}

	Device::~Device(void)
	{
		for (auto resource : mResources)
		{
			delete resource;
		}
		mResources.clear();

		for (auto family : mQueueFamilies)
		{
			delete family;
		}
		mQueueFamilies.clear();
	}

	VkResult Device::Create(PhysicalDevice* physical, const VkDeviceCreateInfo* info)
	{
		mPhysicalDevice = physical;
		HRESULT result = D3D12CreateDevice(physical->GetAdapter(), mFeatureLevel, IID_PPV_ARGS(&mDevice));
		if (SUCCEEDED(result))
		{
			CreateQueue(info);
		}
		return mResult;
	}

	void Device::CreateQueue(const VkDeviceCreateInfo* info)
	{
		uint32_t count = info->queueCreateInfoCount;
		mQueueFamilies.reserve(count);
		for (uint32_t index = 0; index < count; index++)
		{
			const VkDeviceQueueCreateInfo& queue_create_info = info->pQueueCreateInfos[index];
			QueueFamily* family = new QueueFamily;
			family->Create(this, &queue_create_info);
			mQueueFamilies.push_back(family);
		}
		mResult = VK_SUCCESS;
	}

	VkResult Device::GetDeviceQueue(uint32_t family, uint32_t index, VkQueue* queues)
	{
		QueueFamily* exist_family = nullptr;
		for (auto queue_family : mQueueFamilies)
		{
			if (queue_family->GetFamily() == family)
			{
				exist_family = queue_family;
				break;
			}
		}

		if (exist_family != nullptr)
		{
			auto queue = exist_family->GetQueue(index);
			*queues = static_cast<VkQueue>(queue);
			mResult = VK_SUCCESS;
		}
		return mResult;
	}

	void Device::RemoveResource(Resource* resource)
	{
		if (resource != nullptr)
		{
			auto iterator = std::find(mResources.begin(), mResources.end(), resource);
			if (iterator != mResources.end())
			{
				mResources.erase(iterator);
			}
			delete resource;
		}

	}

	Buffer * Device::CreateBuffer(const VkBufferCreateInfo* info)
	{
		Buffer* buffer = new Buffer;
		buffer->Create(this, info);
		mResources.push_back(buffer);
		return buffer;
	}

	Image * Device::CreateImage(const VkImageCreateInfo* info)
	{
		Image* image = new Image;
		image->Create(this, info);
		mResources.push_back(image);
		return image;
	}
}