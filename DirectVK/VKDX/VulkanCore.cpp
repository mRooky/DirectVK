#include "VKInterface.h"
#include "VKCmdInterface.h"
#include <cassert>

VkResult VKAPI_CALL vkCreateInstance(
	const VkInstanceCreateInfo*                 pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkInstance*                                 pInstance)
{
	VkInstance_T* instance = new VkInstance_T;
	VkResult result = instance->Create(pCreateInfo);
	*pInstance = instance;
	return result;
}

void VKAPI_CALL vkDestroyInstance(
	VkInstance                                  instance,
	const VkAllocationCallbacks*                pAllocator)
{
	delete instance;
}

VkResult VKAPI_CALL vkEnumeratePhysicalDevices(
	VkInstance                                  instance,
	uint32_t*                                   pPhysicalDeviceCount,
	VkPhysicalDevice*                           pPhysicalDevices)
{
	VkResult result = VK_INCOMPLETE;
	if (instance)
	{
		result = instance->GetPhysicalDevices(pPhysicalDeviceCount, pPhysicalDevices);
	}
	return result;
}

void VKAPI_CALL vkGetPhysicalDeviceFeatures(
	VkPhysicalDevice                            physicalDevice,
	VkPhysicalDeviceFeatures*                   pFeatures)
{
	if (physicalDevice)
	{
		physicalDevice->GetFeatures(pFeatures);
	}
}

void VKAPI_CALL vkGetPhysicalDeviceFormatProperties(
	VkPhysicalDevice                            physicalDevice,
	VkFormat                                    format,
	VkFormatProperties*                         pFormatProperties)
{
	if (physicalDevice)
	{
		physicalDevice->GetFormatProperties(format, pFormatProperties);
	}
}

VkResult VKAPI_CALL vkGetPhysicalDeviceImageFormatProperties(
	VkPhysicalDevice                            physicalDevice,
	VkFormat                                    format,
	VkImageType                                 type,
	VkImageTiling                               tiling,
	VkImageUsageFlags                           usage,
	VkImageCreateFlags                          flags,
	VkImageFormatProperties*                    pImageFormatProperties);

void VKAPI_CALL vkGetPhysicalDeviceProperties(
	VkPhysicalDevice                            physicalDevice,
	VkPhysicalDeviceProperties*                 pProperties)
{
	if (physicalDevice)
	{
		physicalDevice->GetProperties(pProperties);
	}
}

void VKAPI_CALL vkGetPhysicalDeviceQueueFamilyProperties(
	VkPhysicalDevice                            physicalDevice,
	uint32_t*                                   pQueueFamilyPropertyCount,
	VkQueueFamilyProperties*                    pQueueFamilyProperties)
{
	if (physicalDevice)
	{
		physicalDevice->GetQueueFamilyProperties(pQueueFamilyPropertyCount, pQueueFamilyProperties);
	}
}

void VKAPI_CALL vkGetPhysicalDeviceMemoryProperties(
	VkPhysicalDevice                            physicalDevice,
	VkPhysicalDeviceMemoryProperties*           pMemoryProperties)
{
	if (physicalDevice)
	{
		physicalDevice->GetMemoryProperties(pMemoryProperties);
	}
}

PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(
	VkInstance                                  instance,
	const char*                                 pName);

PFN_vkVoidFunction VKAPI_CALL vkGetDeviceProcAddr(
	VkDevice                                    device,
	const char*                                 pName);

VkResult VKAPI_CALL vkCreateDevice(
	VkPhysicalDevice                            physicalDevice,
	const VkDeviceCreateInfo*                   pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkDevice*                                   pDevice)
{
	VkResult result = VK_INCOMPLETE;
	if (physicalDevice)
	{
		VkDevice_T* device = new VkDevice_T;
		result = device->Create(physicalDevice, pCreateInfo);
		*pDevice = device;
	}
	return result;
}

void VKAPI_CALL vkDestroyDevice(
	VkDevice                                    device,
	const VkAllocationCallbacks*                pAllocator)
{
	delete device;
}

VkResult VKAPI_CALL vkEnumerateInstanceExtensionProperties(
	const char*                                 pLayerName,
	uint32_t*                                   pPropertyCount,
	VkExtensionProperties*                      pProperties);

VkResult VKAPI_CALL vkEnumerateDeviceExtensionProperties(
	VkPhysicalDevice                            physicalDevice,
	const char*                                 pLayerName,
	uint32_t*                                   pPropertyCount,
	VkExtensionProperties*                      pProperties);

VkResult VKAPI_CALL vkEnumerateInstanceLayerProperties(
	uint32_t*                                   pPropertyCount,
	VkLayerProperties*                          pProperties);

VkResult VKAPI_CALL vkEnumerateDeviceLayerProperties(
	VkPhysicalDevice                            physicalDevice,
	uint32_t*                                   pPropertyCount,
	VkLayerProperties*                          pProperties);

void VKAPI_CALL vkGetDeviceQueue(
	VkDevice                                    device,
	uint32_t                                    queueFamilyIndex,
	uint32_t                                    queueIndex,
	VkQueue*                                    pQueue)
{
	if (device)
	{
		device->GetDeviceQueue(queueFamilyIndex, queueIndex, pQueue);
	}
}

VkResult VKAPI_CALL vkQueueSubmit(
	VkQueue                                     queue,
	uint32_t                                    submitCount,
	const VkSubmitInfo*                         pSubmits,
	VkFence                                     fence)
{
	VkResult result = VK_INCOMPLETE;
	if (queue != VK_NULL_HANDLE)
	{
		result = queue->Submit(submitCount, pSubmits, fence);
	}
	return result;
}

