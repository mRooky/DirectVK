#include "VKFormat.h"
#include <cassert>

namespace VK
{
	DXGI_FORMAT Format::GetFormat(VkFormat format)
	{
		DXGI_FORMAT ret = DXGI_FORMAT_UNKNOWN;
		switch (format)
		{
		case VK_FORMAT_R8G8B8A8_UNORM:
			ret = DXGI_FORMAT_R8G8B8A8_UNORM;
			break;
		case VK_FORMAT_D24_UNORM_S8_UINT:
			ret = DXGI_FORMAT_D24_UNORM_S8_UINT;
			break;
		case VK_FORMAT_R32G32B32_SFLOAT:
			ret = DXGI_FORMAT_R32G32B32_FLOAT;
			break;
		case VK_FORMAT_R32G32B32A32_SFLOAT:
			ret = DXGI_FORMAT_R32G32B32A32_FLOAT;
			break;
		default:
			assert(false);
			break;
		}
		return ret;
	}

	VkFormat Format::GetFormat(DXGI_FORMAT format)
	{
		VkFormat ret = VK_FORMAT_UNDEFINED;
		switch (format)
		{
		case DXGI_FORMAT_R8G8B8A8_UNORM:
			ret = VK_FORMAT_R8G8B8A8_UNORM;
			break;
		default:
			assert(false);
			break;
		}
		return ret;
	}

	uint32_t Format::GetFormatByteSize(VkFormat format)
	{
		uint32_t size = 0;
		switch (format)
		{
		case VK_FORMAT_R8G8B8A8_UNORM:
			size = 4;
			break;
		case VK_FORMAT_D24_UNORM_S8_UINT:
			size = 4;
			break;
		default:
			assert(false);
			break;
		}
		return size;
	}
}