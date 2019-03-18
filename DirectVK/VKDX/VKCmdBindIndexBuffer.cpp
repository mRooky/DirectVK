#include "VKCmdBindIndexBuffer.h"
#include "VKCommandBuffer.h"
#include "VKBuffer.h"

namespace VK
{
	CmdBindIndexBuffer::CmdBindIndexBuffer(void)
	{
	}

	CmdBindIndexBuffer::~CmdBindIndexBuffer(void)
	{
	}

	void CmdBindIndexBuffer::SetContent(VkBuffer buffer, VkDeviceSize offset, VkIndexType type)
	{
		m_buffer = buffer;
		m_offset = offset;
		m_type = type;
	}

	void CmdBindIndexBuffer::Encode(CommandBuffer * command)
	{
		auto command_list = command->GetCommandList();
		D3D12_INDEX_BUFFER_VIEW index_buffer_view = m_buffer->GetIndexView();
		index_buffer_view.BufferLocation += m_offset;
		command_list->IASetIndexBuffer(&index_buffer_view);
	}
}