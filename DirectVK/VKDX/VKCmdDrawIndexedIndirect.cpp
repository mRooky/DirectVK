#include "VKCmdDrawIndexedIndirect.h"
#include "VKBuffer.h"
#include "VKCommandBuffer.h"
#include <cassert>

namespace VK
{
	CmdDrawIndexedIndirect::CmdDrawIndexedIndirect(void)
	{
	}

	CmdDrawIndexedIndirect::~CmdDrawIndexedIndirect(void)
	{
	}

	void CmdDrawIndexedIndirect::SetContent(VkBuffer buffer, VkDeviceSize offset, uint32_t count, uint32_t stride)
	{
		m_buffer = buffer;
		m_offset = offset;
		m_count = count;
		m_stride = stride;
	}

	void CmdDrawIndexedIndirect::Encode(CommandBuffer * command)
	{
		auto command_list = command->GetCommandList();
		assert(false);
	}
}