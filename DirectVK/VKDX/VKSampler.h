#pragma once
#include "VKDeviceObject.h"

namespace VK
{
	class Sampler : public DeviceObject
	{
	public:
		Sampler(void);
		virtual ~Sampler(void) override;

	public:
		VkResult Create(Device* device, const VkSamplerCreateInfo* info);

	public:
		inline const D3D12_STATIC_SAMPLER_DESC& GetDesc(void) const { return mSamplerDesc; }

	protected:
		D3D12_STATIC_SAMPLER_DESC mSamplerDesc;
	};
}

struct VkSampler_T final : public VK::Sampler
{
	VkSampler_T(void) = default;
	virtual ~VkSampler_T(void) override final = default;
};
