#pragma once

#include "VKDispatchable.h"
#include <vector>

namespace VK
{
	class Instance : public Dispatchable
	{
	public:
		Instance(void);
		virtual ~Instance(void) override;

	public:
		VkResult Create(const VkInstanceCreateInfo* info);
		VkResult GetPhysicalDevices(uint32_t* count, VkPhysicalDevice* physicals);

	public:
		inline ComPtr<IDXGIFactory5> GetFactory(void) const { return mFactory; }

	protected:
		ComPtr<IDXGIFactory5> mFactory;

	protected:
		std::vector<PhysicalDevice*> mPhysicalDevices;

	};
}

struct VkInstance_T final : public VK::Instance
{
	VkInstance_T(void) = default;
	virtual ~VkInstance_T(void) override final = default;
};
