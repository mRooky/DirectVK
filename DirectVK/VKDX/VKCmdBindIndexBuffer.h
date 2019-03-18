#pragma once
#include "VKCommand.h"

namespace VK
{
	class CmdBindIndexBuffer : public Command
	{
	public:
		CmdBindIndexBuffer(void);
		virtual ~CmdBindIndexBuffer(void) override;

	public:
		void SetContent(VkBuffer buffer, VkDeviceSize offset, VkIndexType type);

	public:
		virtual void Encode(CommandBuffer * command) override;

	private:
		Buffer * m_buffer;
		VkDeviceSize m_offset;
		VkIndexType m_type;
	};
}
