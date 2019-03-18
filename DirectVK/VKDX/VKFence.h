#pragma once
#include "VKDeviceObject.h"

namespace VK
{
	class Fence : public DeviceObject
	{
	public:
		Fence(void);
		virtual ~Fence(void) override;

	public:
		VkResult Create(Device* device, const VkFenceCreateInfo* info);
		VkResult WaitFor(uint64_t timeout = INFINITE) const;
		void Reset(void);
		VkResult GetStatus(void) const;

	public:
		inline UINT64 GetValue(void) const { return mValue; }
		inline ID3D12Fence * GetFence(void) const { return mFence.Get(); }
		inline void IncreaseValue(void) { ++mValue; }

	protected:
		mutable UINT64 mValue;
		ComPtr<ID3D12Fence> mFence;
	};
}

struct VkFence_T final : public VK::Fence
{
	VkFence_T(void) = default;
	virtual ~VkFence_T(void) final override = default;
};
