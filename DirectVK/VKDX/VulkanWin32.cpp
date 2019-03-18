#include "VKInterface.h"
#include <cassert>

VkResult VKAPI_CALL vkCreateWin32SurfaceKHR(
	VkInstance                                  instance,
	const VkWin32SurfaceCreateInfoKHR*          pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkSurfaceKHR*                               pSurface)
{
	VkSurfaceKHR_T* surface = new VkSurfaceKHR_T;
	VkResult result = surface->Create(instance, pCreateInfo);
	*pSurface = surface;
	return result;
}