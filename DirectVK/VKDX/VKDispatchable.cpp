#include "VKDispatchable.h"


namespace VK
{
	Dispatchable::Dispatchable(void)
	{
		mLoaderData.loaderMagic = ICD_LOADER_MAGIC;
	}


	Dispatchable::~Dispatchable(void)
	{
	}
}