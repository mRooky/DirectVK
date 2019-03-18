#pragma once

#include "VKHeader.h"

namespace VK
{
	class Format
	{
	public:
		Format(void) = delete;
		~Format(void) = delete;

	public:
		static DXGI_FORMAT GetFormat(VkFormat format);
		static VkFormat GetFormat(DXGI_FORMAT format);

	public:
		static uint32_t GetFormatByteSize(VkFormat format);
	};
}
