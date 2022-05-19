#include "InstructionLengths.h"

#include <stdint.h>
#include <Windows.h>
#include <assert.h>

enum ImmediateType
{
	IMM_None,
	IMM_8,
	IMM_16,
	IMM_8_16,
	IMM_32,
	IMM_16_32,
	REL_8,
	REL_32
};

enum ModRM_Flags
{
	ModRM_None = 0,

	ModRM_Opcode_0 = 0,
	ModRM_Opcode_1 = 1,
	ModRM_Opcode_2 = 2,
	ModRM_Opcode_3 = 3,
	ModRM_Opcode_4 = 4,
	ModRM_Opcode_5 = 5,
	ModRM_Opcode_6 = 6,
	ModRM_Opcode_7 = 7,
	ModRM_Opcoded = 8,

	//ModRM_16 = 16,
	ModRM_32 = 32,
};

const int ModRM_OPCODE_MASK =
ModRM_Opcode_0
| ModRM_Opcode_1
| ModRM_Opcode_2
| ModRM_Opcode_3
| ModRM_Opcode_4
| ModRM_Opcode_5
| ModRM_Opcode_6
| ModRM_Opcode_7;

const int ModRM_TABLE_MASK = ModRM_32;

struct Instruction_s
{
	int16_t opcode1;
	int16_t opcode2 = -1;
	int16_t opcode3 = -1;
	uint32_t modrm;
	ImmediateType imm;
	int16_t relatedRelative1 = -1;
	int16_t relatedRelative2 = -1;
	int16_t relatedRelative3 = -1;
};

#define ModRM_Opcode( c ) ModRM_32 | ModRM_Opcoded | ModRM_Opcode_##c
#define Opcode3( c1, c2, c3 ) c1, c2, c3
#define Opcode2( c1 , c2 ) Opcode3( c1, c2, -1 )
#define Opcode( c ) Opcode2( c, -1 )

