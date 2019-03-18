#pragma once
#include "VKCommand.h"
#include <vector>

namespace VK
{
	typedef struct BufferBinding
	{
		VkBuffer buffer;
		VkDeviceSize offset;
	}BufferBinding;

	class CmdBindVertexBuffers : public Command
	{
	public:
		CmdBindVertexBuffers(void);
		virtual ~CmdBindVertexBuffers(void) override;

	public:
		void SetContent(uint32_t start, uint32_t count, const VkBuffer* buffers, const VkDeviceSize* offsets);

	public:
		virtual void Encode(CommandBuffer * command) override;

	private:
		UINT m_start;
		std::vector<BufferBinding> mBindings;
	};
}
