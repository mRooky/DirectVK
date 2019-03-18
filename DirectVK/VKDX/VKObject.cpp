#include "VKObject.h"
#include <exception>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "d3dcompiler.lib")


namespace VK
{
	Object::Object(void) :
		mResult(VK_INCOMPLETE)
	{
	}

	Object::~Object(void)
	{
	}

	void ThrowIfFailed(HRESULT result)
	{
		if (FAILED(result))
		{
			throw std::exception();
		}
	}

}