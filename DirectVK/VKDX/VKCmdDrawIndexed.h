#pragma once
#include "VKCommand.h"

namespace VK
{
	class CmdDrawIndexed : public Command
	{
	public:
		CmdDrawIndexed();
		virtual ~CmdDrawIndexed(); public:

	public:
		void SetContent(uint32_t index_count,
			uint32_t instance_count,
			uint32_t first_index,
			uint32_t vertex_offset,
			uint32_t first_instance);

	public:
		virtual void Encode(CommandBuffer * command) override;

	private:
		uint32_t m_indexCount;
		uint32_t m_instanceCount;
		uint32_t m_firstIndex;
		uint32_t m_vertexOffset;
		uint32_t m_firstInstance;
	};
}