Instruction_s instructions[]
{
	/*
	{ PREFIXED, OPCODE, MODRM, IMM },
	*/
	{ Opcode(0x00), ModRM_32, IMM_None },
{ Opcode(0x01), ModRM_32, IMM_None },
{ Opcode(0x02), ModRM_32, IMM_None },
{ Opcode(0x03), ModRM_32, IMM_None },
{ Opcode(0x04), ModRM_None, IMM_8 },
{ Opcode(0x05), ModRM_None, IMM_32 },
{ Opcode(0x06), ModRM_None, IMM_None },
{ Opcode(0x07), ModRM_None, IMM_None },
{ Opcode(0x08), ModRM_32, IMM_None },
{ Opcode(0x09), ModRM_32, IMM_None },
{ Opcode(0x0a), ModRM_32, IMM_None },
{ Opcode(0x0b), ModRM_32, IMM_None },
{ Opcode(0x0c), ModRM_None, IMM_8 },
{ Opcode(0x0d), ModRM_None, IMM_32 },
{ Opcode(0x0e), ModRM_None, IMM_None },
// 0x0F PREFIX 2-BYTE INSTRUCTIONS
{ Opcode(0x10), ModRM_32, IMM_None },
{ Opcode(0x11), ModRM_32, IMM_None },
{ Opcode(0x12), ModRM_32, IMM_None },
{ Opcode(0x13), ModRM_32, IMM_None },
{ Opcode(0x14), ModRM_None, IMM_8 },
{ Opcode(0x15), ModRM_None, IMM_32 },
{ Opcode(0x16), ModRM_None, IMM_None },
{ Opcode(0x17), ModRM_None, IMM_None },
{ Opcode(0x18), ModRM_32, IMM_None },
{ Opcode(0x19), ModRM_32, IMM_None },
{ Opcode(0x1a), ModRM_32, IMM_None },
{ Opcode(0x1b), ModRM_32, IMM_None },
{ Opcode(0x1c), ModRM_None, IMM_8 },
{ Opcode(0x1d), ModRM_None, IMM_32 },
{ Opcode(0x1e), ModRM_None, IMM_None },
{ Opcode(0x1f), ModRM_None, IMM_None },
{ Opcode(0x20), ModRM_32, IMM_None },
{ Opcode(0x21), ModRM_32, IMM_None },
{ Opcode(0x22), ModRM_32, IMM_None },
{ Opcode(0x23), ModRM_32, IMM_None },
{ Opcode(0x24), ModRM_None, IMM_8 },
{ Opcode(0x25), ModRM_None, IMM_32 },
// 0x26 PREFIX ES
{ Opcode(0x27), ModRM_None, IMM_None },
{ Opcode(0x28), ModRM_32, IMM_None },
{ Opcode(0x29), ModRM_32, IMM_None },
{ Opcode(0x2a), ModRM_32, IMM_None },
{ Opcode(0x2b), ModRM_32, IMM_None },
{ Opcode(0x2c), ModRM_None, IMM_8 },
{ Opcode(0x2d), ModRM_None, IMM_32 },
// 0x2E PREFIX CS
{ Opcode(0x2f), ModRM_None, IMM_None },
{ Opcode(0x30), ModRM_32, IMM_None },
{ Opcode(0x31), ModRM_32, IMM_None },
{ Opcode(0x32), ModRM_32, IMM_None },
{ Opcode(0x33), ModRM_32, IMM_None },
{ Opcode(0x34), ModRM_None, IMM_8 },
{ Opcode(0x35), ModRM_None, IMM_32 },
// 0x36 PREFIX SS
{ Opcode(0x37), ModRM_None, IMM_None },
{ Opcode(0x38), ModRM_32, IMM_None },
{ Opcode(0x39), ModRM_32, IMM_None },
{ Opcode(0x3a), ModRM_32, IMM_None },
{ Opcode(0x3b), ModRM_32, IMM_None },
{ Opcode(0x3c), ModRM_None, IMM_8 },
{ Opcode(0x3d), ModRM_None, IMM_32 },
// 0x3E PREFIX DS
{ Opcode(0x3F), ModRM_None, IMM_None },
{ Opcode(0x40), ModRM_None, IMM_None },
{ Opcode(0x41), ModRM_None, IMM_None },
{ Opcode(0x42), ModRM_None, IMM_None },
{ Opcode(0x43), ModRM_None, IMM_None },
{ Opcode(0x44), ModRM_None, IMM_None },
{ Opcode(0x45), ModRM_None, IMM_None },
{ Opcode(0x46), ModRM_None, IMM_None },
{ Opcode(0x47), ModRM_None, IMM_None },
{ Opcode(0x48), ModRM_None, IMM_None },
{ Opcode(0x49), ModRM_None, IMM_None },
{ Opcode(0x4a), ModRM_None, IMM_None },
{ Opcode(0x4b), ModRM_None, IMM_None },
{ Opcode(0x4c), ModRM_None, IMM_None },
{ Opcode(0x4d), ModRM_None, IMM_None },
{ Opcode(0x4e), ModRM_None, IMM_None },
{ Opcode(0x4f), ModRM_None, IMM_None },
{ Opcode(0x50), ModRM_None, IMM_None },
{ Opcode(0x51), ModRM_None, IMM_None },
{ Opcode(0x52), ModRM_None, IMM_None },
{ Opcode(0x53), ModRM_None, IMM_None },
{ Opcode(0x54), ModRM_None, IMM_None },
{ Opcode(0x55), ModRM_None, IMM_None },
{ Opcode(0x56), ModRM_None, IMM_None },
{ Opcode(0x57), ModRM_None, IMM_None },
{ Opcode(0x58), ModRM_None, IMM_None },
{ Opcode(0x59), ModRM_None, IMM_None },
{ Opcode(0x5a), ModRM_None, IMM_None },
{ Opcode(0x5b), ModRM_None, IMM_None },
{ Opcode(0x5c), ModRM_None, IMM_None },
{ Opcode(0x5d), ModRM_None, IMM_None },
{ Opcode(0x5e), ModRM_None, IMM_None },
{ Opcode(0x5f), ModRM_None, IMM_None },
{ Opcode(0x60), ModRM_None, IMM_None },
{ Opcode(0x61), ModRM_None, IMM_None },
{ Opcode(0x62), ModRM_32, IMM_None },
{ Opcode(0x63), ModRM_32, IMM_None },
// 0x64 PREFIX FS
// 0x65 PREFIX GS
// 0x66 PREFIX -
// 0x67 PREFIX -
{ Opcode(0x68), ModRM_None, IMM_32 },
{ Opcode(0x69), ModRM_32, IMM_32 },
{ Opcode(0x6a), ModRM_None, IMM_8 },
{ Opcode(0x6b), ModRM_32, IMM_8 },
{ Opcode(0x6c), ModRM_None, IMM_None },
{ Opcode(0x6d), ModRM_None, IMM_None },
{ Opcode(0x6e), ModRM_None, IMM_None },
{ Opcode(0x6f), ModRM_None, IMM_None },
{ Opcode(0x70), ModRM_None, REL_8, Opcode2(0x0F, 0x80) },
{ Opcode(0x71), ModRM_None, REL_8, Opcode2(0x0F, 0x81) },
{ Opcode(0x72), ModRM_None, REL_8, Opcode2(0x0F, 0x82) },
{ Opcode(0x73), ModRM_None, REL_8, Opcode2(0x0F, 0x83) },
{ Opcode(0x74), ModRM_None, REL_8, Opcode2(0x0F, 0x84) },
{ Opcode(0x75), ModRM_None, REL_8, Opcode2(0x0F, 0x85) },
{ Opcode(0x76), ModRM_None, REL_8, Opcode2(0x0F, 0x86) },
{ Opcode(0x77), ModRM_None, REL_8, Opcode2(0x0F, 0x87) },
{ Opcode(0x78), ModRM_None, REL_8, Opcode2(0x0F, 0x88) },
{ Opcode(0x79), ModRM_None, REL_8, Opcode2(0x0F, 0x89) },
{ Opcode(0x7a), ModRM_None, REL_8, Opcode2(0x0F, 0x8a) },
{ Opcode(0x7b), ModRM_None, REL_8, Opcode2(0x0F, 0x8b) },
{ Opcode(0x7c), ModRM_None, REL_8, Opcode2(0x0F, 0x8c) },
{ Opcode(0x7d), ModRM_None, REL_8, Opcode2(0x0F, 0x8d) },
{ Opcode(0x7e), ModRM_None, REL_8, Opcode2(0x0F, 0x8e) },
{ Opcode(0x7f), ModRM_None, REL_8, Opcode2(0x0F, 0x8f) },
{ Opcode(0x80), ModRM_Opcode(0), IMM_8 },
{ Opcode(0x80), ModRM_Opcode(1), IMM_8 },
{ Opcode(0x80), ModRM_Opcode(2), IMM_8 },
{ Opcode(0x80), ModRM_Opcode(3), IMM_8 },
{ Opcode(0x80), ModRM_Opcode(4), IMM_8 },
{ Opcode(0x80), ModRM_Opcode(5), IMM_8 },
{ Opcode(0x80), ModRM_Opcode(6), IMM_8 },
{ Opcode(0x80), ModRM_Opcode(7), IMM_8 },

{ Opcode(0x81), ModRM_Opcode(0), IMM_32 },
{ Opcode(0x81), ModRM_Opcode(1), IMM_32 },
{ Opcode(0x81), ModRM_Opcode(2), IMM_32 },
{ Opcode(0x81), ModRM_Opcode(3), IMM_32 },
{ Opcode(0x81), ModRM_Opcode(4), IMM_32 },
{ Opcode(0x81), ModRM_Opcode(5), IMM_32 },
{ Opcode(0x81), ModRM_Opcode(6), IMM_32 },
{ Opcode(0x81), ModRM_Opcode(7), IMM_32 },

{ Opcode(0x82), ModRM_Opcode(0), IMM_8 },
{ Opcode(0x82), ModRM_Opcode(1), IMM_8 },
{ Opcode(0x82), ModRM_Opcode(2), IMM_8 },
{ Opcode(0x82), ModRM_Opcode(3), IMM_8 },
{ Opcode(0x82), ModRM_Opcode(4), IMM_8 },
{ Opcode(0x82), ModRM_Opcode(5), IMM_8 },
{ Opcode(0x82), ModRM_Opcode(6), IMM_8 },
{ Opcode(0x82), ModRM_Opcode(7), IMM_8 },

{ Opcode(0x83), ModRM_Opcode(0), IMM_8 },
{ Opcode(0x83), ModRM_Opcode(1), IMM_8 },
{ Opcode(0x83), ModRM_Opcode(2), IMM_8 },
{ Opcode(0x83), ModRM_Opcode(3), IMM_8 },
{ Opcode(0x83), ModRM_Opcode(4), IMM_8 },
{ Opcode(0x83), ModRM_Opcode(5), IMM_8 },
{ Opcode(0x83), ModRM_Opcode(6), IMM_8 },
{ Opcode(0x83), ModRM_Opcode(7), IMM_8 },

{ Opcode(0x84), ModRM_32, IMM_None },
{ Opcode(0x85), ModRM_32, IMM_None },
{ Opcode(0x86), ModRM_32, IMM_None },
{ Opcode(0x87), ModRM_32, IMM_None },
{ Opcode(0x88), ModRM_32, IMM_None },
{ Opcode(0x89), ModRM_32, IMM_None },
{ Opcode(0x8a), ModRM_32, IMM_None },
{ Opcode(0x8b), ModRM_32, IMM_None },
{ Opcode(0x8c), ModRM_32, IMM_None },
{ Opcode(0x8d), ModRM_32, IMM_None },
{ Opcode(0x8e), ModRM_32, IMM_None },
{ Opcode(0x8f), ModRM_Opcode(0), IMM_None },

{ Opcode(0x90), ModRM_None, IMM_None },
{ Opcode(0x91), ModRM_None, IMM_None },
{ Opcode(0x92), ModRM_None, IMM_None },
{ Opcode(0x93), ModRM_None, IMM_None },
{ Opcode(0x94), ModRM_None, IMM_None },
{ Opcode(0x95), ModRM_None, IMM_None },
{ Opcode(0x96), ModRM_None, IMM_None },
{ Opcode(0x97), ModRM_None, IMM_None },
{ Opcode(0x98), ModRM_None, IMM_None },
{ Opcode(0x99), ModRM_None, IMM_None },
{ Opcode(0x9a), ModRM_None, IMM_16_32 },
{ Opcode(0x9b), ModRM_None, IMM_None },
{ Opcode(0x9c), ModRM_None, IMM_None },
{ Opcode(0x9d), ModRM_None, IMM_None },
{ Opcode(0x9e), ModRM_None, IMM_None },
{ Opcode(0x9f), ModRM_None, IMM_None },
{ Opcode(0xa0), ModRM_None, IMM_32 },
{ Opcode(0xa1), ModRM_None, IMM_32 },
{ Opcode(0xa2), ModRM_None, IMM_32 },
{ Opcode(0xa3), ModRM_None, IMM_32 },
{ Opcode(0xa4), ModRM_None, IMM_None },
{ Opcode(0xa5), ModRM_None, IMM_None },
{ Opcode(0xa6), ModRM_None, IMM_None },
{ Opcode(0xa7), ModRM_None, IMM_None },
{ Opcode(0xa8), ModRM_None, IMM_8 },
{ Opcode(0xa9), ModRM_None, IMM_32 },
{ Opcode(0xaa), ModRM_None, IMM_None },
{ Opcode(0xab), ModRM_None, IMM_None },
{ Opcode(0xac), ModRM_None, IMM_None },
{ Opcode(0xad), ModRM_None, IMM_None },
{ Opcode(0xae), ModRM_None, IMM_None },
{ Opcode(0xaf), ModRM_None, IMM_None },
{ Opcode(0xb0), ModRM_None, IMM_8 },
{ Opcode(0xb1), ModRM_None, IMM_8 },
{ Opcode(0xb2), ModRM_None, IMM_8 },
{ Opcode(0xb3), ModRM_None, IMM_8 },
{ Opcode(0xb4), ModRM_None, IMM_8 },
{ Opcode(0xb5), ModRM_None, IMM_8 },
{ Opcode(0xb6), ModRM_None, IMM_8 },
{ Opcode(0xb7), ModRM_None, IMM_8 },
{ Opcode(0xb8), ModRM_None, IMM_32 },
{ Opcode(0xb9), ModRM_None, IMM_32 },
{ Opcode(0xba), ModRM_None, IMM_32 },
{ Opcode(0xbb), ModRM_None, IMM_32 },
{ Opcode(0xbc), ModRM_None, IMM_32 },
{ Opcode(0xbd), ModRM_None, IMM_32 },
{ Opcode(0xbe), ModRM_None, IMM_32 },
{ Opcode(0xbf), ModRM_None, IMM_32 },

{ Opcode(0xc0), ModRM_Opcode(0), IMM_8 },
{ Opcode(0xc0), ModRM_Opcode(1), IMM_8 },
{ Opcode(0xc0), ModRM_Opcode(2), IMM_8 },
{ Opcode(0xc0), ModRM_Opcode(3), IMM_8 },
{ Opcode(0xc0), ModRM_Opcode(4), IMM_8 },
{ Opcode(0xc0), ModRM_Opcode(5), IMM_8 },
{ Opcode(0xc0), ModRM_Opcode(6), IMM_8 },
{ Opcode(0xc0), ModRM_Opcode(7), IMM_8 },

{ Opcode(0xc1), ModRM_Opcode(0), IMM_8 },
{ Opcode(0xc1), ModRM_Opcode(1), IMM_8 },
{ Opcode(0xc1), ModRM_Opcode(2), IMM_8 },
{ Opcode(0xc1), ModRM_Opcode(3), IMM_8 },
{ Opcode(0xc1), ModRM_Opcode(4), IMM_8 },
{ Opcode(0xc1), ModRM_Opcode(5), IMM_8 },
{ Opcode(0xc1), ModRM_Opcode(6), IMM_8 },
{ Opcode(0xc1), ModRM_Opcode(7), IMM_8 },

{ Opcode(0xc2), ModRM_None, IMM_16 },
{ Opcode(0xc3), ModRM_None, IMM_None },
{ Opcode(0xc4), ModRM_32, IMM_8 },
{ Opcode(0xc5), ModRM_32, IMM_32 },
{ Opcode(0xc6), ModRM_Opcode(0), IMM_8 },
{ Opcode(0xc7), ModRM_Opcode(0), IMM_32 },
{ Opcode(0xc8), ModRM_None, IMM_8_16 },
{ Opcode(0xc9), ModRM_None, IMM_None },
{ Opcode(0xca), ModRM_None, IMM_16 },
{ Opcode(0xcb), ModRM_None, IMM_None },
{ Opcode(0xcc), ModRM_None, IMM_None },
{ Opcode(0xcd), ModRM_None, IMM_8 },
{ Opcode(0xce), ModRM_None, IMM_None },
{ Opcode(0xcf), ModRM_None, IMM_None },

{ Opcode(0xd0), ModRM_Opcode(0), IMM_None },
{ Opcode(0xd0), ModRM_Opcode(1), IMM_None },
{ Opcode(0xd0), ModRM_Opcode(2), IMM_None },
{ Opcode(0xd0), ModRM_Opcode(3), IMM_None },
{ Opcode(0xd0), ModRM_Opcode(4), IMM_None },
{ Opcode(0xd0), ModRM_Opcode(5), IMM_None },
{ Opcode(0xd0), ModRM_Opcode(6), IMM_None },
{ Opcode(0xd0), ModRM_Opcode(7), IMM_None },

{ Opcode(0xd1), ModRM_Opcode(0), IMM_None },
{ Opcode(0xd1), ModRM_Opcode(1), IMM_None },
{ Opcode(0xd1), ModRM_Opcode(2), IMM_None },
{ Opcode(0xd1), ModRM_Opcode(3), IMM_None },
{ Opcode(0xd1), ModRM_Opcode(4), IMM_None },
{ Opcode(0xd1), ModRM_Opcode(5), IMM_None },
{ Opcode(0xd1), ModRM_Opcode(6), IMM_None },
{ Opcode(0xd1), ModRM_Opcode(7), IMM_None },

{ Opcode(0xd2), ModRM_Opcode(0), IMM_None },
{ Opcode(0xd2), ModRM_Opcode(1), IMM_None },
{ Opcode(0xd2), ModRM_Opcode(2), IMM_None },
{ Opcode(0xd2), ModRM_Opcode(3), IMM_None },
{ Opcode(0xd2), ModRM_Opcode(4), IMM_None },
{ Opcode(0xd2), ModRM_Opcode(5), IMM_None },
{ Opcode(0xd2), ModRM_Opcode(6), IMM_None },
{ Opcode(0xd2), ModRM_Opcode(7), IMM_None },

{ Opcode(0xd3), ModRM_Opcode(0), IMM_None },
{ Opcode(0xd3), ModRM_Opcode(1), IMM_None },
{ Opcode(0xd3), ModRM_Opcode(2), IMM_None },
{ Opcode(0xd3), ModRM_Opcode(3), IMM_None },
{ Opcode(0xd3), ModRM_Opcode(4), IMM_None },
{ Opcode(0xd3), ModRM_Opcode(5), IMM_None },
{ Opcode(0xd3), ModRM_Opcode(6), IMM_None },
{ Opcode(0xd3), ModRM_Opcode(7), IMM_None },

{ Opcode(0xd4), ModRM_None, IMM_8 },
{ Opcode(0xd5), ModRM_None, IMM_8 },
// 0xD6 Undefined
{ Opcode(0xd7), ModRM_None, IMM_None },

{ Opcode(0xd8), ModRM_Opcode(0), IMM_None },
{ Opcode(0xd8), ModRM_Opcode(1), IMM_None },
{ Opcode(0xd8), ModRM_Opcode(2), IMM_None },
{ Opcode(0xd8), ModRM_Opcode(3), IMM_None },
{ Opcode(0xd8), ModRM_Opcode(4), IMM_None },
{ Opcode(0xd8), ModRM_Opcode(5), IMM_None },
{ Opcode(0xd8), ModRM_Opcode(6), IMM_None },
{ Opcode(0xd8), ModRM_Opcode(7), IMM_None },

{ Opcode(0xd9), ModRM_Opcode(0), IMM_None },
{ Opcode(0xd9), ModRM_Opcode(1), IMM_None },
{ Opcode(0xd9), ModRM_Opcode(2), IMM_None },
{ Opcode(0xd9), ModRM_Opcode(3), IMM_None },
{ Opcode(0xd9), ModRM_Opcode(4), IMM_None },
{ Opcode(0xd9), ModRM_Opcode(5), IMM_None },
{ Opcode(0xd9), ModRM_Opcode(6), IMM_None },
{ Opcode(0xd9), ModRM_Opcode(7), IMM_None },

{ Opcode(0xda), ModRM_Opcode(0), IMM_None },
{ Opcode(0xda), ModRM_Opcode(1), IMM_None },
{ Opcode(0xda), ModRM_Opcode(2), IMM_None },
{ Opcode(0xda), ModRM_Opcode(3), IMM_None },
{ Opcode(0xda), ModRM_Opcode(4), IMM_None },
{ Opcode(0xda), ModRM_Opcode(5), IMM_None },
{ Opcode(0xda), ModRM_Opcode(6), IMM_None },
{ Opcode(0xda), ModRM_Opcode(7), IMM_None },

{ Opcode(0xdb), ModRM_Opcode(0), IMM_None },
{ Opcode(0xdb), ModRM_Opcode(1), IMM_None },
{ Opcode(0xdb), ModRM_Opcode(2), IMM_None },
{ Opcode(0xdb), ModRM_Opcode(3), IMM_None },
{ Opcode(0xdb), ModRM_Opcode(4), IMM_None },
{ Opcode(0xdb), ModRM_Opcode(5), IMM_None },
{ Opcode(0xdb), ModRM_Opcode(6), IMM_None },
{ Opcode(0xdb), ModRM_Opcode(7), IMM_None },

{ Opcode(0xdc), ModRM_Opcode(0), IMM_None },
{ Opcode(0xdc), ModRM_Opcode(1), IMM_None },
{ Opcode(0xdc), ModRM_Opcode(2), IMM_None },
{ Opcode(0xdc), ModRM_Opcode(3), IMM_None },
{ Opcode(0xdc), ModRM_Opcode(4), IMM_None },
{ Opcode(0xdc), ModRM_Opcode(5), IMM_None },
{ Opcode(0xdc), ModRM_Opcode(6), IMM_None },
{ Opcode(0xdc), ModRM_Opcode(7), IMM_None },

{ Opcode(0xdd), ModRM_Opcode(0), IMM_None },
{ Opcode(0xdd), ModRM_Opcode(1), IMM_None },
{ Opcode(0xdd), ModRM_Opcode(2), IMM_None },
{ Opcode(0xdd), ModRM_Opcode(3), IMM_None },
{ Opcode(0xdd), ModRM_Opcode(4), IMM_None },
{ Opcode(0xdd), ModRM_Opcode(5), IMM_None },
{ Opcode(0xdd), ModRM_Opcode(6), IMM_None },
{ Opcode(0xdd), ModRM_Opcode(7), IMM_None },

{ Opcode(0xde), ModRM_Opcode(0), IMM_None },
{ Opcode(0xde), ModRM_Opcode(1), IMM_None },
{ Opcode(0xde), ModRM_Opcode(2), IMM_None },
{ Opcode(0xde), ModRM_Opcode(3), IMM_None },
{ Opcode(0xde), ModRM_Opcode(4), IMM_None },
{ Opcode(0xde), ModRM_Opcode(5), IMM_None },
{ Opcode(0xde), ModRM_Opcode(6), IMM_None },
{ Opcode(0xde), ModRM_Opcode(7), IMM_None },

{ Opcode(0xdf), ModRM_Opcode(0), IMM_None },
{ Opcode(0xdf), ModRM_Opcode(1), IMM_None },
{ Opcode(0xdf), ModRM_Opcode(2), IMM_None },
{ Opcode(0xdf), ModRM_Opcode(3), IMM_None },
{ Opcode(0xdf), ModRM_Opcode(4), IMM_None },
{ Opcode(0xdf), ModRM_Opcode(5), IMM_None },
{ Opcode(0xdf), ModRM_Opcode(6), IMM_None },
{ Opcode(0xdf), ModRM_Opcode(7), IMM_None },

{ Opcode(0xe0), ModRM_None, REL_8, Opcode(-2) },
{ Opcode(0xe1), ModRM_None, REL_8, Opcode(-2) },
{ Opcode(0xe2), ModRM_None, REL_8, Opcode(-2) },
{ Opcode(0xe3), ModRM_None, REL_8, Opcode(-2) },
{ Opcode(0xe4), ModRM_None, IMM_8 },
{ Opcode(0xe5), ModRM_None, IMM_8 },
{ Opcode(0xe6), ModRM_None, IMM_8 },
{ Opcode(0xe7), ModRM_None, IMM_8 },
{ Opcode(0xe8), ModRM_None, REL_32 },
{ Opcode(0xe9), ModRM_None, REL_32 },
{ Opcode(0xea), ModRM_None, IMM_16_32 },
{ Opcode(0xeb), ModRM_None, REL_8 , Opcode(0xe9) },
{ Opcode(0xec), ModRM_None, IMM_None },
{ Opcode(0xed), ModRM_None, IMM_None },
{ Opcode(0xee), ModRM_None, IMM_None },
{ Opcode(0xef), ModRM_None, IMM_None },
// 0xF0 PREFIX LOCK
// 0xF1 Undefined
// 0xF2 PREFIX REPNE
// 0xF3 PREFIX REPNE
{ Opcode(0xf4), ModRM_None, IMM_None },
{ Opcode(0xf5), ModRM_None, IMM_None },

{ Opcode(0xf6), ModRM_Opcode(0), IMM_8 },
{ Opcode(0xf6), ModRM_Opcode(1), IMM_8 },
{ Opcode(0xf6), ModRM_Opcode(2), IMM_None },
{ Opcode(0xf6), ModRM_Opcode(3), IMM_None },
{ Opcode(0xf6), ModRM_Opcode(4), IMM_None },
{ Opcode(0xf6), ModRM_Opcode(5), IMM_None },
{ Opcode(0xf6), ModRM_Opcode(6), IMM_None },
{ Opcode(0xf6), ModRM_Opcode(7), IMM_None },

{ Opcode(0xf7), ModRM_Opcode(0), IMM_32 },
{ Opcode(0xf7), ModRM_Opcode(1), IMM_32 },
{ Opcode(0xf7), ModRM_Opcode(2), IMM_None },
{ Opcode(0xf7), ModRM_Opcode(3), IMM_None },
{ Opcode(0xf7), ModRM_Opcode(4), IMM_None },
{ Opcode(0xf7), ModRM_Opcode(5), IMM_None },
{ Opcode(0xf7), ModRM_Opcode(6), IMM_None },
{ Opcode(0xf7), ModRM_Opcode(7), IMM_None },

{ Opcode(0xf8), ModRM_None, IMM_None },
{ Opcode(0xf9), ModRM_None, IMM_None },
{ Opcode(0xfa), ModRM_None, IMM_None },
{ Opcode(0xfb), ModRM_None, IMM_None },
{ Opcode(0xfc), ModRM_None, IMM_None },
{ Opcode(0xfd), ModRM_None, IMM_None },
{ Opcode(0xfe), ModRM_32, IMM_None },
{ Opcode(0xff), ModRM_32, IMM_None },

{ Opcode2(0x0f, 0x00), ModRM_Opcode(0), IMM_None },
{ Opcode2(0x0f, 0x00), ModRM_Opcode(1), IMM_None },
{ Opcode2(0x0f, 0x00), ModRM_Opcode(2), IMM_None },
{ Opcode2(0x0f, 0x00), ModRM_Opcode(3), IMM_None },
{ Opcode2(0x0f, 0x00), ModRM_Opcode(4), IMM_None },
{ Opcode2(0x0f, 0x00), ModRM_Opcode(5), IMM_None },

{ Opcode2(0x0f, 0x01), ModRM_Opcode(0), IMM_None },
{ Opcode2(0x0f, 0x01), ModRM_Opcode(1), IMM_None },
{ Opcode2(0x0f, 0x01), ModRM_Opcode(2), IMM_None },
{ Opcode2(0x0f, 0x01), ModRM_Opcode(3), IMM_None },
{ Opcode2(0x0f, 0x01), ModRM_Opcode(4), IMM_None },
{ Opcode2(0x0f, 0x01), ModRM_Opcode(6), IMM_None },
{ Opcode2(0x0f, 0x01), ModRM_Opcode(7), IMM_None },

{ Opcode2(0x0f, 0x02), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x03), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x05), ModRM_None, IMM_None },
{ Opcode2(0x0f, 0x06), ModRM_None, IMM_None },
{ Opcode2(0x0f, 0x07), ModRM_None, IMM_None },
{ Opcode2(0x0f, 0x08), ModRM_None, IMM_None },
{ Opcode2(0x0f, 0x09), ModRM_None, IMM_None },
{ Opcode2(0x0f, 0x0b), ModRM_None, IMM_None },
{ Opcode2(0x0f, 0x10), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x11), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x12), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x13), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x14), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x15), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x16), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x17), ModRM_32, IMM_None },

