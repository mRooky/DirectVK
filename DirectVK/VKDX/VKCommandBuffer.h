#pragma once
#include "VKDispatchable.h"
#include <vector>

namespace VK
{
	class Command;
	class CommandBuffer : public Dispatchable
	{
		friend class CommandPool;
	protected:
		CommandBuffer(void);
		virtual ~CommandBuffer(void) override;

	public:
		VkResult Allocate(Device* device, const VkCommandBufferAllocateInfo* info);

	public:
		inline size_t GetCommandCount(void) const { return mCommands.size(); }
		inline ID3D12GraphicsCommandList* GetCommandList(void) const { return mCommandList.Get(); }
		inline bool IsBegin(void) const { return mBegin; }
		inline Device* GetDevice(void) const { return mDevice; }

	public:
		inline void SetCurrentFrameBuffer(FrameBuffer * frame) { mCurrentFrameBuffer = frame; }
		inline FrameBuffer * GetCurrentFrameBuffer(void) const { return mCurrentFrameBuffer; }
		inline void SetCurrentPipeline(Pipeline * pipeline) { mCurrentPipeline = pipeline; }
		inline Pipeline * GetCurrentPipeline(void) const { return mCurrentPipeline; }

	public:
		void AppendCommand(Command* command);

	public:
		VkResult Begin(const VkCommandBufferBeginInfo* info);
		VkResult Reset(VkCommandBufferResetFlags flags);
		VkResult End(void);

	private:
		void FreeCommand(void);

	protected:
		bool mBegin;
		Device* mDevice;
		CommandPool * mCreater;

	protected:
		VkCommandBufferLevel mLevel;
		VkCommandBufferUsageFlags mUsage;

	protected:
		FrameBuffer * mCurrentFrameBuffer;
		Pipeline* mCurrentPipeline;
		std::vector<Command*> mCommands;

	protected:
		ComPtr<ID3D12GraphicsCommandList> mCommandList;

	};
}

struct VkCommandBuffer_T final : public VK::CommandBuffer
{
private:
	VkCommandBuffer_T(void) = default;
	virtual ~VkCommandBuffer_T(void) override final = default;
};
