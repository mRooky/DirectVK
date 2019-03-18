#include "VKQueue.h"
#include "VKDevice.h"
#include "VKFence.h"
#include "VKSemaphore.h"
#include "VKCommandBuffer.h"
#include "VKSwapchain.h"

namespace VK
{
	Queue::Queue(void)
	{
	}

	Queue::~Queue(void)
	{
	}

	VkResult Queue::Create(Device* device, const VkDeviceQueueCreateInfo* info)
	{
		mDesc = {};
		mDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		mDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		device->GetDevice()->CreateCommandQueue(&mDesc, IID_PPV_ARGS(&mQueue));
		mFamily = info->queueFamilyIndex;
		return mResult;
	}

	VkResult Queue::Submit(uint32_t count, const VkSubmitInfo* submits, VkFence fence)
	{
		std::vector<ID3D12CommandList*> command_lists;
		for (uint32_t i = 0; i < count; ++i)
		{
			const VkSubmitInfo& submit = submits[i];
			const uint32_t wait_count = submit.waitSemaphoreCount;
			for (uint32_t index = 0; index < wait_count; ++index)
			{
				VkSemaphore semaphore = submit.pWaitSemaphores[index];
				semaphore->Wait();
			}

			for (uint32_t i = 0; i < submit.commandBufferCount; ++i)
			{
				const CommandBuffer* command = submit.pCommandBuffers[i];
				command_lists.push_back(command->GetCommandList());
			}
		}

		UINT num = static_cast<UINT>(command_lists.size());
		mQueue->ExecuteCommandLists(num, command_lists.data());

		if (fence != VK_NULL_HANDLE)
		{
			UINT64 value = fence->GetValue();
			mQueue->Signal(fence->GetFence(), value + 1);
			fence->IncreaseValue();
		}

		for (uint32_t i = 0; i < count; ++i)
		{
			const VkSubmitInfo& submit = submits[i];
			const uint32_t wait_count = submit.signalSemaphoreCount;
			for (uint32_t index = 0; index < wait_count; ++index)
			{
				VkSemaphore semaphore = submit.pSignalSemaphores[index];
				semaphore->Notify();
			}
		}
		mResult = VK_SUCCESS;
		return mResult;
	}

	VkResult Queue::Present(const VkPresentInfoKHR* presnet)
	{
		for (uint32_t index = 0; index < presnet->waitSemaphoreCount; ++index)
		{
			VkSemaphore semaphore = presnet->pWaitSemaphores[index];
			semaphore->Wait();
		}

		for (uint32_t index = 0; index < presnet->swapchainCount; ++index)
		{
			VkSwapchainKHR swap_chain = presnet->pSwapchains[index];
			swap_chain->Present(1, 0);
		}
		return VK_SUCCESS;
	}
}