#pragma once
#include "VKCommand.h"

namespace VK
{
	class CmdDrawIndirect : public Command
	{
	public:
		CmdDrawIndirect(void);
		virtual ~CmdDrawIndirect(void) override;

	public:
		void SetContent(VkBuffer buffer, VkDeviceSize offset, uint32_t count, uint32_t stride);

	public:
		virtual void Encode(CommandBuffer * command) override;

	private:
		Buffer * m_buffer;
		VkDeviceSize m_offset;
		uint32_t m_count;
		uint32_t m_stride;
	};
}
