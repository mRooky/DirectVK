#pragma once
#include "VKCommand.h"

namespace VK
{
	class CmdBindPipeline : public Command
	{
	public:
		CmdBindPipeline(void);
		virtual ~CmdBindPipeline(void);

	public:
		void SetContent(VkPipelineBindPoint point, VkPipeline pipeline);

	public:
		virtual void Encode(CommandBuffer * command) override;

	private:
		VkPipelineBindPoint m_bindPoint;
		Pipeline* m_pipeline;
	};
}