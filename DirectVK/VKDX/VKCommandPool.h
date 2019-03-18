#pragma once
#include "VKDeviceObject.h"
#include <vector>

namespace VK
{
	class CommandPool : public DeviceObject
	{
	public:
		CommandPool(void);
		virtual ~CommandPool(void) override;

	public:
		VkResult Create(Device* device, const VkCommandPoolCreateInfo* info);
		CommandBuffer* Allocate(const VkCommandBufferAllocateInfo* info);
		VkResult Reset(void);

	public:
		void RemoveCommandBuffer(CommandBuffer* command);

	public:
		inline ID3D12CommandAllocator* GetAllocator(void) const { return mAllocator.Get(); }
		inline ID3D12PipelineState* GetDummyPipelineState(void) const { return mEmptyPipelineState.Get(); }

	private:
		void CreateEmptyPipelineState(void);

	protected:
		uint32_t mFamily;
		std::vector<CommandBuffer*> mCommandBuffers;
		ComPtr<ID3D12PipelineState> mEmptyPipelineState;

	protected:
		ComPtr<ID3D12CommandAllocator> mAllocator;
	};
}

struct VkCommandPool_T final : public VK::CommandPool
{
	VkCommandPool_T(void) = default;
	virtual ~VkCommandPool_T(void) override final = default;
};
