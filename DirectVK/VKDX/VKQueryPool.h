#pragma once
#include "VKDeviceObject.h"

namespace VK
{
	class QueryPool : public DeviceObject
	{
	public:
		QueryPool(void);
		virtual ~QueryPool(void) override;

	public:
		VkResult Create(Device* device, const VkQueryPoolCreateInfo* info);
	};
}

struct VkQueryPool_T final : public VK::QueryPool
{
	VkQueryPool_T(void) = default;
	virtual ~VkQueryPool_T(void) final override = default;
};
