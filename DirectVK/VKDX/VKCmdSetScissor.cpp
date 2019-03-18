#include "VKCmdSetScissor.h"
#include "VKCommandBuffer.h"

namespace VK
{
	CmdSetScissor::CmdSetScissor(void)
	{
	}

	CmdSetScissor::~CmdSetScissor(void)
	{
	}

	void CmdSetScissor::SetContent(uint32_t first, uint32_t count, const VkRect2D* scissors)
	{
		m_first = first;
		for (uint32_t i = 0; i < count; ++i)
		{
			auto scissor = scissors[i];
			CD3DX12_RECT scissor_rect = {};
			scissor_rect.left = scissor.offset.x;
			scissor_rect.top = scissor.offset.y;
			scissor_rect.right = scissor.offset.x + scissor.extent.width;
			scissor_rect.bottom = scissor.offset.y + scissor.extent.height;
			m_scissors.push_back(scissor_rect);
		}
	}

	void CmdSetScissor::Encode(CommandBuffer * command)
	{
		auto command_list = command->GetCommandList();
		UINT count = static_cast<UINT>(m_scissors.size());
		command_list->RSSetScissorRects(count, m_scissors.data());
	}
}