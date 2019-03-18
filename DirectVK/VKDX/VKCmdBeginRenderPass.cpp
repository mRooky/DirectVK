#include "VKCmdBeginRenderPass.h"
#include "VKCommandBuffer.h"
#include "VKFrameBuffer.h"
#include "VKImageView.h"
#include "VKImage.h"
#include <cassert>

namespace VK
{
	CmdBeginRenderPass::CmdBeginRenderPass(void)
	{
	}

	CmdBeginRenderPass::~CmdBeginRenderPass(void)
	{
		m_clearValues.clear();
	}

	void CmdBeginRenderPass::SetContent(const VkRenderPassBeginInfo* info, VkSubpassContents content)
	{
		m_rect = info->renderArea;
		m_renderPass = info->renderPass;
		m_frameBuffer = info->framebuffer;
		m_content = content;
		for (uint32_t i = 0; i < info->clearValueCount; ++i)
		{
			const auto& clear_color = info->pClearValues[i];
			m_clearValues.push_back(clear_color);
		}
	}

	void CmdBeginRenderPass::Encode(CommandBuffer * command)
	{
		BindRenderTarget(command);
		ClearRenderTarget(command);
	}

	void CmdBeginRenderPass::BindRenderTarget(CommandBuffer * command)
	{
		auto commad_list = command->GetCommandList();
		std::vector<CD3DX12_CPU_DESCRIPTOR_HANDLE> descriptors;
		const size_t attachment_count = m_frameBuffer->GetAttachmentCount();
		descriptors.reserve(attachment_count);
		for (uint32_t i = 0; i < attachment_count; ++i)
		{
			CD3DX12_CPU_DESCRIPTOR_HANDLE descriptor = m_frameBuffer->GetAttachmentHandle(i);
			descriptors.push_back(descriptor);
			Image* image = m_frameBuffer->GetAttachment(i)->GetImage();
			image->Barrarier(commad_list, D3D12_RESOURCE_STATE_RENDER_TARGET);
		}

		UINT count = static_cast<UINT>(descriptors.size());
		const ImageView* depth_stencil = m_frameBuffer->GetDepthStencil();
		if (depth_stencil != nullptr)
		{
			CD3DX12_CPU_DESCRIPTOR_HANDLE descriptor = m_frameBuffer->GetDepthStencilHandle();
			commad_list->OMSetRenderTargets(count, descriptors.data(), FALSE, &descriptor);
		}
		else
		{
			commad_list->OMSetRenderTargets(count, descriptors.data(), FALSE, nullptr);
		}
		command->SetCurrentFrameBuffer(m_frameBuffer);

	}

	void CmdBeginRenderPass::ClearRenderTarget(CommandBuffer * command)
	{
		auto commad_list = command->GetCommandList();
		const size_t attachment_count = m_frameBuffer->GetAttachmentCount();
		assert(attachment_count < m_clearValues.size());
		for (size_t i = 0; i < attachment_count; ++i)
		{
			CD3DX12_CPU_DESCRIPTOR_HANDLE descriptor = m_frameBuffer->GetAttachmentHandle(i);
			const auto& color = m_clearValues.at(i);
			commad_list->ClearRenderTargetView(descriptor, color.color.float32, 0, nullptr);
		}

		const ImageView* depth_stencil = m_frameBuffer->GetDepthStencil();
		if (depth_stencil != nullptr)
		{
			assert(m_clearValues.size() >= attachment_count);
			CD3DX12_CPU_DESCRIPTOR_HANDLE descriptor = m_frameBuffer->GetDepthStencilHandle();
			const auto& color = m_clearValues.at(attachment_count);
			float depth = color.depthStencil.depth;
			uint32_t stencil = color.depthStencil.stencil;
			D3D12_CLEAR_FLAGS flags = D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL;
			commad_list->ClearDepthStencilView(descriptor, flags, depth, stencil, 0, nullptr);
		}

	}
}