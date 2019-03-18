#include "VKCommandBuffer.h"
#include "VKCommand.h"
#include "VKCommandPool.h"
#include "VKDevice.h"
#include <cassert>
#include <algorithm>

namespace VK
{
	CommandBuffer::CommandBuffer(void)
	{
	}

	CommandBuffer::~CommandBuffer(void)
	{
		FreeCommand();
	}

	VkResult CommandBuffer::Allocate(Device* device, const VkCommandBufferAllocateInfo* info)
	{
		mDevice = device;
		mCreater = info->commandPool;
		mLevel = info->level;
		assert(info->commandBufferCount == 1);
		ID3D12PipelineState* pipeline_state = mCreater->GetDummyPipelineState();
		auto allocator = mCreater->GetAllocator();
		mDevice->GetDevice()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT,
			allocator, pipeline_state, IID_PPV_ARGS(&mCommandList));
		mCommandList->Close();
		mResult = VK_SUCCESS;
		return mResult;
	}

	VkResult CommandBuffer::Begin(const VkCommandBufferBeginInfo* info)
	{
		mBegin = true;
		mUsage = info->flags;
		bool secondary = mLevel == VK_COMMAND_BUFFER_LEVEL_SECONDARY;
		const VkCommandBufferInheritanceInfo* pInheritInfo = (secondary ? info->pInheritanceInfo : nullptr);
		return mResult;;
	}

	VkResult CommandBuffer::Reset(VkCommandBufferResetFlags flags)
	{
		FreeCommand();
		ID3D12PipelineState* pipeline_state = mCreater->GetDummyPipelineState();
		HRESULT result = mCommandList->Reset(mCreater->GetAllocator(), pipeline_state);
		return (result == S_OK) ? VK_SUCCESS : VK_INCOMPLETE;
	}

	VkResult CommandBuffer::End(void)
	{
		for (auto command : mCommands)
		{
			command->Encode(this);
		}
		mBegin = false;
		HRESULT result = mCommandList->Close();
		return (result == S_OK) ? VK_SUCCESS : VK_INCOMPLETE;
	}

	void CommandBuffer::FreeCommand(void)
	{
		for (auto command : mCommands)
		{
			delete command;
		}
		mCommands.clear();
	}

	void CommandBuffer::AppendCommand(Command* command)
	{
		mCommands.push_back(command);
	}
}