VkResult VKAPI_CALL vkQueueWaitIdle(
	VkQueue                                     queue);

VkResult VKAPI_CALL vkDeviceWaitIdle(
	VkDevice                                    device);

VkResult VKAPI_CALL vkAllocateMemory(
	VkDevice                                    device,
	const VkMemoryAllocateInfo*                 pAllocateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkDeviceMemory*                             pMemory)
{
	VkDeviceMemory_T* memory = new VkDeviceMemory_T;
	VkResult result = memory->Allocate(device, pAllocateInfo);
	*pMemory = memory;
	return result;
}

void VKAPI_CALL vkFreeMemory(
	VkDevice                                    device,
	VkDeviceMemory                              memory,
	const VkAllocationCallbacks*                pAllocator)
{
	delete memory;
}

VkResult VKAPI_CALL vkMapMemory(
	VkDevice                                    device,
	VkDeviceMemory                              memory,
	VkDeviceSize                                offset,
	VkDeviceSize                                size,
	VkMemoryMapFlags                            flags,
	void**                                      ppData)
{
	VkResult result = VK_INCOMPLETE;
	if (memory != VK_NULL_HANDLE)
	{
		void* ptr = memory->Map(offset, size);
		assert(ptr != nullptr);
		*ppData = ptr;
		result = (ptr != nullptr) ? VK_SUCCESS : VK_INCOMPLETE;
	}
	return result;
}

void VKAPI_CALL vkUnmapMemory(
	VkDevice                                    device,
	VkDeviceMemory                              memory)
{
	if (memory)
	{
		memory->Unmap();
	}
}

VkResult VKAPI_CALL vkFlushMappedMemoryRanges(
	VkDevice                                    device,
	uint32_t                                    memoryRangeCount,
	const VkMappedMemoryRange*                  pMemoryRanges);

VkResult VKAPI_CALL vkInvalidateMappedMemoryRanges(
	VkDevice                                    device,
	uint32_t                                    memoryRangeCount,
	const VkMappedMemoryRange*                  pMemoryRanges);

void VKAPI_CALL vkGetDeviceMemoryCommitment(
	VkDevice                                    device,
	VkDeviceMemory                              memory,
	VkDeviceSize*                               pCommittedMemoryInBytes);

VkResult VKAPI_CALL vkBindBufferMemory(
	VkDevice                                    device,
	VkBuffer                                    buffer,
	VkDeviceMemory                              memory,
	VkDeviceSize                                memoryOffset)
{
	VkResult result = VK_INCOMPLETE;
	if (buffer != VK_NULL_HANDLE)
	{
		result = buffer->BindDeviceMemory(memory, memoryOffset);
	}
	return result;
}

VkResult VKAPI_CALL vkBindImageMemory(
	VkDevice                                    device,
	VkImage                                     image,
	VkDeviceMemory                              memory,
	VkDeviceSize                                memoryOffset)
{
	VkResult result = VK_INCOMPLETE;
	if (image != VK_NULL_HANDLE)
	{
		result = image->BindDeviceMemory(memory, memoryOffset);
	}
	return result;
}

void VKAPI_CALL vkGetBufferMemoryRequirements(
	VkDevice                                    device,
	VkBuffer                                    buffer,
	VkMemoryRequirements*                       pMemoryRequirements)
{
	if (buffer != VK_NULL_HANDLE)
	{
		buffer->GetMemoryRequirements(pMemoryRequirements);
	}
}

void VKAPI_CALL vkGetImageMemoryRequirements(
	VkDevice                                    device,
	VkImage                                     image,
	VkMemoryRequirements*                       pMemoryRequirements)
{
	if (image != VK_NULL_HANDLE)
	{
		image->GetMemoryRequirements(pMemoryRequirements);
	}
}

void VKAPI_CALL vkGetImageSparseMemoryRequirements(
	VkDevice                                    device,
	VkImage                                     image,
	uint32_t*                                   pSparseMemoryRequirementCount,
	VkSparseImageMemoryRequirements*            pSparseMemoryRequirements);

void VKAPI_CALL vkGetPhysicalDeviceSparseImageFormatProperties(
	VkPhysicalDevice                            physicalDevice,
	VkFormat                                    format,
	VkImageType                                 type,
	VkSampleCountFlagBits                       samples,
	VkImageUsageFlags                           usage,
	VkImageTiling                               tiling,
	uint32_t*                                   pPropertyCount,
	VkSparseImageFormatProperties*              pProperties);

VkResult VKAPI_CALL vkQueueBindSparse(
	VkQueue                                     queue,
	uint32_t                                    bindInfoCount,
	const VkBindSparseInfo*                     pBindInfo,
	VkFence                                     fence);

VkResult VKAPI_CALL vkCreateFence(
	VkDevice                                    device,
	const VkFenceCreateInfo*                    pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkFence*                                    pFence)
{
	VkFence_T* fence = new VkFence_T;
	VkResult result = fence->Create(device, pCreateInfo);
	*pFence = fence;
	return result;
}

void VKAPI_CALL vkDestroyFence(
	VkDevice                                    device,
	VkFence                                     fence,
	const VkAllocationCallbacks*                pAllocator)
{
	delete fence;
}

VkResult VKAPI_CALL vkResetFences(
	VkDevice                                    device,
	uint32_t                                    fenceCount,
	const VkFence*                              pFences)
{
	for (uint32_t i = 0; i < fenceCount; ++i)
	{
		VkFence fence = pFences[i];
		fence->Reset();
	}
	return VK_SUCCESS;
}

