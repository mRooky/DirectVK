#pragma once
#include "VKCommand.h"

namespace VK
{
	class CmdEndRenderPass : public Command
	{
	public:
		CmdEndRenderPass(void);
		virtual ~CmdEndRenderPass(void);

	public:
		virtual void Encode(CommandBuffer * command) override;
	};
}
