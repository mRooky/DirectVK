#include "DXAdapter.h"
#include <cassert>

namespace DX
{
	Adapter::Adapter(void)
	{
	}

	Adapter::~Adapter(void)
	{
	}

	uint32_t Adapter::GetMemoryTypeIndex(VkMemoryPropertyFlags flags)
	{
		assert(false);
		return 0;
	}
}