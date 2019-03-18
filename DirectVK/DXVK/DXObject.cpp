#include "DXObject.h"
#include <cassert>

namespace DX
{
	Object::Object(Device* device):
		mDevice(device)
	{
		assert(mDevice != nullptr);
	}

	Object::~Object(void)
	{
		mDevice = nullptr;
	}
}