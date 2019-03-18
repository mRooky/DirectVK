#include "VKCmdEndRenderPass.h"
#include "VKCommandBuffer.h"
#include "VKFrameBuffer.h"
#include "VKImageView.h"
#include "VKImage.h"


namespace VK
{
	CmdEndRenderPass::CmdEndRenderPass(void)
	{
	}

	CmdEndRenderPass::~CmdEndRenderPass(void)
	{
	}

	void CmdEndRenderPass::Encode(CommandBuffer * command)
	{
		FrameBuffer* current_frame = command->GetCurrentFrameBuffer();
		if (current_frame != nullptr)
		{
			auto commad_list = command->GetCommandList();
			const size_t attachment_count = current_frame->GetAttachmentCount();
			for (uint32_t i = 0; i < attachment_count; ++i)
			{
				CD3DX12_CPU_DESCRIPTOR_HANDLE descriptor = current_frame->GetAttachmentHandle(i);
				Image* image = current_frame->GetAttachment(i)->GetImage();
				image->Barrarier(commad_list, D3D12_RESOURCE_STATE_PRESENT);
			}
		}
		command->SetCurrentFrameBuffer(nullptr);
	}
}