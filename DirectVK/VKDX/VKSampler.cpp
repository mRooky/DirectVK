#include "VKSampler.h"
#include "VKDevice.h"

namespace VK
{
	Sampler::Sampler(void)
	{
	}

	Sampler::~Sampler(void)
	{
	}

	VkResult Sampler::Create(Device* device, const VkSamplerCreateInfo* info)
	{
		mDevice = device;
		mSamplerDesc = {};
		mSamplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
		mSamplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
		mSamplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
		mSamplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
		mSamplerDesc.MipLODBias = 0;
		mSamplerDesc.MaxAnisotropy = 0;
		mSamplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
		mSamplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
		mSamplerDesc.MinLOD = 0.0f;
		mSamplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
		mSamplerDesc.ShaderRegister = 0;
		mSamplerDesc.RegisterSpace = 0;
		mSamplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
		return mResult;
	}
}