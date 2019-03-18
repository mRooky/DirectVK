#include "VKInstance.h"
#include "VKPhysicalDevice.h"

namespace VK
{
	Instance::Instance(void)
	{
	}

	Instance::~Instance(void)
	{
		for (auto physical : mPhysicalDevices)
		{
			delete physical;
		}
		mPhysicalDevices.clear();
	}

	VkResult Instance::Create(const VkInstanceCreateInfo* info)
	{
		UINT flags = 0;

#ifdef _DEBUG
		{
			ComPtr<ID3D12Debug> debug_controller;
			if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debug_controller))))
			{
				debug_controller->EnableDebugLayer();
				flags |= DXGI_CREATE_FACTORY_DEBUG;
			}
		}
#endif

		ThrowIfFailed(CreateDXGIFactory2(0, IID_PPV_ARGS(&mFactory)));
		ComPtr<IDXGIAdapter1> adapter;
		for (UINT index = 0; DXGI_ERROR_NOT_FOUND != mFactory->EnumAdapters1(index, &adapter); ++index)
		{
			PhysicalDevice* physical = new PhysicalDevice;
			physical->Initialize(this, adapter);
			mPhysicalDevices.push_back(physical);
		}

		mResult = mPhysicalDevices.size() > 0 ? VK_SUCCESS : VK_INCOMPLETE;
		return mResult;
	}

	VkResult Instance::GetPhysicalDevices(uint32_t* count, VkPhysicalDevice* physicals)
	{
		uint32_t size = static_cast<uint32_t>(mPhysicalDevices.size());
		if (physicals == nullptr)
		{
			*count = size;
			return VK_SUCCESS;
		}

		*count = min(size, *count);
		for (uint32_t index = 0; index < *count; ++index)
		{
			PhysicalDevice* physical = mPhysicalDevices.at(index);
			physicals[index] = static_cast<VkPhysicalDevice>(physical);
		}

		return mResult;
	}
}