{ Opcode2(0x0f, 0x18), ModRM_Opcode(0), IMM_None },
{ Opcode2(0x0f, 0x18), ModRM_Opcode(1), IMM_None },
{ Opcode2(0x0f, 0x18), ModRM_Opcode(2), IMM_None },
{ Opcode2(0x0f, 0x18), ModRM_Opcode(3), IMM_None },

{ Opcode2(0x0f, 0x1f), ModRM_Opcode(0), IMM_None },

{ Opcode2(0x0f, 0x20), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x21), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x22), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x23), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x28), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x29), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x2a), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x2b), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x2c), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x2d), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x2e), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x2f), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x30), ModRM_None, IMM_None },
{ Opcode2(0x0f, 0x31), ModRM_None, IMM_None },
{ Opcode2(0x0f, 0x32), ModRM_None, IMM_None },
{ Opcode2(0x0f, 0x33), ModRM_None, IMM_None },
{ Opcode2(0x0f, 0x34), ModRM_None, IMM_None },
{ Opcode2(0x0f, 0x35), ModRM_None, IMM_None },
{ Opcode2(0x0f, 0x37), ModRM_None, IMM_None },

{ Opcode3(0x0f, 0x38, 0x00), ModRM_32, IMM_None },
{ Opcode3(0x0f, 0x38, 0x01), ModRM_32, IMM_None },
{ Opcode3(0x0f, 0x38, 0x02), ModRM_32, IMM_None },
{ Opcode3(0x0f, 0x38, 0x03), ModRM_32, IMM_None },
{ Opcode3(0x0f, 0x38, 0x04), ModRM_32, IMM_None },
{ Opcode3(0x0f, 0x38, 0x05), ModRM_32, IMM_None },
{ Opcode3(0x0f, 0x38, 0x06), ModRM_32, IMM_None },
{ Opcode3(0x0f, 0x38, 0x07), ModRM_32, IMM_None },
{ Opcode3(0x0f, 0x38, 0x08), ModRM_32, IMM_None },
{ Opcode3(0x0f, 0x38, 0x09), ModRM_32, IMM_None },
{ Opcode3(0x0f, 0x38, 0x0a), ModRM_32, IMM_None },
{ Opcode3(0x0f, 0x38, 0x0b), ModRM_32, IMM_None },
{ Opcode3(0x0f, 0x38, 0x10), ModRM_32, IMM_None },
{ Opcode3(0x0f, 0x38, 0x1c), ModRM_32, IMM_None },
{ Opcode3(0x0f, 0x38, 0x1d), ModRM_32, IMM_None },
{ Opcode3(0x0f, 0x38, 0x1e), ModRM_32, IMM_None },
{ Opcode3(0x0f, 0x38, 0xf0), ModRM_32, IMM_None },
{ Opcode3(0x0f, 0x38, 0xf1), ModRM_32, IMM_None },
{ Opcode3(0x0f, 0x3a, 0x0f), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x40), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x41), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x42), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x43), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x44), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x45), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x46), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x47), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x48), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x49), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x4a), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x4b), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x4c), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x4d), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x4e), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x4f), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x50), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x51), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x52), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x53), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x54), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x55), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x56), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x57), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x58), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x59), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x5a), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x5b), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x5c), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x5d), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x5e), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x5f), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x60), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x61), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x62), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x63), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x64), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x65), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x66), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x67), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x68), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x69), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x6a), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x6b), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x6c), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x6d), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x6e), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x6f), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x70), ModRM_32, IMM_8 },
{ Opcode2(0x0f, 0x71), ModRM_Opcode(2), IMM_8 },
{ Opcode2(0x0f, 0x71), ModRM_Opcode(4), IMM_8 },
{ Opcode2(0x0f, 0x71), ModRM_Opcode(6), IMM_8 },
{ Opcode2(0x0f, 0x72), ModRM_Opcode(2), IMM_8 },
{ Opcode2(0x0f, 0x72), ModRM_Opcode(4), IMM_8 },
{ Opcode2(0x0f, 0x72), ModRM_Opcode(6), IMM_8 },
{ Opcode2(0x0f, 0x73), ModRM_Opcode(2), IMM_8 },
{ Opcode2(0x0f, 0x73), ModRM_Opcode(4), IMM_8 },
{ Opcode2(0x0f, 0x73), ModRM_Opcode(6), IMM_8 },
{ Opcode2(0x0f, 0x74), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x75), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x76), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x77), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x78), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x79), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x7e), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x7f), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0x80), ModRM_None, REL_32 },
{ Opcode2(0x0f, 0x81), ModRM_None, REL_32 },
{ Opcode2(0x0f, 0x82), ModRM_None, REL_32 },
{ Opcode2(0x0f, 0x83), ModRM_None, REL_32 },
{ Opcode2(0x0f, 0x84), ModRM_None, REL_32 },
{ Opcode2(0x0f, 0x85), ModRM_None, REL_32 },
{ Opcode2(0x0f, 0x86), ModRM_None, REL_32 },
{ Opcode2(0x0f, 0x87), ModRM_None, REL_32 },
{ Opcode2(0x0f, 0x88), ModRM_None, REL_32 },
{ Opcode2(0x0f, 0x89), ModRM_None, REL_32 },
{ Opcode2(0x0f, 0x8a), ModRM_None, REL_32 },
{ Opcode2(0x0f, 0x8b), ModRM_None, REL_32 },
{ Opcode2(0x0f, 0x8c), ModRM_None, REL_32 },
{ Opcode2(0x0f, 0x8d), ModRM_None, REL_32 },
{ Opcode2(0x0f, 0x8e), ModRM_None, REL_32 },
{ Opcode2(0x0f, 0x8f), ModRM_None, REL_32 },
{ Opcode2(0x0f, 0x90), ModRM_Opcode(0), IMM_None },
{ Opcode2(0x0f, 0x91), ModRM_Opcode(0), IMM_None },
{ Opcode2(0x0f, 0x92), ModRM_Opcode(0), IMM_None },
{ Opcode2(0x0f, 0x93), ModRM_Opcode(0), IMM_None },
{ Opcode2(0x0f, 0x94), ModRM_Opcode(0), IMM_None },
{ Opcode2(0x0f, 0x95), ModRM_Opcode(0), IMM_None },
{ Opcode2(0x0f, 0x96), ModRM_Opcode(0), IMM_None },
{ Opcode2(0x0f, 0x97), ModRM_Opcode(0), IMM_None },
{ Opcode2(0x0f, 0x98), ModRM_Opcode(0), IMM_None },
{ Opcode2(0x0f, 0x99), ModRM_Opcode(0), IMM_None },
{ Opcode2(0x0f, 0x9a), ModRM_Opcode(0), IMM_None },
{ Opcode2(0x0f, 0x9b), ModRM_Opcode(0), IMM_None },
{ Opcode2(0x0f, 0x9c), ModRM_Opcode(0), IMM_None },
{ Opcode2(0x0f, 0x9d), ModRM_Opcode(0), IMM_None },
{ Opcode2(0x0f, 0x9e), ModRM_Opcode(0), IMM_None },
{ Opcode2(0x0f, 0x9f), ModRM_Opcode(0), IMM_None },
{ Opcode2(0x0f, 0xa0), ModRM_None, IMM_None },
{ Opcode2(0x0f, 0xa1), ModRM_None, IMM_None },
{ Opcode2(0x0f, 0xa2), ModRM_None, IMM_None },
{ Opcode2(0x0f, 0xa3), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xa4), ModRM_32, IMM_8 },
{ Opcode2(0x0f, 0xa5), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xa8), ModRM_None, IMM_None },
{ Opcode2(0x0f, 0xa9), ModRM_None, IMM_None },
{ Opcode2(0x0f, 0xaa), ModRM_None, IMM_None },
{ Opcode2(0x0f, 0xab), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xac), ModRM_32, IMM_8 },
{ Opcode2(0x0f, 0xad), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xae), ModRM_Opcode(0), IMM_None },
{ Opcode2(0x0f, 0xae), ModRM_Opcode(1), IMM_None },
{ Opcode2(0x0f, 0xae), ModRM_Opcode(2), IMM_None },
{ Opcode2(0x0f, 0xae), ModRM_Opcode(3), IMM_None },
{ Opcode2(0x0f, 0xae), ModRM_Opcode(4), IMM_None },
{ Opcode2(0x0f, 0xae), ModRM_Opcode(5), IMM_None },
{ Opcode2(0x0f, 0xae), ModRM_Opcode(6), IMM_None },
{ Opcode2(0x0f, 0xae), ModRM_Opcode(7), IMM_None },
{ Opcode2(0x0f, 0xaf), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xb1), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xb2), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xb3), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xb4), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xb5), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xb6), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xb7), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xb9), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xba), ModRM_Opcode(4), IMM_8 },
{ Opcode2(0x0f, 0xba), ModRM_Opcode(5), IMM_8 },
{ Opcode2(0x0f, 0xba), ModRM_Opcode(6), IMM_8 },
{ Opcode2(0x0f, 0xba), ModRM_Opcode(7), IMM_8 },
{ Opcode2(0x0f, 0xbb), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xbc), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xbd), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xbe), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xbf), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xc0), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xc1), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xc2), ModRM_32, IMM_8 },
{ Opcode2(0x0f, 0xc3), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xc4), ModRM_32, IMM_8 },
{ Opcode2(0x0f, 0xc5), ModRM_32, IMM_8 },
{ Opcode2(0x0f, 0xc6), ModRM_32, IMM_8 },
{ Opcode2(0x0f, 0xc7), ModRM_Opcode(1), IMM_None },
{ Opcode2(0x0f, 0xc7), ModRM_Opcode(6), IMM_None },
{ Opcode2(0x0f, 0xc7), ModRM_Opcode(7), IMM_None },
{ Opcode2(0x0f, 0xc8), ModRM_None, IMM_None },
{ Opcode2(0x0f, 0xc9), ModRM_None, IMM_None },
{ Opcode2(0x0f, 0xca), ModRM_None, IMM_None },
{ Opcode2(0x0f, 0xcb), ModRM_None, IMM_None },
{ Opcode2(0x0f, 0xcc), ModRM_None, IMM_None },
{ Opcode2(0x0f, 0xcd), ModRM_None, IMM_None },
{ Opcode2(0x0f, 0xce), ModRM_None, IMM_None },
{ Opcode2(0x0f, 0xcf), ModRM_None, IMM_None },
{ Opcode2(0x0f, 0xd1), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xd2), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xd3), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xd4), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xd5), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xd7), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xd8), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xd9), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xda), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xdb), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xdc), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xdd), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xde), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xdf), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xe0), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xe1), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xe2), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xe3), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xe4), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xe5), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xe7), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xe8), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xe9), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xea), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xeb), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xec), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xed), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xee), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xef), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xf1), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xf2), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xf3), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xf4), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xf5), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xf6), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xf7), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xf8), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xf9), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xfa), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xfb), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xfc), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xfd), ModRM_32, IMM_None },
{ Opcode2(0x0f, 0xfe), ModRM_32, IMM_None },
};

