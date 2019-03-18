#pragma once
#include "VKDeviceObject.h"
#include <vector>

namespace VK
{
	class Pipeline : public DeviceObject
	{
	public:
		Pipeline(void);
		virtual ~Pipeline(void) override;

	public:
		VkResult Create(Device* device, PipelineCache* cache, const VkGraphicsPipelineCreateInfo* info);
		VkResult Create(Device* device, PipelineCache* cache, const VkComputePipelineCreateInfo* info);

	public:
		void GetShaderCode(const VkGraphicsPipelineCreateInfo* info, D3D12_GRAPHICS_PIPELINE_STATE_DESC* desc) const;
		std::vector<D3D12_INPUT_ELEMENT_DESC> GetInputLayout(const VkGraphicsPipelineCreateInfo* info);
		CD3DX12_RASTERIZER_DESC GetRasterizer(const VkGraphicsPipelineCreateInfo* info) const;
		CD3DX12_BLEND_DESC GetBlend(const VkGraphicsPipelineCreateInfo* info) const;
		CD3DX12_DEPTH_STENCIL_DESC GetDepthStencil(const VkGraphicsPipelineCreateInfo* info) const;

	public:
		inline PipelineCache* GetCache(void) const { return mCache; }
		inline PipelineLayout* GetLayout(void) const { return mLayout; }
		inline ID3D12PipelineState* GetState(void) const { return mPipeline.Get(); }
		inline D3D12_PRIMITIVE_TOPOLOGY GetTopology(void) const { return mTopology; }

	public:
		inline const VkVertexInputBindingDescription& GetInputBinding(uint32_t index) const { return mInputBindings.at(index); }

	protected:
		PipelineLayout * mLayout;
		PipelineCache * mCache;
		uint32_t mSubPassIndex;
		RenderPass* mRenderPass;

	protected:
		std::vector<VkVertexInputBindingDescription> mInputBindings;

	protected:
		D3D12_PRIMITIVE_TOPOLOGY mTopology;
		ComPtr<ID3D12PipelineState> mPipeline;
	};
}

struct VkPipeline_T final : public VK::Pipeline
{
	VkPipeline_T(void) = default;
	virtual ~VkPipeline_T(void) final override = default;
};
