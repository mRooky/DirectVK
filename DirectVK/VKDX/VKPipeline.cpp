#include "VKPipeline.h"
#include "VKPipelineLayout.h"
#include "VKDevice.h"
#include "VKShaderModule.h"
#include "VKUtility.h"
#include "VKRenderPass.h"
#include "VKRenderSubPass.h"
#include <cassert>

namespace VK
{
	Pipeline::Pipeline(void)
	{
	}

	Pipeline::~Pipeline(void)
	{
	}

	VkResult Pipeline::Create(Device* device, PipelineCache* cache, const VkComputePipelineCreateInfo* info)
	{
		assert(false);
		return VK_INCOMPLETE;
	}

	VkResult Pipeline::Create(Device* device, PipelineCache* cache, const VkGraphicsPipelineCreateInfo* info)
	{
		mDevice = device;
		mCache = cache;
		mLayout = info->layout;
		mRenderPass = info->renderPass;
		mSubPassIndex = info->subpass;

		D3D12_GRAPHICS_PIPELINE_STATE_DESC state_desc = {};
		state_desc.pRootSignature = mLayout->GetRootSignature();

		auto input_elements = GetInputLayout(info);
		state_desc.InputLayout.NumElements = static_cast<UINT>(input_elements.size());
		state_desc.InputLayout.pInputElementDescs = input_elements.data();

		GetShaderCode(info, &state_desc);

		state_desc.RasterizerState = GetRasterizer(info);
		state_desc.BlendState = GetBlend(info);
		state_desc.DepthStencilState = GetDepthStencil(info);
		state_desc.SampleMask = UINT_MAX;
		state_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

		RenderSubPass* sub_pass = mRenderPass->GetSubPass(mSubPassIndex);
		UINT num = static_cast<UINT>(sub_pass->GetColorAttachmentCount());
		state_desc.NumRenderTargets = num;

		for (UINT i = 0; i < num; ++i)
		{
			uint32_t index = sub_pass->GetColorAttachment(i).attachment;
			VkFormat format = mRenderPass->GetAttachmentDescription(index).format;
			state_desc.RTVFormats[0] = Format::GetFormat(format);
		}

		uint32_t depth_index = sub_pass->GetDepthStencilAttachment().attachment;
		VkFormat dsv_format = mRenderPass->GetAttachmentDescription(depth_index).format;

		state_desc.DSVFormat = Format::GetFormat(dsv_format);
		state_desc.SampleDesc.Count = 1;

		ThrowIfFailed(device->GetDevice()->CreateGraphicsPipelineState(&state_desc, IID_PPV_ARGS(&mPipeline)));

		mTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		mResult = VK_SUCCESS;
		return mResult;
	}

	void Pipeline::GetShaderCode(const VkGraphicsPipelineCreateInfo* info,
		D3D12_GRAPHICS_PIPELINE_STATE_DESC* desc) const
	{
		for (uint32_t i = 0; i < info->stageCount; ++i)
		{
			const VkPipelineShaderStageCreateInfo& shader_stage = info->pStages[i];
			VkShaderStageFlagBits flag = shader_stage.stage;
			switch (flag)
			{
			case VK_SHADER_STAGE_VERTEX_BIT:
				desc->VS = shader_stage.module->GetByteCode();
				break;
			case VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT:
				desc->HS = shader_stage.module->GetByteCode();
				break;
			case VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT:
				desc->DS = shader_stage.module->GetByteCode();
				break;
			case VK_SHADER_STAGE_GEOMETRY_BIT:
				desc->GS = shader_stage.module->GetByteCode();
				break;
			case VK_SHADER_STAGE_FRAGMENT_BIT:
				desc->PS = shader_stage.module->GetByteCode();
				break;
			default:
				assert(false);
				break;
			}
		}
	}

	std::vector<D3D12_INPUT_ELEMENT_DESC> Pipeline::GetInputLayout(const VkGraphicsPipelineCreateInfo* info)
	{
		const VkPipelineVertexInputStateCreateInfo* vertex_input = info->pVertexInputState;

		mInputBindings.reserve(vertex_input->vertexBindingDescriptionCount);

		for (uint32_t i = 0; i < vertex_input->vertexBindingDescriptionCount; ++i)
		{
			mInputBindings.push_back(vertex_input->pVertexBindingDescriptions[i]);
		}

		uint32_t count = vertex_input->vertexAttributeDescriptionCount;
		std::vector<D3D12_INPUT_ELEMENT_DESC> input_elements;

		input_elements.reserve(count);
		for (uint32_t i = 0; i < count; ++i)
		{
			D3D12_INPUT_ELEMENT_DESC input_element = {};
			const VkVertexInputAttributeDescription& attribute = vertex_input->pVertexAttributeDescriptions[i];
			uint32_t binding = attribute.binding;
			const VkVertexInputBindingDescription& description = mInputBindings.at(binding);
			input_element.SemanticName = "VS_INPUT";					// Semantic Name as Default
			input_element.SemanticIndex = i;							// Zero-base Number as Default
			input_element.Format = Format::GetFormat(attribute.format);
			input_element.AlignedByteOffset = attribute.offset;
			input_element.InputSlot = binding;
			input_element.InputSlotClass = Utility::GetInputRate(description.inputRate);
			input_elements.push_back(input_element);
		}

		return input_elements;
	}

	CD3DX12_RASTERIZER_DESC Pipeline::GetRasterizer(const VkGraphicsPipelineCreateInfo* info) const
	{
		CD3DX12_RASTERIZER_DESC rasterizer(D3D12_DEFAULT);
		rasterizer.CullMode = D3D12_CULL_MODE_NONE;
		return rasterizer;
	}

	CD3DX12_BLEND_DESC Pipeline::GetBlend(const VkGraphicsPipelineCreateInfo* info) const
	{
		CD3DX12_BLEND_DESC blend_desc(D3D12_DEFAULT);
		return blend_desc;
	}

	CD3DX12_DEPTH_STENCIL_DESC Pipeline::GetDepthStencil(const VkGraphicsPipelineCreateInfo* info) const
	{
		CD3DX12_DEPTH_STENCIL_DESC depth_stencil_desc(D3D12_DEFAULT);
		return depth_stencil_desc;
	}
}