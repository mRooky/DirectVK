#include "VKCmdBindDescriptorSets.h"
#include "VKDescriptorSet.h"
#include "VKPipelineLayout.h"
#include "VKCommandBuffer.h"
#include "VKDevice.h"

namespace VK
{
	CmdBindDescriptorSets::CmdBindDescriptorSets(void)
	{
	}

	CmdBindDescriptorSets::~CmdBindDescriptorSets(void)
	{
	}

	void CmdBindDescriptorSets::SetContent(VkPipelineBindPoint point,
		VkPipelineLayout layout,
		uint32_t first_set,
		uint32_t set_count,
		const VkDescriptorSet* sets,
		uint32_t dynamic_count,
		const uint32_t* dynamics)
	{
		m_bindPoint = point;
		m_pipelineLayout = layout;
		m_firstSet = first_set;
		m_sets.reserve(set_count);
		for (uint32_t i = 0; i < set_count; ++i)
		{
			const DescriptorSet* descriptor_set = sets[i];
			m_sets.push_back(descriptor_set);
		}

		m_dynamics.reserve(dynamic_count);
		for (uint32_t i = 0; i < dynamic_count; ++i)
		{
			m_dynamics.push_back(dynamics[i]);
		}
	}

	void CmdBindDescriptorSets::Encode(CommandBuffer * command)
	{
		auto command_list = command->GetCommandList();
		auto root_signature = m_pipelineLayout->GetRootSignature();
		command_list->SetGraphicsRootSignature(root_signature);

	}
}
