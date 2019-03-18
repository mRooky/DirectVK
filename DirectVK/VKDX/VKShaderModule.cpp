#include "VKShaderModule.h"
#include <string>
#include <cassert>
#include <d3dcompiler.h>

namespace VK
{
	ShaderModule::ShaderModule(void)
	{
	}

	ShaderModule::~ShaderModule(void)
	{
	}

	VkResult ShaderModule::Create(Device* device, const VkShaderModuleCreateInfo* info)
	{
		mDevice = device;
		D3DCreateBlob(info->codeSize, &mShader);
		std::memcpy(mShader->GetBufferPointer(), info->pCode, info->codeSize);
		mResult = VK_SUCCESS;
		return mResult;
	}
}
