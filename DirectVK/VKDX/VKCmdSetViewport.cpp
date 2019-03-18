#include "VKCmdSetViewport.h"
#include "VKCommandBuffer.h"

namespace VK
{
	CmdSetViewport::CmdSetViewport(void)
	{
	}

	CmdSetViewport::~CmdSetViewport(void)
	{
	}

	void CmdSetViewport::SetContent(uint32_t first, uint32_t count, const VkViewport* viewports)
	{
		m_first = first;
		for (uint32_t i = 0; i < count; ++i)
		{
			auto vk_viewport = viewports[i];
			CD3DX12_VIEWPORT viewport = {};
			viewport.TopLeftX = vk_viewport.x;
			viewport.TopLeftY = vk_viewport.y;
			viewport.Width = vk_viewport.width;
			viewport.Height = vk_viewport.height;
			viewport.MaxDepth = vk_viewport.maxDepth;
			viewport.MinDepth = vk_viewport.minDepth;
			m_viewports.push_back(viewport);
		}
	}

	void CmdSetViewport::Encode(CommandBuffer * command)
	{
		auto command_list = command->GetCommandList();
		UINT count = static_cast<UINT>(m_viewports.size());
		command_list->RSSetViewports(count, m_viewports.data());
	}
}