VkResult VKAPI_CALL vkGetFenceStatus(
	VkDevice                                    device,
	VkFence                                     fence)
{
	VkResult result = VK_INCOMPLETE;
	if (fence)
	{
		result = fence->GetStatus();
	}
	return result;
}

VkResult VKAPI_CALL vkWaitForFences(
	VkDevice                                    device,
	uint32_t                                    fenceCount,
	const VkFence*                              pFences,
	VkBool32                                    waitAll,
	uint64_t                                    timeout)
{
	for (uint32_t i = 0; i < fenceCount; ++i)
	{
		VkFence fence = pFences[i];
		VkResult result = fence->WaitFor(timeout);
		if (result == VK_TIMEOUT)
		{
			return VK_TIMEOUT;
		}
		else
		{
			if (waitAll != VK_TRUE)
			{
				return VK_SUCCESS;
			}
		}
	}
	return VK_SUCCESS;
}

VkResult VKAPI_CALL vkCreateSemaphore(
	VkDevice                                    device,
	const VkSemaphoreCreateInfo*                pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkSemaphore*                                pSemaphore)
{
	VkSemaphore_T* semaphore = new VkSemaphore_T;
	VkResult result = semaphore->Create(device, pCreateInfo);
	*pSemaphore = semaphore;
	return result;
}

void VKAPI_CALL vkDestroySemaphore(
	VkDevice                                    device,
	VkSemaphore                                 semaphore,
	const VkAllocationCallbacks*                pAllocator)
{
	delete semaphore;
}

VkResult VKAPI_CALL vkCreateEvent(
	VkDevice                                    device,
	const VkEventCreateInfo*                    pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkEvent*                                    pEvent)
{
	return VK_INCOMPLETE;
}

void VKAPI_CALL vkDestroyEvent(
	VkDevice                                    device,
	VkEvent                                     event,
	const VkAllocationCallbacks*                pAllocator)
{
	//unimplement
}

VkResult VKAPI_CALL vkGetEventStatus(
	VkDevice                                    device,
	VkEvent                                     event)
{
	return VK_INCOMPLETE;
}

VkResult VKAPI_CALL vkSetEvent(
	VkDevice                                    device,
	VkEvent                                     event)
{
	return VK_INCOMPLETE;
}

VkResult VKAPI_CALL vkResetEvent(
	VkDevice                                    device,
	VkEvent                                     event)
{
	return VK_INCOMPLETE;
}

VkResult VKAPI_CALL vkCreateQueryPool(
	VkDevice                                    device,
	const VkQueryPoolCreateInfo*                pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkQueryPool*                                pQueryPool)
{
	VkQueryPool_T* pool = new  VkQueryPool_T;
	VkResult result = pool->Create(device, pCreateInfo);
	*pQueryPool = pool;
	return result;
}

void VKAPI_CALL vkDestroyQueryPool(
	VkDevice                                    device,
	VkQueryPool                                 queryPool,
	const VkAllocationCallbacks*                pAllocator)
{
	delete queryPool;
}

VkResult VKAPI_CALL vkGetQueryPoolResults(
	VkDevice                                    device,
	VkQueryPool                                 queryPool,
	uint32_t                                    firstQuery,
	uint32_t                                    queryCount,
	size_t                                      dataSize,
	void*                                       pData,
	VkDeviceSize                                stride,
	VkQueryResultFlags                          flags);

VkResult VKAPI_CALL vkCreateBuffer(
	VkDevice                                    device,
	const VkBufferCreateInfo*                   pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkBuffer*                                   pBuffer)
{
	VkResult result = VK_INCOMPLETE;
	if (device != VK_NULL_HANDLE)
	{
		VK::Buffer* buffer = device->CreateBuffer(pCreateInfo);
		result = buffer->GetResult();
		*pBuffer = static_cast<VkBuffer_T*>(buffer);
	}
	return result;
}

void VKAPI_CALL vkDestroyBuffer(
	VkDevice                                    device,
	VkBuffer                                    buffer,
	const VkAllocationCallbacks*                pAllocator)
{
	if (device != VK_NULL_HANDLE)
	{
		device->RemoveResource(buffer);
	}
}

VkResult VKAPI_CALL vkCreateBufferView(
	VkDevice                                    device,
	const VkBufferViewCreateInfo*               pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkBufferView*                               pView)
{
	VkBufferView_T* view = new VkBufferView_T;
	VkResult result = view->Create(device, pCreateInfo);
	*pView = view;
	return result;
}

void VKAPI_CALL vkDestroyBufferView(
	VkDevice                                    device,
	VkBufferView                                bufferView,
	const VkAllocationCallbacks*                pAllocator)
{
	delete bufferView;
}

VkResult VKAPI_CALL vkCreateImage(
	VkDevice                                    device,
	const VkImageCreateInfo*                    pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkImage*                                    pImage)
{
	VkResult result = VK_INCOMPLETE;
	if (device != VK_NULL_HANDLE)
	{
		VK::Image* image = device->CreateImage(pCreateInfo);
		result = image->GetResult();
		*pImage = static_cast<VkImage_T*>(image);
	}
	return result;
}

void VKAPI_CALL vkDestroyImage(
	VkDevice                                    device,
	VkImage                                     image,
	const VkAllocationCallbacks*                pAllocator)
{
	if (device != VK_NULL_HANDLE)
	{
		device->RemoveResource(image);
	}
}

void VKAPI_CALL vkGetImageSubresourceLayout(
	VkDevice                                    device,
	VkImage                                     image,
	const VkImageSubresource*                   pSubresource,
	VkSubresourceLayout*                        pLayout);

