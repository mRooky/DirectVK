#pragma once
#include "VKCommand.h"
#include "VKHeader.h"
#include <vector>

namespace VK
{
	class CmdBindDescriptorSets : public Command
	{
	public:
		CmdBindDescriptorSets(void);
		virtual ~CmdBindDescriptorSets(void) override;

	public:
		void SetContent(VkPipelineBindPoint point,
			VkPipelineLayout layout,
			uint32_t first_set,
			uint32_t set_count,
			const VkDescriptorSet* sets,
			uint32_t dynamic_count,
			const uint32_t* dynamics
		);

	public:
		virtual void Encode(CommandBuffer * command) override;

	private:
		void CreateRootSignature(CommandBuffer * command);

	private:
		VkPipelineBindPoint m_bindPoint;
		PipelineLayout* m_pipelineLayout;
		uint32_t m_firstSet;
		std::vector<const DescriptorSet*> m_sets;
		std::vector<uint32_t> m_dynamics;
	};

}