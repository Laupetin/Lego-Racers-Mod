#pragma once

struct InstructionLength
{
	// Length of the original unmodified instruction
	int length;

	// This length might be longer than the original length when the instruction had to be updated
	// For example due to to an original 8bit offset (Updated to a 32bit offset to match the instruction target)
	int extendedLength;
};

extern InstructionLength GetInstructionLength(char* pos);

extern InstructionLength CopyInstruction(char* source, char* dest);