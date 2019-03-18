#include "VKCmdDrawIndexed.h"
#include "VKCommandBuffer.h"

namespace VK
{
	CmdDrawIndexed::CmdDrawIndexed(void)
	{
	}

	CmdDrawIndexed::~CmdDrawIndexed(void)
	{
	}

	void CmdDrawIndexed::SetContent(uint32_t index_count,
		uint32_t instance_count,
		uint32_t first_index,
		uint32_t vertex_offset,
		uint32_t first_instance)
	{
		m_indexCount = index_count;
		m_instanceCount = instance_count;
		m_firstIndex = first_index;
		m_vertexOffset = vertex_offset;
		m_firstInstance = first_instance;
	}

	void CmdDrawIndexed::Encode(CommandBuffer * command)
	{
		auto command_list = command->GetCommandList();
		command_list->DrawIndexedInstanced(m_indexCount, m_instanceCount, m_firstIndex, m_vertexOffset, m_firstIndex);
	}
}