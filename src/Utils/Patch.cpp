#include "Patch.h"

#include <cassert>

#include "InstructionLengths.h"

#define CALL_NEAR32 0xE8
#define JMP_NEAR32 0xE9
#define NOP 0x90

namespace Patch
{
	void* MakeTrampoline(const RefPtr& ptr, int* overwrittenCodeSize)
	{
		DWORD temp;
		DWORD oldProtect;

        assert(static_cast<void*>(ptr) != nullptr);

		if (overwrittenCodeSize)
			*overwrittenCodeSize = 0;

		VirtualProtect(ptr, 5 + 12, PAGE_EXECUTE_READWRITE, &oldProtect);

		int originalCodeSize = 0;
		int allocationSize = 0;

		while (originalCodeSize < 5)
		{
            const InstructionLength length = GetInstructionLength(reinterpret_cast<char*>(static_cast<uint32_t>(ptr) + originalCodeSize));

			originalCodeSize += length.length;
			allocationSize += length.extendedLength;
		}

		allocationSize += 5; // Space for the Jump back

		void* trampoline = malloc(allocationSize);
		VirtualProtect(trampoline, allocationSize, PAGE_EXECUTE_READWRITE, &temp);

		int sourceOffset = 0;
		int targetOffset = 0;
		while(sourceOffset < originalCodeSize)
		{
            const InstructionLength length = CopyInstruction(static_cast<char*>(static_cast<void*>(ptr)) + sourceOffset, static_cast<char*>(trampoline) + targetOffset);
			sourceOffset += length.length;
			targetOffset += length.extendedLength;
		}

		Jump(static_cast<char*>(trampoline) + targetOffset, static_cast<char*>(static_cast<void*>(ptr)) + sourceOffset);

		// Memory allocation runtime checks let the application crash when it cannot write to the allocated memory. Therefore leave it writable
		// VirtualProtect(trampoline, allocationSize, PAGE_EXECUTE_READ, &temp);

		VirtualProtect(ptr, 5 + 12, oldProtect, &oldProtect);

		if (overwrittenCodeSize)
			*overwrittenCodeSize = originalCodeSize;

		return trampoline;
	}

	void Nop(const RefPtr& ptr, const unsigned size)
	{
		assert(static_cast<void*>(ptr) != nullptr);
		assert(size > 0);
		DWORD oldProtect;

		VirtualProtect(ptr, size, PAGE_EXECUTE_READWRITE, &oldProtect);

		memset(ptr, NOP, size);

		VirtualProtect(ptr, size, oldProtect, &oldProtect);
	}

	void Call(const RefPtr& ptr, const RefPtr& data, unsigned int len)
	{
		assert(static_cast<void*>(ptr) != nullptr);
		assert(len >= 5);
		if (len < 5)
			return;

		DWORD oldProtect;

		VirtualProtect(ptr, len, PAGE_EXECUTE_READWRITE, &oldProtect);

		*static_cast<BYTE*>(ptr) = CALL_NEAR32;
		*reinterpret_cast<DWORD*>(static_cast<uint32_t>(ptr) + 1) = static_cast<uint32_t>(data) - static_cast<uint32_t>(ptr) - 5;

		if (len > 5)
			memset(reinterpret_cast<void*>(static_cast<uint32_t>(ptr) + 5), NOP, len - 5);

		VirtualProtect(ptr, len, oldProtect, &oldProtect);
	}

	void Jump(const RefPtr& ptr, const RefPtr& data, unsigned int len)
	{
		assert((void*)ptr != nullptr);
		assert(len >= 5);
		if (len < 5)
			return;

		DWORD oldProtect;

		VirtualProtect(ptr, 5, PAGE_EXECUTE_READWRITE, &oldProtect);

		*static_cast<BYTE*>(ptr) = JMP_NEAR32;
		*reinterpret_cast<DWORD*>(static_cast<uint32_t>(ptr) + 1) = static_cast<uint32_t>(data) - static_cast<uint32_t>(ptr) - 5;

		if (len > 5)
			memset(reinterpret_cast<void*>(static_cast<uint32_t>(ptr) + 5), NOP, len - 5);

		VirtualProtect(ptr, 5, oldProtect, &oldProtect);
	}
}