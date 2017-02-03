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

/*
 * Workaround for SLOW implementation of lrint() and lrintf() functions in MSVC
 * The following inline assembly is about 168x faster on my test system, compared to built-in MSVC functions!
 */
#if defined(_MSC_VER) && (_MSC_VER)
#include <float.h>
static __inline long int SF_lrint(double flt)
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
static __inline long int SF_lrintf(float flt)
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
#else
#define SF_lrint(X)  lrint((X))
#define SF_lrintf(X) lrintf((X))
#endif

/*static __inline long long int SF_llrint(double flt)
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

/*static __inline long long int SF_llrintf(float flt)
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
