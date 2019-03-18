#pragma once
#include "VKCommand.h"
#include <vector>

namespace VK
{
	class CmdSetViewport : public Command
	{
	public:
		CmdSetViewport(void);
		virtual ~CmdSetViewport(void) override;

	public:
		void SetContent(uint32_t first, uint32_t count, const VkViewport* viewports);

	public:
		virtual void Encode(CommandBuffer * command) override;

	private:
		uint32_t m_first;
		std::vector<CD3DX12_VIEWPORT> m_viewports;
	};

}