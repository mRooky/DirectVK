#include "VKRenderPass.h"
#include "VKRenderSubPass.h"
#include <cstring>

namespace VK
{
	RenderPass::RenderPass(void)
	{
	}

	RenderPass::~RenderPass(void)
	{
		for (auto sub : mSubPasses)
		{
			delete sub;
		}
		mSubPasses.clear();
	}

	VkResult RenderPass::Create(Device* device, const VkRenderPassCreateInfo* info)
	{
		mDevice = device;
		for (uint32_t i = 0; i < info->subpassCount; ++i)
		{
			const auto& sub_pass = info->pSubpasses[i];
			RenderSubPass* sub = new RenderSubPass;
			sub->Create(this, &sub_pass);
			mSubPasses.push_back(sub);
		}

		mAttachmentDescriptions.reserve(info->attachmentCount);

		for (uint32_t i = 0; i < info->attachmentCount; ++i)
		{
			mAttachmentDescriptions.push_back(info->pAttachments[i]);
		}

		mResult = mSubPasses.size() > 0 ? VK_SUCCESS : VK_INCOMPLETE;
		return mResult;
	}
}