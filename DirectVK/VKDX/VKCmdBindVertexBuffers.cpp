#include "VKCmdBindVertexBuffers.h"
#include "VKCommandBuffer.h"
#include "VKBuffer.h"
#include "VKPipeline.h"
#include <cassert>

namespace VK
{
	CmdBindVertexBuffers::CmdBindVertexBuffers(void)
	{
	}

	CmdBindVertexBuffers::~CmdBindVertexBuffers(void)
	{
	}

	void CmdBindVertexBuffers::SetContent(uint32_t start, uint32_t count, const VkBuffer* buffers, const VkDeviceSize* offsets)
	{
		m_start = static_cast<UINT>(start);
		mBindings.reserve(count);
		BufferBinding buffer_binding = {};
		for (uint32_t i = 0; i < count; ++i)
		{
			buffer_binding.buffer = buffers[i];
			buffer_binding.offset = offsets[i];
			mBindings.push_back(buffer_binding);
		}
	}

	void CmdBindVertexBuffers::Encode(CommandBuffer * command)
	{
		auto command_list = command->GetCommandList();
		std::vector<D3D12_VERTEX_BUFFER_VIEW> vertex_buffer_views;
		vertex_buffer_views.reserve(mBindings.size());
		for (uint32_t i = 0; i < mBindings.size(); ++i)
		{
			const BufferBinding& binding = mBindings.at(i);
			D3D12_VERTEX_BUFFER_VIEW vertex_buffer_view = binding.buffer->GetVertexView();
			vertex_buffer_view.BufferLocation += binding.offset;

			Pipeline* pipeline = command->GetCurrentPipeline();
			assert(pipeline != nullptr);
			const VkVertexInputBindingDescription& description = pipeline->GetInputBinding(i);
			vertex_buffer_view.StrideInBytes = description.stride;

			vertex_buffer_views.push_back(vertex_buffer_view);
		}
		UINT num_views = static_cast<UINT>(vertex_buffer_views.size());
		assert(num_views > 0);
		command_list->IASetVertexBuffers(m_start, num_views, vertex_buffer_views.data());
	}
}