#include "VKPipelineCache.h"
#include "VKPipeline.h"
#include <cassert>
#include <cstring>

namespace VK
{
	PipelineCache::PipelineCache(void) :
		mCached(false)
	{
	}

	PipelineCache::~PipelineCache(void)
	{
	}

	VkResult PipelineCache::Create(Device* device, const VkPipelineCacheCreateInfo* info)
	{
		mDevice = device;
		mResult = VK_SUCCESS;
		return mResult;
	}

	VkResult PipelineCache::CachePipeline(Pipeline* pipeline)
	{
		ID3D12PipelineState* pipeline_state = pipeline->GetState();
		HRESULT result = pipeline_state->GetCachedBlob(&mCache);
		mCached = !FAILED(result);
		mResult = mCached ? VK_SUCCESS : VK_INCOMPLETE;
		return mResult;
	}

	void PipelineCache::GetCacheData(size_t* size, void* data)
	{
		if (data != nullptr)
		{
			*size = mCache->GetBufferSize();
			return;
		}

		assert(*size <= mCache->GetBufferSize());
		if (data != nullptr)
		{
			std::memcpy(data, mCache->GetBufferPointer(), *size);
		}
	}
}