#pragma once
#include "VKObject.h"

namespace VK
{
	class Command : public Object
	{
		friend class CommandBuffer;
	protected:
		Command(void);
		virtual ~Command(void) override;

	public:
		virtual void Encode(CommandBuffer * command) = 0;

	};

	class CmdBindPipeline;
	class CmdBindDescriptorSets;
	class CmdBindVertexBuffers;
	class CmdBindIndexBuffer;
	class CmdPushConstants;
	class CmdSetViewport;
	class CmdSetDepthBias;
	class CmdSetScissor;
	class CmdSetStencilCompareMask;
	class CmdSetStencilWriteMask;
	class CmdSetStencilReference;
	class CmdSetBlendConstants;
	class CmdBeginQuery;
	class CmdEndQuery;
	class CmdPipelineBarrier;
	class CmdWriteTimestamp;
	class CmdExecuteCommands;
	class CmdSetLineWidth;
	class CmdSetDepthBounds;
	class CmdWaitEvents;
	class CmdPipelineBarrier;
}