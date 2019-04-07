#pragma once
#include <cstdint>

typedef int32_t ResultCode;

#define CALC_E_DIVIDEBYZERO				( ( uint32_t ) 0x80000000 )

#define CALC_E_DOMAIN					( ( uint32_t ) 0x80000001 )

#define CALC_E_INDEFINITE				( ( uint32_t ) 0x80000002 )

#define CALC_E_POSINFINITY				( ( uint32_t ) 0x80000003 )

#define CALC_E_NEGINFINITY				( ( uint32_t ) 0x80000004 )

#define CALC_E_INVALIDRANGE				( ( uint32_t ) 0x80000006 )

#define CALC_E_OUTOFMEMORY				( ( uint32_t ) 0x80000007 )

#define CALC_E_OVERFLOW					( ( uint32_t ) 0x80000008 )

#define CALC_E_NORESULT					( ( uint32_t ) 0x80000009 )