uint8_t prefixes[]
{
	0x26,
	0x2E,
	0x36,
	0x3E,
	0x64,
	0x65,
	0x66,
	0x67,
	0x9B,
	0xF0,
	0xF2,
	0xF3,
};

int GetOpcodeLength(int16_t opcode1, int16_t opcode2, int16_t opcode3)
{
	int length = 0;

	if (opcode1 != -1)
	{
		length++;
	}
	else
		return length;

	if (opcode2 != -1)
	{
		length++;
	}
	else
		return length;

	if (opcode3 != -1)
	{
		length++;
	}
	else
		return length;

	return length;
}

int GetOpcodeLength(Instruction_s* instruction)
{
	return GetOpcodeLength(instruction->opcode1, instruction->opcode2, instruction->opcode3);
}

int GetRelatedOpcodeLength(Instruction_s* instruction)
{
	return GetOpcodeLength(instruction->relatedRelative1, instruction->relatedRelative2, instruction->relatedRelative3);
}

bool IsPrefix(uint8_t opcode)
{
	for (int i = 0; i < sizeof(prefixes) / sizeof(uint8_t); i++)
	{
		if (opcode == prefixes[i])
			return true;
	}

	return false;
}

int ModRM_32_GetAdditionalLength(uint8_t* pos)
{
	int length = 0;
	int mod = (*pos & 0xC0) >> 6;
	int rm = *pos & 0x7;

	if (mod != 0x03 && rm == 0x04)
		length++; // SIB-Byte

	if (mod == 0x00 && rm == 0x05)
		length += 4; // displacement 32bits
	else if (mod == 0x01)
		length++; // displacement 8bits
	else if (mod == 0x02)
		length += 4; // displacement 32bits

	return length;
}

