#pragma once
#include "VKDeviceObject.h"

namespace VK
{
	class BufferView : public DeviceObject
	{
	public:
		BufferView(void);
		virtual ~BufferView(void);

	public:
		VkResult Create(Device* device, const VkBufferViewCreateInfo* info);

	public:
		inline const D3D12_VERTEX_BUFFER_VIEW& GetView(void) const { return mBufferView; }

	protected:
		VkFormat mFormat;
		Buffer * mBuffer;

	protected:
		D3D12_VERTEX_BUFFER_VIEW mBufferView;
	};

}

struct VkBufferView_T final : public VK::BufferView
{
	VkBufferView_T(void) = default;
	virtual ~VkBufferView_T(void) override final = default;
};

