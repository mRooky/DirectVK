#include "VKPhysicalDevice.h"
#include "VKDevice.h"
#include <cstring>
#include <limits>
#include <cassert>

namespace VK
{
	PhysicalDevice::PhysicalDevice(void)
	{
		mDesc = {};
	}

	PhysicalDevice::~PhysicalDevice(void)
	{
	}

	void PhysicalDevice::Initialize(Instance* instance, ComPtr<IDXGIAdapter1> adapter)
	{
		mInstance = instance;
		mAdapter = adapter;
		InitFeatures();
		InitProperties();
		InitDeviceLimit();
		InitSparseProperties();
		InitMemoryProperties();
		InitQueueFamilyPropertiex();
	}

	void PhysicalDevice::GetFeatures(VkPhysicalDeviceFeatures* features) const
	{
		if (features)
		{
			*features = mFeatures;
		}
		return;
	}

	void PhysicalDevice::GetProperties(VkPhysicalDeviceProperties* properties) const
	{
		if (properties)
		{
			*properties = mProperties;
		}
	}

	void PhysicalDevice::GetFormatProperties(VkFormat format, VkFormatProperties* pFormatProperties)
	{
		if (pFormatProperties)
		{
			//*pFormatProperties = mvkVkFormatProperties(format);
			assert(false);
		}
		return;
	}

	void PhysicalDevice::GetQueueFamilyProperties(uint32_t* count, VkQueueFamilyProperties* properties) const
	{
		if (properties == nullptr)
		{
			*count = 1;
			return;
		}
		assert(*count == 1);
	}