VkResult VKAPI_CALL vkCreateImageView(
	VkDevice                                    device,
	const VkImageViewCreateInfo*                pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkImageView*                                pView)
{
	VkImageView_T* view = new VkImageView_T;
	VkResult result = view->Create(device, pCreateInfo);
	*pView = view;
	return result;
}

void VKAPI_CALL vkDestroyImageView(
	VkDevice                                    device,
	VkImageView                                 imageView,
	const VkAllocationCallbacks*                pAllocator)
{
	delete imageView;
}

VkResult VKAPI_CALL vkCreateShaderModule(
	VkDevice                                    device,
	const VkShaderModuleCreateInfo*             pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkShaderModule*                             pShaderModule)
{
	VkShaderModule_T* shader = new VkShaderModule_T;
	VkResult result = shader->Create(device, pCreateInfo);
	*pShaderModule = shader;
	return result;
}

void VKAPI_CALL vkDestroyShaderModule(
	VkDevice                                    device,
	VkShaderModule                              shaderModule,
	const VkAllocationCallbacks*                pAllocator)
{
	delete shaderModule;
}

VkResult VKAPI_CALL vkCreatePipelineCache(
	VkDevice                                    device,
	const VkPipelineCacheCreateInfo*            pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkPipelineCache*                            pPipelineCache)
{
	VkPipelineCache_T* cache = new VkPipelineCache_T;
	VkResult result = cache->Create(device, pCreateInfo);
	*pPipelineCache = cache;
	return result;
}

void VKAPI_CALL vkDestroyPipelineCache(
	VkDevice                                    device,
	VkPipelineCache                             pipelineCache,
	const VkAllocationCallbacks*                pAllocator)
{
	delete pipelineCache;
}

VkResult VKAPI_CALL vkGetPipelineCacheData(
	VkDevice                                    device,
	VkPipelineCache                             pipelineCache,
	size_t*                                     pDataSize,
	void*                                       pData)
{
	if (pipelineCache)
	{
		pipelineCache->GetCacheData(pDataSize, pData);
	}
	return VK_SUCCESS;
}

VkResult VKAPI_CALL vkMergePipelineCaches(
	VkDevice                                    device,
	VkPipelineCache                             dstCache,
	uint32_t                                    srcCacheCount,
	const VkPipelineCache*                      pSrcCaches);

VkResult VKAPI_CALL vkCreateGraphicsPipelines(
	VkDevice                                    device,
	VkPipelineCache                             pipelineCache,
	uint32_t                                    createInfoCount,
	const VkGraphicsPipelineCreateInfo*         pCreateInfos,
	const VkAllocationCallbacks*                pAllocator,
	VkPipeline*                                 pPipelines)
{
	assert(createInfoCount == 1);
	VkPipeline_T * pipeline = new VkPipeline_T;
	VkResult result = pipeline->Create(device, pipelineCache, pCreateInfos);
	*pPipelines = pipeline;
	return result;
}

VkResult VKAPI_CALL vkCreateComputePipelines(
	VkDevice                                    device,
	VkPipelineCache                             pipelineCache,
	uint32_t                                    createInfoCount,
	const VkComputePipelineCreateInfo*          pCreateInfos,
	const VkAllocationCallbacks*                pAllocator,
	VkPipeline*                                 pPipelines)
{
	VkPipeline_T* pipeline = new VkPipeline_T;
	assert(createInfoCount == 1);
	VkResult result = pipeline->Create(device, pipelineCache, pCreateInfos);
	*pPipelines = pipeline;
	return result;
}

void VKAPI_CALL vkDestroyPipeline(
	VkDevice                                    device,
	VkPipeline                                  pipeline,
	const VkAllocationCallbacks*                pAllocator)
{
	delete pipeline;
}

VkResult VKAPI_CALL vkCreatePipelineLayout(
	VkDevice                                    device,
	const VkPipelineLayoutCreateInfo*           pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkPipelineLayout*                           pPipelineLayout)
{
	VkPipelineLayout_T * layout = new VkPipelineLayout_T;
	VkResult result = layout->Create(device, pCreateInfo);
	*pPipelineLayout = layout;
	return result;
}

void VKAPI_CALL vkDestroyPipelineLayout(
	VkDevice                                    device,
	VkPipelineLayout                            pipelineLayout,
	const VkAllocationCallbacks*                pAllocator)
{
	delete pipelineLayout;
}

VkResult VKAPI_CALL vkCreateSampler(
	VkDevice                                    device,
	const VkSamplerCreateInfo*                  pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkSampler*                                  pSampler)
{
	VkSampler_T * sampler = new VkSampler_T;
	VkResult result = sampler->Create(device, pCreateInfo);
	*pSampler = sampler;
	return result;
}

void VKAPI_CALL vkDestroySampler(
	VkDevice                                    device,
	VkSampler                                   sampler,
	const VkAllocationCallbacks*                pAllocator)
{
	delete sampler;
}

VkResult VKAPI_CALL vkCreateDescriptorSetLayout(
	VkDevice                                    device,
	const VkDescriptorSetLayoutCreateInfo*      pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkDescriptorSetLayout*                      pSetLayout)
{
	VkDescriptorSetLayout_T * layout = new VkDescriptorSetLayout_T;
	VkResult result = layout->Create(device, pCreateInfo);
	*pSetLayout = layout;
	return result;
}


void VKAPI_CALL vkDestroyDescriptorSetLayout(
	VkDevice                                    device,
	VkDescriptorSetLayout                       descriptorSetLayout,
	const VkAllocationCallbacks*                pAllocator)
{
	delete descriptorSetLayout;
}

