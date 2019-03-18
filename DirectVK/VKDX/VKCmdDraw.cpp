#include "VKCmdDraw.h"
#include "VKCommandBuffer.h"

namespace VK
{
	CmdDraw::CmdDraw(void)
	{
	}

	CmdDraw::~CmdDraw(void)
	{
	}

	void CmdDraw::SetContent(uint32_t vertex_count,
		uint32_t instance_count,
		uint32_t first_vertex,
		uint32_t first_instance)
	{
		m_vertexCount = vertex_count;
		m_instanceCount = instance_count;
		m_firstVertex = first_vertex;
		m_firstInstance = first_instance;
	}

	void CmdDraw::Encode(CommandBuffer * command)
	{
		auto command_list = command->GetCommandList();
		command_list->DrawInstanced(m_vertexCount, m_instanceCount, m_firstVertex, m_firstInstance);
	}
}