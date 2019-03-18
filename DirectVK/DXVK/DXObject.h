#pragma once

#include "DXHeader.h"
#include "DXClasses.h"

namespace DX
{
	class Device;
	class Object
	{
	public:
		explicit Object(Device* device);
		virtual ~Object(void);

	protected:
		Device* mDevice = nullptr;
	};
}