VkResult VKAPI_CALL vkCreateDescriptorPool(
	VkDevice                                    device,
	const VkDescriptorPoolCreateInfo*           pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkDescriptorPool*                           pDescriptorPool)
{
	VkDescriptorPool_T * pool = new VkDescriptorPool_T;
	VkResult result = pool->Create(device, pCreateInfo);
	*pDescriptorPool = pool;
	return result;
}

void VKAPI_CALL vkDestroyDescriptorPool(
	VkDevice                                    device,
	VkDescriptorPool                            descriptorPool,
	const VkAllocationCallbacks*                pAllocator)
{
	delete descriptorPool;
}

VkResult VKAPI_CALL vkResetDescriptorPool(
	VkDevice                                    device,
	VkDescriptorPool                            descriptorPool,
	VkDescriptorPoolResetFlags                  flags);

VkResult VKAPI_CALL vkAllocateDescriptorSets(
	VkDevice                                    device,
	const VkDescriptorSetAllocateInfo*          pAllocateInfo,
	VkDescriptorSet*                            pDescriptorSets)
{
	VkResult result = VK_INCOMPLETE;
	if (pAllocateInfo != nullptr)
	{
		VK::DescriptorPool* pool = pAllocateInfo->descriptorPool;
		VK::DescriptorSet* set = pool->Allocate(pAllocateInfo);
		*pDescriptorSets = static_cast<VkDescriptorSet_T*>(set);
		result = VK_SUCCESS;
	}
	return result;
}

VkResult VKAPI_CALL vkFreeDescriptorSets(
	VkDevice                                    device,
	VkDescriptorPool                            descriptorPool,
	uint32_t                                    descriptorSetCount,
	const VkDescriptorSet*                      pDescriptorSets)
{
	if (descriptorPool != VK_NULL_HANDLE)
	{
		for (uint32_t i = 0; i < descriptorSetCount; ++i)
		{
			VkDescriptorSet set = pDescriptorSets[i];
			descriptorPool->RemoveSet(set);
		}
	}
	return VK_SUCCESS;
}

void VKAPI_CALL vkUpdateDescriptorSets(
	VkDevice                                    device,
	uint32_t                                    descriptorWriteCount,
	const VkWriteDescriptorSet*                 pDescriptorWrites,
	uint32_t                                    descriptorCopyCount,
	const VkCopyDescriptorSet*                  pDescriptorCopies);

VkResult VKAPI_CALL vkCreateFramebuffer(
	VkDevice                                    device,
	const VkFramebufferCreateInfo*              pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkFramebuffer*                              pFramebuffer)
{
	VkFramebuffer_T * frame = new VkFramebuffer_T;
	VkResult result = frame->Create(device, pCreateInfo);
	*pFramebuffer = frame;
	return result;
}

void VKAPI_CALL vkDestroyFramebuffer(
	VkDevice                                    device,
	VkFramebuffer                               framebuffer,
	const VkAllocationCallbacks*                pAllocator)
{
	delete framebuffer;
}

VkResult VKAPI_CALL vkCreateRenderPass(
	VkDevice                                    device,
	const VkRenderPassCreateInfo*               pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkRenderPass*                               pRenderPass)
{
	VkRenderPass_T * pass = new VkRenderPass_T;
	VkResult result = pass->Create(device, pCreateInfo);
	*pRenderPass = pass;
	return result;
}

void VKAPI_CALL vkDestroyRenderPass(
	VkDevice                                    device,
	VkRenderPass                                renderPass,
	const VkAllocationCallbacks*                pAllocator)
{
	delete renderPass;
}

void VKAPI_CALL vkGetRenderAreaGranularity(
	VkDevice                                    device,
	VkRenderPass                                renderPass,
	VkExtent2D*                                 pGranularity);

VkResult VKAPI_CALL vkCreateCommandPool(
	VkDevice                                    device,
	const VkCommandPoolCreateInfo*              pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkCommandPool*                              pCommandPool)
{
	VkCommandPool_T * pool = new VkCommandPool_T;
	VkResult result = pool->Create(device, pCreateInfo);
	*pCommandPool = pool;
	return result;
}

void VKAPI_CALL vkDestroyCommandPool(
	VkDevice                                    device,
	VkCommandPool                               commandPool,
	const VkAllocationCallbacks*                pAllocator)
{
	delete commandPool;
}

VkResult VKAPI_CALL vkResetCommandPool(
	VkDevice                                    device,
	VkCommandPool                               commandPool,
	VkCommandPoolResetFlags                     flags)
{
	VkResult result = VK_INCOMPLETE;
	if (commandPool != VK_NULL_HANDLE)
	{
		result = commandPool->Reset();
	}
	return result;
}

VkResult VKAPI_CALL vkAllocateCommandBuffers(
	VkDevice                                    device,
	const VkCommandBufferAllocateInfo*          pAllocateInfo,
	VkCommandBuffer*                            pCommandBuffers)
{
	VK::CommandPool* pool = pAllocateInfo->commandPool;
	VK::CommandBuffer * command = pool->Allocate(pAllocateInfo);
	VkResult result = command->Allocate(device, pAllocateInfo);
	*pCommandBuffers = static_cast<VkCommandBuffer>(command);
	return result;
}

