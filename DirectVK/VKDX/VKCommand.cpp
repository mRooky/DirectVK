#include "VKCommand.h"
#include "VKCommandBuffer.h"

namespace VK
{
	Command::Command(void)
	{
	}

	Command::~Command(void)
	{
	}

	// + vkCmdBindPipeline()				//done
	// + vkCmdBindDescriptorSets()			//done
	// + vkCmdBindVertexBuffers()			//done
	// + vkCmdBindIndexBuffer()				//done
	// + vkCmdPushConstants()
	// + vkCmdSetViewport()					//done
	// + vkCmdSetDepthBias()
	// + vkCmdSetScissor()					//done
	// + vkCmdSetStencilCompareMask()
	// + vkCmdSetStencilWriteMask()
	// + vkCmdSetStencilReference()
	// + vkCmdSetBlendConstants()
	// + vkCmdBeginQuery()
	// + vkCmdEndQuery()
	// + vkCmdPipelineBarrier()				//done
	// + vkCmdWriteTimestamp()
	// + vkCmdExecuteCommands()
	// - vkCmdSetLineWidth()
	// - vkCmdSetDepthBounds()
	// - vkCmdWaitEvents()					//unimplement
}