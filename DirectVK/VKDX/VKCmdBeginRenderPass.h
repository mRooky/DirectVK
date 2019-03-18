#pragma once
#include "VKCommand.h"
#include <vector>

namespace VK
{
	class CmdBeginRenderPass : public Command
	{
	public:
		CmdBeginRenderPass(void);
		virtual ~CmdBeginRenderPass(void) override;

	public:
		void SetContent(const VkRenderPassBeginInfo* info, VkSubpassContents content);

	public:
		virtual void Encode(CommandBuffer * command) override;

	private:
		void BindRenderTarget(CommandBuffer * command);
		void ClearRenderTarget(CommandBuffer * command);

	private:
		VkRect2D m_rect;
		VkRenderPass m_renderPass;
		VkFramebuffer m_frameBuffer;
		VkSubpassContents m_content;
		std::vector<VkClearValue> m_clearValues;
	};
}
