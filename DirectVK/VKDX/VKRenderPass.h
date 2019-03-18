#pragma once
#include "VKDeviceObject.h"
#include <vector>

namespace VK
{
	class RenderSubPass;
	class RenderPass : public DeviceObject
	{
	public:
		RenderPass(void);
		virtual ~RenderPass(void);

	public:
		VkResult Create(Device* device, const VkRenderPassCreateInfo* info);

	public:
		inline size_t GetSubPassCount(void) const { return mSubPasses.size(); }
		inline RenderSubPass* GetSubPass(uint32_t index) const { return mSubPasses.at(index); }
		inline const VkAttachmentDescription& GetAttachmentDescription(uint32_t index) const
		{ 
			return mAttachmentDescriptions.at(index);
		}

	protected:
		std::vector<RenderSubPass*> mSubPasses;
		std::vector<VkAttachmentDescription> mAttachmentDescriptions;
	};
}

struct VkRenderPass_T final : public VK::RenderPass
{
	VkRenderPass_T(void) = default;
	virtual ~VkRenderPass_T(void) override final = default;
};
