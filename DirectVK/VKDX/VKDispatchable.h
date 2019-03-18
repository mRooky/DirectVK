#pragma once
#include "VKObject.h"
#include <vulkan/vk_icd.h>

namespace VK
{
	class Dispatchable : public Object
	{
	protected:
		Dispatchable(void);
		virtual ~Dispatchable(void) override;

	public:
		VK_LOADER_DATA GetLoaderData(void) const { return mLoaderData; }

	protected:
		VK_LOADER_DATA mLoaderData;
	};
}
