#include "VKQueryPool.h"
#include <cassert>

namespace VK
{
	QueryPool::QueryPool(void)
	{
	}

	QueryPool::~QueryPool(void)
	{
	}

	VkResult QueryPool::Create(Device* device, const VkQueryPoolCreateInfo* info)
	{
		assert(false);
		return mResult;
	}
}