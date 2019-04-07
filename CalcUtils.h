#pragma once

#include <cstdint>

using OpCode = uintptr_t;

bool IsOpInRange(OpCode op, uint32_t x, uint32_t y);
bool IsBinOpCode(OpCode opCode);

bool IsUnaryOpCode(OpCode opCode);
bool IsDigitOpCode(OpCode opCode);
bool IsGuiSettingOpCode(OpCode opCode);