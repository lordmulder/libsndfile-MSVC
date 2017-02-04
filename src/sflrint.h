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
 * Workaround for forbiddingly SLOW implementation of lrint() and lrintf() functions in MSVC
 * The following inline implemenatation was adapted from Qt's qRound() function
*  Runs about ~32x faster (on my test system), compared to MSVC's built-in lrint() function!
 */
#if defined(_MSC_VER) && (_MSC_VER)
#define _SF_LRINT_MSVC(T) \
((d >= ((T)0.0)) ? ((long)(d + ((T)0.5))) : ((long)(d - ((long)(d - 1)) + ((T)0.5))) + ((long)(d - 1)))
static __inline long SF_lrint(double d) { return _SF_LRINT_MSVC(double); }
static __inline long SF_lrintf(float d) { return _SF_LRINT_MSVC(float);  }
#else
#define SF_lrint(X)  lrint((X))
#define SF_lrintf(X) lrintf((X))
#endif

/*Inline assembly versions *not* currently used!
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
static __inline long long int SF_llrint(double flt)
{
	long long int intgr;
	_controlfp_s(NULL, _RC_NEAR, _MCW_RC);
	_asm
	{
		fld flt
		fistp intgr
	};
	return intgr;
}
static __inline long long int SF_llrintf(float flt)
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
