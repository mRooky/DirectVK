#include "VKRenderSubPass.h"

namespace VK
{
	RenderSubPass::RenderSubPass(void)
	{
	}

	RenderSubPass::~RenderSubPass(void)
	{
	}

	VkResult RenderSubPass::Create(RenderPass* pass, const VkSubpassDescription* description)
	{
		mRenderPass = pass;
		uint32_t count = description->colorAttachmentCount;
		for (uint32_t i = 0; i < count; ++i)
		{
			const auto& color = description->pColorAttachments[i];
			mColorAttachments.push_back(color);
		}

		count = description->inputAttachmentCount;
		for (uint32_t i = 0; i < count; ++i)
		{
			const auto& attachment = description->pInputAttachments[i];
			mInputAttachments.push_back(attachment);
		}

		count = description->preserveAttachmentCount;
		for (uint32_t i = 0; i < count; ++i)
		{
			const auto& attachment = description->pPreserveAttachments[i];
			mPreserveAttachments.push_back(attachment);
		}

		if (description->pDepthStencilAttachment != nullptr)
		{
			mDepthStencilAttachment = *description->pDepthStencilAttachment;
		}
		mResult = VK_SUCCESS;
		return mResult;
	}
}