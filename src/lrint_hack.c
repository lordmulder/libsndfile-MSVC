/*
** Copyright (C) 1999-2015 Erik de Castro Lopo <erikd@mega-nerd.com>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation; either version 2.1 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#include "sfconfig.h"

/* Workaround for slow lrint() and lrintf() functions of MSVC */
#if defined(_MSC_VER) && defined(ENABLE_LRINT_HACK) && (ENABLE_LRINT_HACK)
#include <float.h>

long int
SF_lrint(double flt)
{
	int intgr;
	_controlfp(_RC_NEAR, _MCW_RC);
	_asm
	{
		fld flt
		fistp intgr
	};
	return intgr;
}

long int
SF_lrintf(float flt)
{
	int intgr;
	_controlfp(_RC_NEAR, _MCW_RC);
	_asm
	{
		fld flt
		fistp intgr
	};
	return intgr;
}

/*__inline long long int
SF_llrint(double flt)
{
	long long int intgr;
	_controlfp_s(NULL, _RC_NEAR, _MCW_RC);
	_asm
	{
		fld flt
		fistp intgr
	};
	return intgr;
}*/

/*__inline long long int
SF_llrintf(float flt)
{
	long long int intgr;
	_controlfp_s(NULL, _RC_NEAR, _MCW_RC);
	_asm
	{
		fld flt
		fistp intgr
	};
	return intgr;
}*/

#endif //defined(ENABLE_LRINT_HACK) && (ENABLE_LRINT_HACK)