Instruction_s* GetInstruction(char* pos, uint32_t* prefixLength)
{
	int prefixLengthValue;
	uint8_t* currentPos;

	int16_t opcode1, opcode2, opcode3;
	uint8_t* modrm;
	int16_t rmOpcode;

	Instruction_s* foundInstruction = nullptr;

	prefixLengthValue = 0;
	currentPos = (uint8_t*)pos;

	while (1)
	{
		for (int iteration = 0; iteration < 3; iteration++)
		{
			rmOpcode = -1;
			opcode1 = currentPos[0];
			modrm = &currentPos[1];

			if (iteration >= 1)
			{
				opcode2 = currentPos[1];
				modrm++;
			}
			else
				opcode2 = -1;

			if (iteration >= 2)
			{
				opcode3 = currentPos[2];
				modrm++;
			}
			else
				opcode3 = -1;

			for (int i = 0; i < sizeof(instructions) / sizeof(Instruction_s); i++)
			{
				if (instructions[i].opcode1 == opcode1
					&& instructions[i].opcode2 == opcode2
					&& instructions[i].opcode3 == opcode3)
				{
					if (instructions[i].modrm & ModRM_Opcoded)
					{
						if (rmOpcode == -1)
							rmOpcode = (*modrm & 0x38) >> 3;

						if ((instructions[i].modrm & ModRM_OPCODE_MASK) != rmOpcode)
							continue;
					}

					foundInstruction = &instructions[i];
				}
			}
		}

		if (foundInstruction || !IsPrefix(*currentPos))
			break;

		// First byte is a prefix. Skip it and check again afterwards.
		currentPos++;
		prefixLengthValue++;
	}

	if (prefixLength)
		*prefixLength = foundInstruction ? prefixLengthValue : 0;

	return foundInstruction;
}

