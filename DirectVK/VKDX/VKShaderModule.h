#pragma once
#include "VKDeviceObject.h"

namespace VK
{
	class ShaderModule : public DeviceObject
	{
	public:
		ShaderModule(void);
		virtual ~ShaderModule(void) override;

	public:
		VkResult Create(Device* device, const VkShaderModuleCreateInfo* info);

	public:
		ID3DBlob * GetShader(void) const { return mShader.Get(); }
		CD3DX12_SHADER_BYTECODE GetByteCode(void) const { return CD3DX12_SHADER_BYTECODE(mShader.Get()); }

	protected:
		ComPtr<ID3DBlob> mShader;
	};
}

struct VkShaderModule_T final : public VK::ShaderModule
{
	VkShaderModule_T(void) = default;
	virtual ~VkShaderModule_T(void) override final = default;
};
