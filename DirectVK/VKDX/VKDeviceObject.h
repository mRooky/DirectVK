#pragma once
#include "VKObject.h"

namespace VK
{
	class DeviceObject : public Object
	{
	public:
		DeviceObject(void);
		virtual ~DeviceObject(void) override;

	public:
		inline Device* GetDevice(void) const { return mDevice; }

	protected:
		Device * mDevice;
	};
}
