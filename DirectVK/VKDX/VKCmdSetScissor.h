#pragma once
#include "VKCommand.h"
#include <vector>

namespace VK
{
	class CmdSetScissor : public Command
	{
	public:
		CmdSetScissor(void);
		virtual ~CmdSetScissor(void) override;

	public:
		void SetContent(uint32_t first, uint32_t count, const VkRect2D* scissors);

	public:
		virtual void Encode(CommandBuffer * command) override;

	private:
		uint32_t m_first;
		std::vector<CD3DX12_RECT> m_scissors;
	};
}
