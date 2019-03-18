#include "VKCommandPool.h"
#include "VKCommandBuffer.h"
#include "VKDevice.h"
#include <algorithm>
#include <cassert>

namespace VK
{
	CommandPool::CommandPool(void)
	{
	}

	CommandPool::~CommandPool(void)
	{
		for (auto command : mCommandBuffers)
		{
			delete command;
		}
		mCommandBuffers.clear();
	}

	VkResult CommandPool::Create(Device* device, const VkCommandPoolCreateInfo* info)
	{
		mDevice = device;
		mFamily = info->queueFamilyIndex;
		device->GetDevice()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&mAllocator));
		mResult = VK_SUCCESS;
		return mResult;
	}

	void CommandPool::RemoveCommandBuffer(CommandBuffer* command)
	{
		if (command != nullptr)
		{
			auto iterator = std::find(mCommandBuffers.begin(), mCommandBuffers.end(), command);
			if (iterator != mCommandBuffers.end())
			{
				mCommandBuffers.erase(iterator);
				delete command;
			}
			else
			{
				assert(false && "CommandBuffer not Allocate form this Pool !");
			}
		}
	}

	CommandBuffer* CommandPool::Allocate(const VkCommandBufferAllocateInfo* info)
	{
		CommandBuffer* command = new CommandBuffer;
		command->Allocate(mDevice, info);
		mCommandBuffers.push_back(command);
		return command;
	}

	VkResult CommandPool::Reset(void)
	{
		HRESULT result = mAllocator->Reset();
		return (result == S_OK) ? VK_SUCCESS : VK_INCOMPLETE;
	}

	void CommandPool::CreateEmptyPipelineState(void)
	{
		auto device = mDevice->GetDevice();
		D3D_ROOT_SIGNATURE_VERSION highest_version = D3D_ROOT_SIGNATURE_VERSION_1_1;
		CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC signature_desc;
		signature_desc.Init_1_1(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

		ComPtr<ID3DBlob> signature;
		ComPtr<ID3DBlob> error;
		ThrowIfFailed(D3DX12SerializeVersionedRootSignature(&signature_desc, highest_version, &signature, &error));
		ThrowIfFailed(device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(),
			IID_PPV_ARGS(&mEmptyPipelineState)));
	}
}