	void PhysicalDevice::InitQueueFamilyPropertiex(void)
	{
		mQueueFamilyProperties = {};
		mQueueFamilyProperties.queueFlags = VK_QUEUE_GRAPHICS_BIT |
			VK_QUEUE_COMPUTE_BIT | VK_QUEUE_TRANSFER_BIT;
		mQueueFamilyProperties.queueCount = 8;
		if (mDesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
		{
			mQueueFamilyProperties.queueFlags = 0;
		}
	}

	void PhysicalDevice::GetMemoryProperties(VkPhysicalDeviceMemoryProperties* properties) const
	{
		if (properties)
		{
			*properties = mMemoryProperties;
		}
	}

	D3D12_HEAP_TYPE PhysicalDevice::GetHeapType(uint32_t index) const
	{
		assert(index < mMemoryProperties.memoryTypeCount);
		auto type = mMemoryProperties.memoryTypes[index].propertyFlags;
		if (type & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
		{
			return D3D12_HEAP_TYPE_DEFAULT;
		}
		else
		{
			return D3D12_HEAP_TYPE_UPLOAD;
		}
	}

	void PhysicalDevice::InitFeatures(void)
	{
		mFeatures = {};
		//	mFeatures.robustBufferAccess;
		//	mFeatures.fullDrawIndexUint32;
		//	mFeatures.imageCubeArray;
		//	mFeatures.independentBlend;
		//	mFeatures.geometryShader;
		//	mFeatures.tessellationShader;
		//	mFeatures.sampleRateShading;
		//	mFeatures.dualSrcBlend;
		//	mFeatures.logicOp;
		mFeatures.multiDrawIndirect = TRUE;
		mFeatures.drawIndirectFirstInstance = TRUE;
		//	mFeatures.depthClamp;
		//	mFeatures.depthBiasClamp;
		mFeatures.fillModeNonSolid = TRUE;
		//	mFeatures.depthBounds;
		//	mFeatures.wideLines;
		//	mFeatures.largePoints;
		//	mFeatures.alphaToOne;
		//	mFeatures.multiViewport;
		//	mFeatures.samplerAnisotropy;
		//	mFeatures.textureCompressionETC2;
		//	mFeatures.textureCompressionASTC_LDR;
		mFeatures.textureCompressionBC = TRUE;
		//	mFeatures.occlusionQueryPrecise;
		//	mFeatures.pipelineStatisticsQuery;
		//	mFeatures.vertexPipelineStoresAndAtomics;
		//	mFeatures.fragmentStoresAndAtomics;
		//	mFeatures.shaderTessellationAndGeometryPointSize;
		//	mFeatures.shaderImageGatherExtended;
		//	mFeatures.shaderStorageImageExtendedFormats;
		//	mFeatures.shaderStorageImageMultisample;
		//	mFeatures.shaderStorageImageReadWithoutFormat;
		//	mFeatures.shaderStorageImageWriteWithoutFormat;
		//	mFeatures.shaderUniformBufferArrayDynamicIndexing;
		//	mFeatures.shaderSampledImageArrayDynamicIndexing;
		//	mFeatures.shaderStorageBufferArrayDynamicIndexing;
		//	mFeatures.shaderStorageImageArrayDynamicIndexing;
		//	mFeatures.shaderClipDistance;
		//	mFeatures.shaderCullDistance;
		//	mFeatures.shaderFloat64;
		//	mFeatures.shaderInt64;
		//	mFeatures.shaderInt16;
		//	mFeatures.shaderResourceResidency;
		//	mFeatures.shaderResourceMinLod;
		//	mFeatures.sparseBinding;
		//	mFeatures.sparseResidencyBuffer;
		//	mFeatures.sparseResidencyImage2D;
		//	mFeatures.sparseResidencyImage3D;
		//	mFeatures.sparseResidency2Samples;
		//	mFeatures.sparseResidency4Samples;
		//	mFeatures.sparseResidency8Samples;
		//	mFeatures.sparseResidency16Samples;
		//	mFeatures.sparseResidencyAliased;
		//	mFeatures.variableMultisampleRate;
		//	mFeatures.inheritedQueries;
	}

	void PhysicalDevice::InitProperties(void)
	{
		/*
		uint32_t                            apiVersion;
		uint32_t                            driverVersion;
		uint32_t                            vendorID;
		uint32_t                            deviceID;
		VkPhysicalDeviceType                deviceType;
		char                                deviceName;
		uint8_t                             pipelineCacheUUID[16];
		VkPhysicalDeviceLimits              limits;
		VkPhysicalDeviceSparseProperties    sparseProperties;
		*/

		mProperties.apiVersion = VK_API_VERSION_1_1;
		mAdapter->GetDesc1(&mDesc);
		char device_name[VK_MAX_PHYSICAL_DEVICE_NAME_SIZE];
		wcstombs(device_name, mDesc.Description, VK_MAX_PHYSICAL_DEVICE_NAME_SIZE);
		std::memcpy(mProperties.deviceName, device_name, VK_MAX_PHYSICAL_DEVICE_NAME_SIZE);
		mProperties.deviceID = mDesc.DeviceId;
		mProperties.vendorID = mDesc.VendorId;
		mProperties.driverVersion = mDesc.Revision;
		if (mDesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
		{
			mProperties.deviceType = VK_PHYSICAL_DEVICE_TYPE_CPU;
		}
		else
		{
			mProperties.deviceType = VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;
		}
		static_assert(sizeof(mDesc.AdapterLuid) == 8, "Test Luid Size : 8");
		std::memcpy(mProperties.pipelineCacheUUID, &mDesc.AdapterLuid, sizeof(mDesc.AdapterLuid));
	}

	void PhysicalDevice::InitDeviceLimit(void)
	{
		VkPhysicalDeviceLimits& device_limit = mProperties.limits;
		//	device_limit.maxImageDimension1D;
		//	device_limit.maxImageDimension2D;
		//	device_limit.maxImageDimension3D;
		//	device_limit.maxImageDimensionCube;
		//	device_limit.maxImageArrayLayers;
		//	device_limit.maxTexelBufferElements;
		//	device_limit.maxUniformBufferRange;
		//	device_limit.maxStorageBufferRange;
		//	device_limit.maxPushConstantsSize;
		//	device_limit.maxMemoryAllocationCount;
		//	device_limit.maxSamplerAllocationCount;
		//	device_limit.bufferImageGranularity;
		//	device_limit.sparseAddressSpaceSize;
		//	device_limit.maxBoundDescriptorSets;
		//	device_limit.maxPerStageDescriptorSamplers;
		//	device_limit.maxPerStageDescriptorUniformBuffers;
		//	device_limit.maxPerStageDescriptorStorageBuffers;
		//	device_limit.maxPerStageDescriptorSampledImages;
		//	device_limit.maxPerStageDescriptorStorageImages;
		//	device_limit.maxPerStageDescriptorInputAttachments;
		//	device_limit.maxPerStageResources;
		//	device_limit.maxDescriptorSetSamplers;
		//	device_limit.maxDescriptorSetUniformBuffers;
		//	device_limit.maxDescriptorSetUniformBuffersDynamic;
		//	device_limit.maxDescriptorSetStorageBuffers;
		//	device_limit.maxDescriptorSetStorageBuffersDynamic;
		//	device_limit.maxDescriptorSetSampledImages;
		//	device_limit.maxDescriptorSetStorageImages;
		//	device_limit.maxDescriptorSetInputAttachments;
		//	device_limit.maxVertexInputAttributes;
		//	device_limit.maxVertexInputBindings;
		//	device_limit.maxVertexInputAttributeOffset;
		//	device_limit.maxVertexInputBindingStride;
		//	device_limit.maxVertexOutputComponents;
		//	device_limit.maxTessellationGenerationLevel;
		//	device_limit.maxTessellationPatchSize;
		//	device_limit.maxTessellationControlPerVertexInputComponents;
		//	device_limit.maxTessellationControlPerVertexOutputComponents;
		//	device_limit.maxTessellationControlPerPatchOutputComponents;
		//	device_limit.maxTessellationControlTotalOutputComponents;
		//	device_limit.maxTessellationEvaluationInputComponents;
		//	device_limit.maxTessellationEvaluationOutputComponents;
		//	device_limit.maxGeometryShaderInvocations;
		//	device_limit.maxGeometryInputComponents;
		//	device_limit.maxGeometryOutputComponents;
		//	device_limit.maxGeometryOutputVertices;
		//	device_limit.maxGeometryTotalOutputComponents;
		//	device_limit.maxFragmentInputComponents;
		//	device_limit.maxFragmentOutputAttachments;
		//	device_limit.maxFragmentDualSrcAttachments;
		//	device_limit.maxFragmentCombinedOutputResources;
		//	device_limit.maxComputeSharedMemorySize;
		//	device_limit.maxComputeWorkGroupCount[3];
		//	device_limit.maxComputeWorkGroupInvocations;
		//	device_limit.maxComputeWorkGroupSize[3];
		//	device_limit.subPixelPrecisionBits;
		//	device_limit.subTexelPrecisionBits;
		//	device_limit.mipmapPrecisionBits;
		device_limit.maxDrawIndexedIndexValue = UINT_MAX - 1;
		device_limit.maxDrawIndirectCount = 0;
		//	device_limit.maxSamplerLodBias;
		//	device_limit.maxSamplerAnisotropy;
		//	device_limit.maxViewports;
		//	device_limit.maxViewportDimensions[2];
		//	device_limit.viewportBoundsRange[2];
		//	device_limit.viewportSubPixelBits;
		//	device_limit.minMemoryMapAlignment;
		//	device_limit.minTexelBufferOffsetAlignment;
		//	device_limit.minUniformBufferOffsetAlignment;
		//	device_limit.minStorageBufferOffsetAlignment;
		//	device_limit.minTexelOffset;
		//	device_limit.maxTexelOffset;
		//	device_limit.minTexelGatherOffset;
		//	device_limit.maxTexelGatherOffset;
		//	device_limit.minInterpolationOffset;
		//	device_limit.maxInterpolationOffset;
		//	device_limit.subPixelInterpolationOffsetBits;
		//	device_limit.maxFramebufferWidth;
		//	device_limit.maxFramebufferHeight;
		//	device_limit.maxFramebufferLayers;
		//	device_limit.framebufferColorSampleCounts;
		//	device_limit.framebufferDepthSampleCounts;
		//	device_limit.framebufferStencilSampleCounts;
		//	device_limit.framebufferNoAttachmentsSampleCounts;
		//	device_limit.maxColorAttachments;
		//	device_limit.sampledImageColorSampleCounts;
		//	device_limit.sampledImageIntegerSampleCounts;
		//	device_limit.sampledImageDepthSampleCounts;
		//	device_limit.sampledImageStencilSampleCounts;
		//	device_limit.storageImageSampleCounts;
		//	device_limit.maxSampleMaskWords;
		//	device_limit.timestampComputeAndGraphics;
		//	device_limit.timestampPeriod;
		//	device_limit.maxClipDistances;
		//	device_limit.maxCullDistances;
		//	device_limit.maxCombinedClipAndCullDistances;
		//	device_limit.discreteQueuePriorities;
		//	device_limit.pointSizeRange[2];
		//	device_limit.lineWidthRange[2];
		//	device_limit.pointSizeGranularity;
		//	device_limit.lineWidthGranularity;
		//	device_limit.strictLines;
		//	device_limit.standardSampleLocations;
		//	device_limit.optimalBufferCopyOffsetAlignment;
		//	device_limit.optimalBufferCopyRowPitchAlignment;
		//	device_limit.nonCoherentAtomSize;

	}

	void PhysicalDevice::InitSparseProperties(void)
	{
		VkPhysicalDeviceSparseProperties& sparse_properties = mProperties.sparseProperties;
		//	sparse_properties.residencyStandard2DBlockShape;
		//	sparse_properties.residencyStandard2DMultisampleBlockShape;
		//	sparse_properties.residencyStandard3DBlockShape;
		//	sparse_properties.residencyAlignedMipSize;
		//	sparse_properties.residencyNonResidentStrict;
	}

	void PhysicalDevice::InitMemoryProperties(void)
	{
		mMemoryProperties = {};

		uint32_t heap_count = 0;
		if (mDesc.DedicatedVideoMemory != 0)
		{
			mMemoryProperties.memoryHeaps[heap_count].flags = VK_MEMORY_HEAP_DEVICE_LOCAL_BIT;
			mMemoryProperties.memoryHeaps[heap_count].size = mDesc.DedicatedVideoMemory;
			++heap_count;
		}

		if (mDesc.SharedSystemMemory != 0)
		{
			mMemoryProperties.memoryHeaps[heap_count].flags = VK_MEMORY_HEAP_MULTI_INSTANCE_BIT;	//host ?
			mMemoryProperties.memoryHeaps[heap_count].size = mDesc.SharedSystemMemory;
			++heap_count;
		}
		mMemoryProperties.memoryHeapCount = heap_count;

		uint32_t type_count = 0;
		for (uint32_t i = 0; i < heap_count; ++i)
		{
			mMemoryProperties.memoryTypes[i].heapIndex = i;
			VkMemoryHeapFlags flags = mMemoryProperties.memoryHeaps[i].flags;
			if (flags == VK_MEMORY_HEAP_DEVICE_LOCAL_BIT)
			{
				mMemoryProperties.memoryTypes[i].propertyFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
				++type_count;
			}

			if (flags == VK_MEMORY_HEAP_MULTI_INSTANCE_BIT)
			{
				mMemoryProperties.memoryTypes[i].propertyFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
					VK_MEMORY_PROPERTY_HOST_COHERENT_BIT |
					VK_MEMORY_PROPERTY_HOST_CACHED_BIT;
				++type_count;
			}
		}
		mMemoryProperties.memoryTypeCount = type_count;
	}
}