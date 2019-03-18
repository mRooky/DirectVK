#pragma once
#include "VKObject.h"
#include <vector>

namespace VK
{
	class QueueFamily : public Object
	{
	public:
		QueueFamily(void);
		virtual ~QueueFamily(void) override;

	public:
		VkResult Create(Device* device, const VkDeviceQueueCreateInfo* info);
		void GetProperties(VkQueueFamilyProperties* properties) const;

	public:
		inline uint32_t GetFamily(void) const { return mFamily; }
		inline Queue* GetQueue(size_t index) const { return mQueues.at(index); }

	private:
		void InitProperties(void);

	protected:
		uint32_t mFamily;
		Device * mDevice;
		std::vector<Queue*> mQueues;
		VkQueueFamilyProperties mProperties;
	};
}
