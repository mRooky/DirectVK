#pragma once
#include "VKResource.h"

namespace VK
{
	class Buffer : public Resource
	{
		friend class Device;
	protected:
		Buffer(void);
		virtual ~Buffer(void) override;

	public:
		VkResult Create(Device* device, const VkBufferCreateInfo* info);

	protected:
		virtual void CreateRequirements(void) override;
		virtual void CreateResource(D3D12_HEAP_TYPE type) override;

	protected:
		VkBufferUsageFlags mUsage;

	public:
		D3D12_VERTEX_BUFFER_VIEW GetVertexView(void) const;
		D3D12_INDEX_BUFFER_VIEW GetIndexView(void) const;
		D3D12_SHADER_RESOURCE_VIEW_DESC GetResourceView(void) const;
		D3D12_CONSTANT_BUFFER_VIEW_DESC GetConstView(void) const;

	};
}

struct VkBuffer_T final : public VK::Buffer
{
private:
	VkBuffer_T(void) = default;
	virtual ~VkBuffer_T(void) override final = default;
};
