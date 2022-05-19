/*
* Copyright (C) ATLAS Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of ATLAS nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include <cstdint>
#include <functional>
#include <Windows.h>

#include "RefPtr.h"

namespace Patch
{
	void* MakeTrampoline(const RefPtr& ptr, int* overwrittenCodeSize = nullptr);
	void Nop(const RefPtr& ptr, unsigned int size);
	void Call(const RefPtr& ptr, const RefPtr& data, unsigned int len = 5);
	void Jump(const RefPtr& ptr, const RefPtr& data, unsigned int len = 5);

	template<typename T>
	void __forceinline Patch(T* ptr, T data)
	{
		DWORD oldProtect;

		VirtualProtect(ptr, sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtect);

		*static_cast<T*>(static_cast<void*>(ptr)) = data;

		VirtualProtect(ptr, sizeof(T), oldProtect, &oldProtect);
	}

	template<typename T>
	__forceinline void* GetP(T a)
	{
		return *reinterpret_cast<void**>(&a);
	}

	template <typename T>
    void LambdaCall(const RefPtr& kSource, T* pFunction, const int nLength = 5)
	{
		const auto uiDest = static_cast<uint32_t>(pFunction);
		Patch::Call(kSource, uiDest, nLength);
	}

	template<typename T>
    T TrampolineJump(const RefPtr& ptr, const RefPtr& data, unsigned int len = 5)
	{
		int overwrittenCodeSize;

		T result = reinterpret_cast<T>(MakeTrampoline(ptr, &overwrittenCodeSize));
		Jump(ptr, data, overwrittenCodeSize);
		return result;
	}


	template <typename T> static std::function<T> DoCall(DWORD function)
	{
		return std::function<T>(reinterpret_cast<T*>(function));
	}

	template <typename T> static std::function<T> DoCall(FARPROC function)
	{
		return DoCall<T>(reinterpret_cast<DWORD>(function));
	}

	template <typename T> static std::function<T> DoCall(void* function)
	{
		return DoCall<T>(reinterpret_cast<DWORD>(function));
	}
}