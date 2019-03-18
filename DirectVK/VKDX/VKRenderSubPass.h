#pragma once
#include "VKDeviceObject.h"
#include <vector>

namespace VK
{
	class RenderSubPass : public DeviceObject
	{
	public:
		RenderSubPass(void);
		virtual ~RenderSubPass(void) override;

	public:
		VkResult Create(RenderPass* pass, const VkSubpassDescription* description);

	public:
		inline size_t GetColorAttachmentCount(void) const { return mColorAttachments.size(); }
		inline const VkAttachmentReference& GetColorAttachment(uint32_t index) const { return mColorAttachments.at(index); }
		inline const VkAttachmentReference& GetDepthStencilAttachment(void) const { return mDepthStencilAttachment; }

	protected:
		RenderPass * mRenderPass;
		VkAttachmentReference mDepthStencilAttachment;
		std::vector<uint32_t> mPreserveAttachments;
		std::vector<VkAttachmentReference> mInputAttachments;
		std::vector<VkAttachmentReference> mColorAttachments;
		//std::vector<VkAttachmentReference> mResolveAttachments;
	};
}
