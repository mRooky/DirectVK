#pragma once
#include "VKCommand.h"

namespace VK
{
	class CmdDraw : public Command
	{
	public:
		CmdDraw();
		virtual ~CmdDraw();

	public:
		void SetContent(uint32_t vertex_count,
			uint32_t instance_count,
			uint32_t first_vertex,
			uint32_t first_instance);

	public:
		virtual void Encode(CommandBuffer * command) override;

	private:
		uint32_t m_vertexCount;
		uint32_t m_instanceCount;
		uint32_t m_firstVertex;
		uint32_t m_firstInstance;
	};

}