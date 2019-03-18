#include "VKCmdBindPipeline.h"
#include "VKPipeline.h"
#include "VKCommandBuffer.h"
#include <cassert>

namespace VK
{
	CmdBindPipeline::CmdBindPipeline(void)
	{
	}

	CmdBindPipeline::~CmdBindPipeline(void)
	{
	}

	void CmdBindPipeline::SetContent(VkPipelineBindPoint point, VkPipeline pipeline)
	{
		m_bindPoint = point;
		m_pipeline = pipeline;
	}

	void CmdBindPipeline::Encode(CommandBuffer * command)
	{
		auto command_list = command->GetCommandList();
		command_list->SetPipelineState(m_pipeline->GetState());
		command_list->IASetPrimitiveTopology(m_pipeline->GetTopology());
		command->SetCurrentPipeline(m_pipeline);
	}
}