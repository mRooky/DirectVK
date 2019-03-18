/*
===========================================================================
Copyright (C) 2018 rookyma. DirextXVK GPLv3 Source Code.
===========================================================================
*/

#pragma once

#include "VKClasses.h"
#define VK_USE_PLATFORM_WIN32_KHR
#include "VKHeader.h"

using Microsoft::WRL::ComPtr;

namespace VK
{
	class Object
	{
	protected:
		Object(void);
		virtual ~Object(void);

	public:
		VkResult GetResult(void) const { return mResult; }

	protected:
		VkResult mResult;
	};

	void ThrowIfFailed(HRESULT result);
}
