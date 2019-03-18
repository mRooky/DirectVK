#include "VKCmdDrawIndirect.h"
#include "VKBuffer.h"
#include "VKCommandBuffer.h"
#include <cassert>


namespace VK
{
	CmdDrawIndirect::CmdDrawIndirect(void)
	{
	}


	CmdDrawIndirect::~CmdDrawIndirect(void)
	{
	}

	void CmdDrawIndirect::SetContent(VkBuffer buffer, VkDeviceSize offset, uint32_t count, uint32_t stride)
	{
		m_buffer = buffer;
		m_offset = offset;
		m_count = count;
		m_stride = stride;
	}

	void CmdDrawIndirect::Encode(CommandBuffer * command)
	{
		auto command_list = command->GetCommandList();
		assert(false);
	}
}