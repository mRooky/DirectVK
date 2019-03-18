#pragma once
#include "VKCommand.h"
#include <vector>

namespace VK
{
	class CmdPipelineBarrier : public Command
	{
	public:
		CmdPipelineBarrier(void);
		virtual ~CmdPipelineBarrier(void) override;

	public:
		void SetContent(VkPipelineBindPoint point, VkPipeline pipeline);

	public:
		virtual void Encode(CommandBuffer * command) override;

	private:
		VkPipelineStageFlags                        srcStageMask;
		VkPipelineStageFlags                        dstStageMask;
		VkDependencyFlags                           dependencyFlags;
		std::vector<VkMemoryBarrier>                pMemoryBarriers;
		std::vector<VkBufferMemoryBarrier>			pBufferMemoryBarriers;
		std::vector<VkImageMemoryBarrier>			pImageMemoryBarriers;
	};

}