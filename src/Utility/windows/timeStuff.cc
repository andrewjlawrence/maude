/*

This file is part of the Maude 2 interpreter.

Copyright 1997-2003 SRI International, Menlo Park, CA 94025, USA.
Copyright 2017 Andrew Lawrence.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.

*/

#include "../timeStuff.hh"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdint.h> 

int gettimeofday(struct timeval * tp, struct timezone * tzp)
{
	static const uint64_t EPOCH = ((uint64_t)116444736000000000ULL);
	SYSTEMTIME  systemtime;
	FILETIME    filetime;
	uint64_t    thetime;

	GetSystemTime(&systemtime);
	SystemTimeToFileTime(&systemtime, &filetime);
	thetime = ((uint64_t)filetime.dwLowDateTime);
	thetime += ((uint64_t)filetime.dwHighDateTime) << 32;

	tp->tv_sec = (long)((thetime - EPOCH) / 10000000L);
	tp->tv_usec = (long)(systemtime.wMilliseconds * 1000);
	return 0;
}