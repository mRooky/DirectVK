#include "VKPipelineLayout.h"
#include "VKDescriptorSetLayout.h"
#include "VKDevice.h"
#include <cassert>

namespace VK
{
	PipelineLayout::PipelineLayout(void)
	{
	}

	PipelineLayout::~PipelineLayout(void)
	{
		mDescriptorSetLayouts.clear();
	}

	VkResult PipelineLayout::Create(Device* device, const VkPipelineLayoutCreateInfo* info)
	{
		mDevice = device;
		const uint32_t count = info->setLayoutCount;
		for (uint32_t i = 0; i < count; ++i)
		{
			mDescriptorSetLayouts.push_back(info->pSetLayouts[i]);
		}
		CreateRootSignature();
		mResult = mDescriptorSetLayouts.size() > 0 ? VK_SUCCESS : VK_INCOMPLETE;
		return mResult;
	}

	void PipelineLayout::CreateRootSignature(void)
	{
		auto device = mDevice->GetDevice();
		D3D12_FEATURE_DATA_ROOT_SIGNATURE featureData = {};
		featureData.HighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_1;

		if (FAILED(device->CheckFeatureSupport(D3D12_FEATURE_ROOT_SIGNATURE, &featureData, sizeof(featureData))))
		{
			featureData.HighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_0;
		}

		CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
		UINT count = static_cast<UINT>(mRootParamters.size());
		rootSignatureDesc.Init_1_1(count, mRootParamters.data(), 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

		ComPtr<ID3DBlob> signature;
		ComPtr<ID3DBlob> error;
		ThrowIfFailed(D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, featureData.HighestVersion, &signature, &error));
		ThrowIfFailed(device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&mRootSignature)));
	}

	void PipelineLayout::GetDescriptorRanges(void)
	{
		size_t count = mDescriptorSetLayouts.size();
		mDescriptorRanges.reserve(count);
		for (uint32_t i = 0; i < count; ++i)
		{
			DescriptorSetLayout* layout = mDescriptorSetLayouts.at(i);
			const auto& binding = layout->GetBinding(i);
			VkDescriptorType type = binding.descriptorType;
			CD3DX12_DESCRIPTOR_RANGE1 descriptor_range = {};
			descriptor_range.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0, 0, D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC);
			mDescriptorRanges.push_back(descriptor_range);
			assert(false);
		}
	}

	void PipelineLayout::GetRootParamters(void)
	{
		size_t count = mDescriptorRanges.size();
		mRootParamters.reserve(count);
		for (size_t i = 0; i < count; ++i)
		{
			const CD3DX12_DESCRIPTOR_RANGE1& descriptor_range = mDescriptorRanges.at(i);
			CD3DX12_ROOT_PARAMETER1 parameter = {};
			parameter.InitAsDescriptorTable(1, &descriptor_range, D3D12_SHADER_VISIBILITY_ALL);
			assert(false);
		}
	}
}