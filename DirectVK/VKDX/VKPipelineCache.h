#pragma once
#include "VKDeviceObject.h"

namespace VK
{
	class PipelineCache : public DeviceObject
	{
	public:
		PipelineCache(void);
		virtual ~PipelineCache(void) override;

	public:
		VkResult Create(Device* device, const VkPipelineCacheCreateInfo* info);

	public:
		VkResult CachePipeline(Pipeline* pipeline);
		void GetCacheData(size_t* size, void* data);

	public:
		bool IsCached(void) const { return mCached; }
		ID3DBlob* GetCache(void) const { return mCache.Get(); }

	protected:
		bool mCached;
		ComPtr<ID3DBlob> mCache;
	};
}

struct VkPipelineCache_T final : public VK::PipelineCache
{
	VkPipelineCache_T(void) = default;
	virtual ~VkPipelineCache_T(void) final override = default;
};