void VKAPI_CALL vkFreeCommandBuffers(
	VkDevice                                    device,
	VkCommandPool                               commandPool,
	uint32_t                                    commandBufferCount,
	const VkCommandBuffer*                      pCommandBuffers)
{
	if (commandPool != VK_NULL_HANDLE)
	{
		for (uint32_t i = 0; i < commandBufferCount; ++i)
		{
			VK::CommandBuffer* command = pCommandBuffers[i];
			commandPool->RemoveCommandBuffer(command);
		}
	}
}

VkResult VKAPI_CALL vkBeginCommandBuffer(
	VkCommandBuffer                             commandBuffer,
	const VkCommandBufferBeginInfo*             pBeginInfo)
{
	VkResult result = VK_INCOMPLETE;
	if (commandBuffer != VK_NULL_HANDLE)
	{
		result = commandBuffer->Begin(pBeginInfo);
	}
	return result;
}

VkResult VKAPI_CALL vkEndCommandBuffer(
	VkCommandBuffer                             commandBuffer)
{
	VkResult result = VK_INCOMPLETE;
	if (commandBuffer != VK_NULL_HANDLE)
	{
		result = commandBuffer->End();
	}
	return result;
}

VkResult VKAPI_CALL vkResetCommandBuffer(
	VkCommandBuffer                             commandBuffer,
	VkCommandBufferResetFlags                   flags)
{
	VkResult result = VK_INCOMPLETE;
	if (commandBuffer != VK_NULL_HANDLE)
	{
		result = commandBuffer->Reset(flags);
	}
	return result;
}

void VKAPI_CALL vkCmdBindPipeline(
	VkCommandBuffer                             commandBuffer,
	VkPipelineBindPoint                         pipelineBindPoint,
	VkPipeline                                  pipeline)
{
	if (commandBuffer != VK_NULL_HANDLE)
	{
		VK::CmdBindPipeline* command = new VK::CmdBindPipeline;
		command->SetContent(pipelineBindPoint, pipeline);
		commandBuffer->AppendCommand(command);
	}
}

void VKAPI_CALL vkCmdSetViewport(
	VkCommandBuffer                             commandBuffer,
	uint32_t                                    firstViewport,
	uint32_t                                    viewportCount,
	const VkViewport*                           pViewports)
{
	if (commandBuffer != VK_NULL_HANDLE)
	{
		VK::CmdSetViewport* command = new VK::CmdSetViewport;
		command->SetContent(firstViewport, viewportCount, pViewports);
		commandBuffer->AppendCommand(command);
	}
}

void VKAPI_CALL vkCmdSetScissor(
	VkCommandBuffer                             commandBuffer,
	uint32_t                                    firstScissor,
	uint32_t                                    scissorCount,
	const VkRect2D*                             pScissors)
{
	if (commandBuffer != VK_NULL_HANDLE)
	{
		VK::CmdSetScissor* command = new VK::CmdSetScissor;
		command->SetContent(firstScissor, scissorCount, pScissors);
		commandBuffer->AppendCommand(command);
	}
}

void VKAPI_CALL vkCmdSetLineWidth(
	VkCommandBuffer                             commandBuffer,
	float                                       lineWidth);

void VKAPI_CALL vkCmdSetDepthBias(
	VkCommandBuffer                             commandBuffer,
	float                                       depthBiasConstantFactor,
	float                                       depthBiasClamp,
	float                                       depthBiasSlopeFactor);

void VKAPI_CALL vkCmdSetBlendConstants(
	VkCommandBuffer                             commandBuffer,
	const float                                 blendConstants[4]);

void VKAPI_CALL vkCmdSetDepthBounds(
	VkCommandBuffer                             commandBuffer,
	float                                       minDepthBounds,
	float                                       maxDepthBounds);

void VKAPI_CALL vkCmdSetStencilCompareMask(
	VkCommandBuffer                             commandBuffer,
	VkStencilFaceFlags                          faceMask,
	uint32_t                                    compareMask);

void VKAPI_CALL vkCmdSetStencilWriteMask(
	VkCommandBuffer                             commandBuffer,
	VkStencilFaceFlags                          faceMask,
	uint32_t                                    writeMask);

void VKAPI_CALL vkCmdSetStencilReference(
	VkCommandBuffer                             commandBuffer,
	VkStencilFaceFlags                          faceMask,
	uint32_t                                    reference);

void VKAPI_CALL vkCmdBindDescriptorSets(
	VkCommandBuffer                             commandBuffer,
	VkPipelineBindPoint                         pipelineBindPoint,
	VkPipelineLayout                            layout,
	uint32_t                                    firstSet,
	uint32_t                                    descriptorSetCount,
	const VkDescriptorSet*                      pDescriptorSets,
	uint32_t                                    dynamicOffsetCount,
	const uint32_t*                             pDynamicOffsets)
{
	if (commandBuffer != VK_NULL_HANDLE)
	{
		VK::CmdBindDescriptorSets* command = new VK::CmdBindDescriptorSets;
		command->SetContent(pipelineBindPoint, layout, firstSet, descriptorSetCount,
			pDescriptorSets, dynamicOffsetCount, pDynamicOffsets);
		commandBuffer->AppendCommand(command);
	}
}

void VKAPI_CALL vkCmdBindIndexBuffer(
	VkCommandBuffer                             commandBuffer,
	VkBuffer                                    buffer,
	VkDeviceSize                                offset,
	VkIndexType                                 indexType)
{
	if (commandBuffer != VK_NULL_HANDLE)
	{
		VK::CmdBindIndexBuffer* command = new VK::CmdBindIndexBuffer;
		command->SetContent(buffer, offset, indexType);
		commandBuffer->AppendCommand(command);
	}
}