int GetInstructionLength(Instruction_s* instruction, int prefixLength, char* pos)
{
	int currentLength;
	uint8_t* currentPos;

	if (instruction == nullptr || pos == nullptr)
		return -1;

	currentPos = (uint8_t*)pos + prefixLength;
	currentLength = prefixLength;

	int opcodeLength = GetOpcodeLength(instruction);

	currentPos += opcodeLength;
	currentLength += opcodeLength;

	if (instruction->modrm != ModRM_None)
	{
		currentLength++;

		switch (instruction->modrm & ModRM_TABLE_MASK)
		{
		case ModRM_32:
			currentLength += ModRM_32_GetAdditionalLength(currentPos);
			break;
		}
	}

	switch (instruction->imm)
	{
	case IMM_None:
		break;

	case REL_8:
	case IMM_8:
		currentLength++;
		break;

	case IMM_16:
		currentLength += 2;
		break;

	case IMM_8_16:
		currentLength += 3;
		break;

	case REL_32:
	case IMM_32:
		currentLength += 4;
		break;

	case IMM_16_32:
		currentLength += 6;
		break;

	default:
		assert(false);
		break;
	}

	return currentLength;
}

InstructionLength GetInstructionLength(char* pos)
{
	uint32_t prefixLength;
	Instruction_s* instruction;
	InstructionLength result;

	result.length = -1;
	result.extendedLength = -1;

	instruction = GetInstruction(pos, &prefixLength);

	if (instruction == nullptr)
		return result;

	result.length = GetInstructionLength(instruction, prefixLength, pos);
	if (instruction->imm == REL_8
		&& instruction->relatedRelative1 >= 0
		&& instruction->relatedRelative2 >= -1
		&& instruction->relatedRelative3 >= -1)
	{
		// If the instruction has a relative 8bit offset and a replacement with 32bit offset then we have to use an updated instruction to match the target of the instruction
		result.extendedLength = result.length + 3;

		// Get rid of the current opcode length
		result.extendedLength -= GetOpcodeLength(instruction);

		// Add the opcode length of the new opcode
		result.extendedLength += GetRelatedOpcodeLength(instruction);
	}
	else
	{
		result.extendedLength = result.length;
	}

	return result;
}

