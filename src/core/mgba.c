#include <tonc_types.h>

#include "mgba.h"
#include "printf.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define REG_DEBUG_ENABLE (vu16*)0x4FFF780
#define REG_DEBUG_FLAGS (vu16*)0x4FFF700
#define REG_DEBUG_STRING (char*)0x4FFF600

void mgba_printf(int level, const char* ptr, ...)
{
#if !MODERN
	va_list args;
	level &= 0x7;
	va_start(args, ptr);
	vsnprintf(REG_DEBUG_STRING, 0x100, ptr, args);
	va_end(args);
	*REG_DEBUG_FLAGS = level | 0x100;
#endif
}

bool mgba_open(void)
{
	*REG_DEBUG_ENABLE = 0xC0DE;
	return *REG_DEBUG_ENABLE == 0x1DEA;
}

void mgba_close(void)
{
	*REG_DEBUG_ENABLE = 0;
}
