#include "VKFence.h"
#include "VKDevice.h"

namespace VK
{
	Fence::Fence(void) :
		mValue(0)
	{
	}

	Fence::~Fence(void)
	{
	}

	VkResult Fence::Create(Device* device, const VkFenceCreateInfo* info)
	{
		mDevice = device;
		mDevice->GetDevice()->CreateFence(mValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&mFence));
		return mResult;
	}

	VkResult Fence::WaitFor(uint64_t timeout) const
	{
		VkResult result = VK_SUCCESS;
		if (mFence->GetCompletedValue() < mValue)
		{
			HANDLE event = CreateEvent(nullptr, FALSE, FALSE, nullptr);
			ThrowIfFailed(mFence->SetEventOnCompletion(mValue, event));
			DWORD result = WaitForSingleObject(event, static_cast<DWORD>(timeout));
			result = (WAIT_TIMEOUT == result) ? VK_TIMEOUT : VK_SUCCESS;
			CloseHandle(event);
		}
		return result;
	}

	void Fence::Reset(void)
	{
		mFence->Signal(0);
		mValue = 0;
	}

	VkResult Fence::GetStatus(void) const
	{
		VkResult status = mFence->GetCompletedValue() == mValue ? VK_SUCCESS : VK_NOT_READY;
		return status;
	}
}