void VKAPI_CALL vkCmdBindVertexBuffers(
	VkCommandBuffer                             commandBuffer,
	uint32_t                                    firstBinding,
	uint32_t                                    bindingCount,
	const VkBuffer*                             pBuffers,
	const VkDeviceSize*                         pOffsets)
{
	if (commandBuffer != VK_NULL_HANDLE)
	{
		VK::CmdBindVertexBuffers* command = new VK::CmdBindVertexBuffers;
		command->SetContent(firstBinding, bindingCount, pBuffers, pOffsets);
		commandBuffer->AppendCommand(command);
	}
}

void VKAPI_CALL vkCmdDraw(
	VkCommandBuffer                             commandBuffer,
	uint32_t                                    vertexCount,
	uint32_t                                    instanceCount,
	uint32_t                                    firstVertex,
	uint32_t                                    firstInstance)
{
	if (commandBuffer != VK_NULL_HANDLE)
	{
		VK::CmdDraw* command = new VK::CmdDraw;
		command->SetContent(vertexCount, instanceCount, firstVertex, firstInstance);
		commandBuffer->AppendCommand(command);
	}
}

void VKAPI_CALL vkCmdDrawIndexed(
	VkCommandBuffer                             commandBuffer,
	uint32_t                                    indexCount,
	uint32_t                                    instanceCount,
	uint32_t                                    firstIndex,
	int32_t                                     vertexOffset,
	uint32_t                                    firstInstance)
{
	if (commandBuffer != VK_NULL_HANDLE)
	{
		VK::CmdDrawIndexed* command = new VK::CmdDrawIndexed;
		command->SetContent(indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
		commandBuffer->AppendCommand(command);
	}
}

void VKAPI_CALL vkCmdDrawIndirect(
	VkCommandBuffer                             commandBuffer,
	VkBuffer                                    buffer,
	VkDeviceSize                                offset,
	uint32_t                                    drawCount,
	uint32_t                                    stride)
{
	if (commandBuffer != VK_NULL_HANDLE)
	{
		VK::CmdDrawIndirect* command = new VK::CmdDrawIndirect;
		command->SetContent(buffer, offset, drawCount, stride);
		commandBuffer->AppendCommand(command);
	}
}

void VKAPI_CALL vkCmdDrawIndexedIndirect(
	VkCommandBuffer                             commandBuffer,
	VkBuffer                                    buffer,
	VkDeviceSize                                offset,
	uint32_t                                    drawCount,
	uint32_t                                    stride)
{
	if (commandBuffer != VK_NULL_HANDLE)
	{
		VK::CmdDrawIndexedIndirect* command = new VK::CmdDrawIndexedIndirect;
		command->SetContent(buffer, offset, drawCount, stride);
		commandBuffer->AppendCommand(command);
	}
}

void VKAPI_CALL vkCmdDispatch(
	VkCommandBuffer                             commandBuffer,
	uint32_t                                    groupCountX,
	uint32_t                                    groupCountY,
	uint32_t                                    groupCountZ);

void VKAPI_CALL vkCmdDispatchIndirect(
	VkCommandBuffer                             commandBuffer,
	VkBuffer                                    buffer,
	VkDeviceSize                                offset);

void VKAPI_CALL vkCmdCopyBuffer(
	VkCommandBuffer                             commandBuffer,
	VkBuffer                                    srcBuffer,
	VkBuffer                                    dstBuffer,
	uint32_t                                    regionCount,
	const VkBufferCopy*                         pRegions);

void VKAPI_CALL vkCmdCopyImage(
	VkCommandBuffer                             commandBuffer,
	VkImage                                     srcImage,
	VkImageLayout                               srcImageLayout,
	VkImage                                     dstImage,
	VkImageLayout                               dstImageLayout,
	uint32_t                                    regionCount,
	const VkImageCopy*                          pRegions);

void VKAPI_CALL vkCmdBlitImage(
	VkCommandBuffer                             commandBuffer,
	VkImage                                     srcImage,
	VkImageLayout                               srcImageLayout,
	VkImage                                     dstImage,
	VkImageLayout                               dstImageLayout,
	uint32_t                                    regionCount,
	const VkImageBlit*                          pRegions,
	VkFilter                                    filter);

void VKAPI_CALL vkCmdCopyBufferToImage(
	VkCommandBuffer                             commandBuffer,
	VkBuffer                                    srcBuffer,
	VkImage                                     dstImage,
	VkImageLayout                               dstImageLayout,
	uint32_t                                    regionCount,
	const VkBufferImageCopy*                    pRegions);

void VKAPI_CALL vkCmdCopyImageToBuffer(
	VkCommandBuffer                             commandBuffer,
	VkImage                                     srcImage,
	VkImageLayout                               srcImageLayout,
	VkBuffer                                    dstBuffer,
	uint32_t                                    regionCount,
	const VkBufferImageCopy*                    pRegions);

void VKAPI_CALL vkCmdUpdateBuffer(
	VkCommandBuffer                             commandBuffer,
	VkBuffer                                    dstBuffer,
	VkDeviceSize                                dstOffset,
	VkDeviceSize                                dataSize,
	const void*                                 pData);

void VKAPI_CALL vkCmdFillBuffer(
	VkCommandBuffer                             commandBuffer,
	VkBuffer                                    dstBuffer,
	VkDeviceSize                                dstOffset,
	VkDeviceSize                                size,
	uint32_t                                    data);

void VKAPI_CALL vkCmdClearColorImage(
	VkCommandBuffer                             commandBuffer,
	VkImage                                     image,
	VkImageLayout                               imageLayout,
	const VkClearColorValue*                    pColor,
	uint32_t                                    rangeCount,
	const VkImageSubresourceRange*              pRanges);

void VKAPI_CALL vkCmdClearDepthStencilImage(
	VkCommandBuffer                             commandBuffer,
	VkImage                                     image,
	VkImageLayout                               imageLayout,
	const VkClearDepthStencilValue*             pDepthStencil,
	uint32_t                                    rangeCount,
	const VkImageSubresourceRange*              pRanges);

void VKAPI_CALL vkCmdClearAttachments(
	VkCommandBuffer                             commandBuffer,
	uint32_t                                    attachmentCount,
	const VkClearAttachment*                    pAttachments,
	uint32_t                                    rectCount,
	const VkClearRect*                          pRects);

void VKAPI_CALL vkCmdResolveImage(
	VkCommandBuffer                             commandBuffer,
	VkImage                                     srcImage,
	VkImageLayout                               srcImageLayout,
	VkImage                                     dstImage,
	VkImageLayout                               dstImageLayout,
	uint32_t                                    regionCount,
	const VkImageResolve*                       pRegions);

void VKAPI_CALL vkCmdSetEvent(
	VkCommandBuffer                             commandBuffer,
	VkEvent                                     event,
	VkPipelineStageFlags                        stageMask)
{
	//unimplement
}

void VKAPI_CALL vkCmdResetEvent(
	VkCommandBuffer                             commandBuffer,
	VkEvent                                     event,
	VkPipelineStageFlags                        stageMask)
{
	//unimplement
}

void VKAPI_CALL vkCmdWaitEvents(
	VkCommandBuffer                             commandBuffer,
	uint32_t                                    eventCount,
	const VkEvent*                              pEvents,
	VkPipelineStageFlags                        srcStageMask,
	VkPipelineStageFlags                        dstStageMask,
	uint32_t                                    memoryBarrierCount,
	const VkMemoryBarrier*                      pMemoryBarriers,
	uint32_t                                    bufferMemoryBarrierCount,
	const VkBufferMemoryBarrier*                pBufferMemoryBarriers,
	uint32_t                                    imageMemoryBarrierCount,
	const VkImageMemoryBarrier*                 pImageMemoryBarriers)
{
	//unimplement
}

void VKAPI_CALL vkCmdPipelineBarrier(
	VkCommandBuffer                             commandBuffer,
	VkPipelineStageFlags                        srcStageMask,
	VkPipelineStageFlags                        dstStageMask,
	VkDependencyFlags                           dependencyFlags,
	uint32_t                                    memoryBarrierCount,
	const VkMemoryBarrier*                      pMemoryBarriers,
	uint32_t                                    bufferMemoryBarrierCount,
	const VkBufferMemoryBarrier*                pBufferMemoryBarriers,
	uint32_t                                    imageMemoryBarrierCount,
	const VkImageMemoryBarrier*                 pImageMemoryBarriers);

void VKAPI_CALL vkCmdBeginQuery(
	VkCommandBuffer                             commandBuffer,
	VkQueryPool                                 queryPool,
	uint32_t                                    query,
	VkQueryControlFlags                         flags);

void VKAPI_CALL vkCmdEndQuery(
	VkCommandBuffer                             commandBuffer,
	VkQueryPool                                 queryPool,
	uint32_t                                    query);

void VKAPI_CALL vkCmdResetQueryPool(
	VkCommandBuffer                             commandBuffer,
	VkQueryPool                                 queryPool,
	uint32_t                                    firstQuery,
	uint32_t                                    queryCount);

void VKAPI_CALL vkCmdWriteTimestamp(
	VkCommandBuffer                             commandBuffer,
	VkPipelineStageFlagBits                     pipelineStage,
	VkQueryPool                                 queryPool,
	uint32_t                                    query);

void VKAPI_CALL vkCmdCopyQueryPoolResults(
	VkCommandBuffer                             commandBuffer,
	VkQueryPool                                 queryPool,
	uint32_t                                    firstQuery,
	uint32_t                                    queryCount,
	VkBuffer                                    dstBuffer,
	VkDeviceSize                                dstOffset,
	VkDeviceSize                                stride,
	VkQueryResultFlags                          flags);

void VKAPI_CALL vkCmdPushConstants(
	VkCommandBuffer                             commandBuffer,
	VkPipelineLayout                            layout,
	VkShaderStageFlags                          stageFlags,
	uint32_t                                    offset,
	uint32_t                                    size,
	const void*                                 pValues);

void VKAPI_CALL vkCmdBeginRenderPass(
	VkCommandBuffer                             commandBuffer,
	const VkRenderPassBeginInfo*                pRenderPassBegin,
	VkSubpassContents                           contents)
{
	if (commandBuffer != VK_NULL_HANDLE)
	{
		VK::CmdBeginRenderPass* command = new VK::CmdBeginRenderPass;
		command->SetContent(pRenderPassBegin, contents);
		commandBuffer->AppendCommand(command);
	}
}

void VKAPI_CALL vkCmdNextSubpass(
	VkCommandBuffer                             commandBuffer,
	VkSubpassContents                           contents);

void VKAPI_CALL vkCmdEndRenderPass(
	VkCommandBuffer                             commandBuffer)
{
	if (commandBuffer != VK_NULL_HANDLE)
	{
		VK::CmdEndRenderPass* command = new VK::CmdEndRenderPass;
		commandBuffer->AppendCommand(command);
	}
}

void VKAPI_CALL vkCmdExecuteCommands(
	VkCommandBuffer                             commandBuffer,
	uint32_t                                    commandBufferCount,
	const VkCommandBuffer*                      pCommandBuffers);
