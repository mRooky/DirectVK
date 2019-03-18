#include "VKUtility.h"
#include <cassert>

namespace VK
{
	D3D12_RESOURCE_DIMENSION Utility::GetDimension(VkImageType type)
	{
		D3D12_RESOURCE_DIMENSION dimension = D3D12_RESOURCE_DIMENSION_UNKNOWN;
		switch (type)
		{
		case VK_IMAGE_TYPE_1D:
			dimension = D3D12_RESOURCE_DIMENSION_TEXTURE1D;
			break;
		case VK_IMAGE_TYPE_2D:
			dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			break;
		case VK_IMAGE_TYPE_3D:
			dimension = D3D12_RESOURCE_DIMENSION_TEXTURE3D;
			break;
		default:
			assert(false);
			break;
		}
		return dimension;
	}

	D3D12_SRV_DIMENSION Utility::GetDimension(VkImageViewType type)
	{
		D3D12_SRV_DIMENSION dimension = D3D12_SRV_DIMENSION_UNKNOWN;
		switch (type)
		{
		case VK_IMAGE_VIEW_TYPE_1D:
			dimension = D3D12_SRV_DIMENSION_TEXTURE1D;
			break;
		case VK_IMAGE_VIEW_TYPE_2D:
			dimension = D3D12_SRV_DIMENSION_TEXTURE2D;
			break;
		case VK_IMAGE_VIEW_TYPE_3D:
			dimension = D3D12_SRV_DIMENSION_TEXTURE3D;
			break;
		case VK_IMAGE_VIEW_TYPE_CUBE:
			dimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
			break;
		case VK_IMAGE_VIEW_TYPE_1D_ARRAY:
			dimension = D3D12_SRV_DIMENSION_TEXTURE1DARRAY;
			break;
		case VK_IMAGE_VIEW_TYPE_2D_ARRAY:
			dimension = D3D12_SRV_DIMENSION_TEXTURE2DARRAY;
			break;
		case VK_IMAGE_VIEW_TYPE_CUBE_ARRAY:
			dimension = D3D12_SRV_DIMENSION_TEXTURECUBEARRAY;
			break;
		default:
			break;
		}
		return dimension;
	}

	D3D12_INPUT_CLASSIFICATION Utility::GetInputRate(VkVertexInputRate rate)
	{
		switch (rate)
		{
		case VK_VERTEX_INPUT_RATE_VERTEX:
			return D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
			break;
		case VK_VERTEX_INPUT_RATE_INSTANCE:
			return D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA;
			break;
		default:
			assert(false);
			break;
		}
		return D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
	}

	uint32_t  Utility::GetLog2(uint32_t value)
	{
		assert((value & (value - 1)) == 0); //must pow 2
		uint32_t pow = 0;
		while (value > 1)
		{
			value >>= 1;
			++pow;
		}
		return pow;
	}

	uint32_t Utility::GetMipmapLevelSize(uint32_t width, uint32_t height, uint32_t level)
	{
		assert(width == height);			//must be square
		uint32_t div = 2 ^ (level - 1);
		return width / div * height / div;
	}

	uint32_t Utility::GetMipmapSize(uint32_t width, uint32_t height, uint32_t levels)
	{
		uint32_t sum = 0;
		while (levels > 0)
		{
			sum += Utility::GetMipmapLevelSize(width, height, levels);
			--levels;
		}
		return sum;
	}
}