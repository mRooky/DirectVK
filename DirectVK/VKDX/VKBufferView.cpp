#include "VKBufferView.h"
#include "VKBuffer.h"

namespace VK
{
	BufferView::BufferView(void)
	{
	}

	BufferView::~BufferView(void)
	{
	}

	VkResult BufferView::Create(Device* device, const VkBufferViewCreateInfo* info)
	{
		mDevice = device;
		mBuffer = info->buffer;
		mFormat = info->format;
		mBufferView = mBuffer->GetVertexView();
		mBufferView.BufferLocation += info->offset;					//done
		mBufferView.SizeInBytes = static_cast<UINT>(info->range);	//done
		return mResult;
	}

}