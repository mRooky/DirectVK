#pragma once
#include "VKDeviceObject.h"
#include <vector>

namespace VK
{
	class PipelineLayout : public DeviceObject
	{
	public:
		PipelineLayout(void);
		virtual ~PipelineLayout(void) override;

	public:
		VkResult Create(Device* device, const VkPipelineLayoutCreateInfo* info);

	public:
		ID3D12RootSignature * GetRootSignature(void) const { return mRootSignature.Get(); }

	private:
		void CreateRootSignature(void);
		void GetDescriptorRanges(void);
		void GetRootParamters(void);

	protected:
		std::vector<DescriptorSetLayout*> mDescriptorSetLayouts;

	protected:
		ComPtr<ID3D12RootSignature> mRootSignature;
		std::vector<CD3DX12_DESCRIPTOR_RANGE1> mDescriptorRanges;
		std::vector<CD3DX12_ROOT_PARAMETER1> mRootParamters;
	};
}

struct VkPipelineLayout_T final : public VK::PipelineLayout
{
	VkPipelineLayout_T(void) = default;
	virtual ~VkPipelineLayout_T(void) final override = default;
};
