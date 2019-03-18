#pragma once
#include "VKDispatchable.h"


namespace VK
{
	class Queue : public Dispatchable
	{
	public:
		Queue(void);
		virtual ~Queue(void) override;

	public:
		VkResult Create(Device* device, const VkDeviceQueueCreateInfo* info);
		VkResult Submit(uint32_t count, const VkSubmitInfo* submits, VkFence fence);
		VkResult Present(const VkPresentInfoKHR* presnet);

	public:
		ID3D12CommandQueue * GetCommandQueue(void) const { return mQueue.Get(); }

	protected:
		uint32_t mFamily;

	protected:
		D3D12_COMMAND_QUEUE_DESC mDesc;
		ComPtr<ID3D12CommandQueue> mQueue;

	};
}

struct VkQueue_T final : public VK::Queue
{
	VkQueue_T(void) = default;
	virtual ~VkQueue_T(void) final override = default;
};
