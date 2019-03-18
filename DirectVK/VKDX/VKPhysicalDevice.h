#pragma once
#include "VKDispatchable.h"

namespace VK
{
	class PhysicalDevice : public Dispatchable
	{
	public:
		PhysicalDevice(void);
		virtual ~PhysicalDevice(void) override;

	public:
		void Initialize(Instance* instance, ComPtr<IDXGIAdapter1> adapter);

	public:
		void GetFeatures(VkPhysicalDeviceFeatures* features) const;
		void GetProperties(VkPhysicalDeviceProperties* properties) const;
		void GetMemoryProperties(VkPhysicalDeviceMemoryProperties* properties) const;
		void GetQueueFamilyProperties(uint32_t* count, VkQueueFamilyProperties* properties) const;

	public:
		D3D12_HEAP_TYPE GetHeapType(uint32_t index) const;

	public:
		inline Instance* GetInstance(void) const { return mInstance; }
		inline IDXGIAdapter1* GetAdapter(void) const { return mAdapter.Get(); }

	public:
		void GetFormatProperties(VkFormat format, VkFormatProperties* pFormatProperties);

	private:
		void InitFeatures(void);
		void InitProperties(void);
		void InitDeviceLimit(void);
		void InitSparseProperties(void);
		void InitMemoryProperties(void);
		void InitQueueFamilyPropertiex(void);

	protected:
		DXGI_ADAPTER_DESC1 mDesc;
		ComPtr<IDXGIAdapter1> mAdapter;

	protected:
		Instance* mInstance;

	protected:
		VkPhysicalDeviceFeatures mFeatures;
		VkPhysicalDeviceProperties mProperties;
		VkQueueFamilyProperties mQueueFamilyProperties;
		VkPhysicalDeviceMemoryProperties mMemoryProperties;
	};
}

struct VkPhysicalDevice_T final : public VK::PhysicalDevice
{
	VkPhysicalDevice_T(void) = default;
	virtual ~VkPhysicalDevice_T(void) final override = default;
};
