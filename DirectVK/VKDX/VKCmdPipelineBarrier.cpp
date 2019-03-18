#include "VKCmdPipelineBarrier.h"
#include "VKCommandBuffer.h"


namespace VK
{
	CmdPipelineBarrier::CmdPipelineBarrier(void)
	{
	}

	CmdPipelineBarrier::~CmdPipelineBarrier(void)
	{
	}

	void CmdPipelineBarrier::Encode(CommandBuffer * command)
	{
		auto command_list = command->GetCommandList();
		//command_list->ResourceBarrier();
	}
}