#pragma once
#include "VKDeviceObject.h"

namespace VK
{
	class Surface : public DeviceObject
	{
	public:
		Surface(void);
		virtual ~Surface(void) override;

	public:
		VkResult Create(Instance* mInstance, const VkWin32SurfaceCreateInfoKHR* info);
		VkResult GetCapabilities(VkSurfaceCapabilitiesKHR* capabilities) const;

	public:
		inline HWND GetHwnd(void) const { return mHandle; }
		inline HINSTANCE GetInstance(void) const { return mHinstance; }
		inline Instance* GetPhysicalDevice(void) const { return mInstance; }
		inline const VkExtent2D& GetExtent(void) const { return mCapabilities.currentExtent; }

	private:
		void InitCapabilities(void);

	protected:
		RECT mRect;
		HWND mHandle;
		HINSTANCE mHinstance;

	protected:
		Instance * mInstance;
		VkSurfaceCapabilitiesKHR mCapabilities;
	};
}

struct VkSurfaceKHR_T final : public VK::Surface
{
	VkSurfaceKHR_T(void) = default;
	virtual ~VkSurfaceKHR_T(void) override final = default;
};