InstructionLength CopyInstruction(char* source, char* dest)
{
	uint32_t prefixLength;
	Instruction_s* instruction;
	InstructionLength result;

	result.length = -1;
	result.extendedLength = -1;

	instruction = GetInstruction(source, &prefixLength);

	if (instruction == nullptr)
		return result;

	result.length = GetInstructionLength(instruction, prefixLength, source);
	result.extendedLength = result.length;

	if (instruction->imm == REL_8)
	{
		if (instruction->relatedRelative1 < 0
			|| instruction->relatedRelative2 < -1
			|| instruction->relatedRelative3 < -1)
		{
			assert(false);
			result.length = -1;
			return result;
		}

		uint32_t offsetSource = 0;
		uint32_t opcodeLengthSource = 0;
		uint32_t offsetDest = 0;
		uint32_t destAddr = (uint32_t)source + *((uint8_t*)(source + result.length - 1));

		if (prefixLength > 0)
		{
			memcpy(dest + offsetDest, source + offsetSource, prefixLength);
			offsetDest += prefixLength;
			offsetSource += prefixLength;
		}

		opcodeLengthSource = GetOpcodeLength(instruction);
		offsetSource += opcodeLengthSource;

		dest[offsetDest++] = instruction->relatedRelative1;

		if (instruction->relatedRelative2 >= 0)
		{
			dest[offsetDest++] = instruction->relatedRelative2;

			if (instruction->relatedRelative3 >= 0)
				dest[offsetDest++] = instruction->relatedRelative3;
		}

		uint32_t middlePartLength = result.length - prefixLength - opcodeLengthSource - 1;
		if (middlePartLength > 0)
		{
			memcpy(dest + offsetDest, source + offsetSource, middlePartLength);
			offsetDest += middlePartLength;
			offsetSource += middlePartLength;
		}

		*(uint32_t*)(dest + offsetDest) = destAddr - ((uint32_t)dest + offsetDest);

		// - 1 + 4
		result.extendedLength = result.length + 3;
	}
	else if (instruction->imm == REL_32)
	{
		uint32_t destAddr = (uint32_t)source + *((uint32_t*)(source + result.length - 4));
		memcpy(dest, source, result.length);

		*(uint32_t*)(dest + result.length - 4) = destAddr - (uint32_t)dest;
	}
	else
	{
		memcpy(dest, source, result.length);
	}

	return result;
}