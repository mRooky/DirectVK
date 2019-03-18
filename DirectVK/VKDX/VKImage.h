#pragma once
#include "VKResource.h"

namespace VK
{
	class Image : public Resource
	{
		friend class Device;
	protected:
		Image(void);
		virtual ~Image(void) override;

	public:
		VkResult Create(Device* device, const VkImageCreateInfo* info);

	public:
		inline VkImageType GetImageType(void) const { return mType; }
		inline const VkExtent3D& GetExtent(void) const { return mExtent; }
		inline uint32_t GetMipLevels(void) const { return mMipLevels; }
		inline uint32_t GetArrayLayers(void) const { return mArrayLayers; }
		inline VkSampleCountFlags GetSamples(void) const { return mSamples; }
		inline VkImageUsageFlags GetUsage(void) const { return mUsage; }

	protected:
		virtual void CreateRequirements(void) override;
		virtual void CreateResource(D3D12_HEAP_TYPE type) override;

	protected:
		VkImageType mType;
		VkExtent3D mExtent;
		uint32_t mMipLevels;
		uint32_t mArrayLayers;
		VkSampleCountFlags mSamples;
		VkImageUsageFlags mUsage;

	};
}

struct VkImage_T final : public VK::Image
{
private:
	VkImage_T(void) = default;
	virtual ~VkImage_T(void) override final = default;
};
