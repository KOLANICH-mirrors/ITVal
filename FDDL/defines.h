
/*
FDDL: A Free Decision Diagram Library
Copyright (C) 2004 Robert Marmorstein

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
A full-text version is located in the LICENSE file distributed with this
utility.

You may contact the author at rmmarm@wm.edu or by sending mail to:

Robert Marmorstein
Department of Computer Science
College of William and Mary
Williamsburg, VA 23185
*/

#ifndef __DEFINES_H
#   define __DEFINES_H
/// Standard MAX "macro".
#   define MAX(X,Y) ((X>Y)?X:Y)
#   define MAX3(X,Y,Z) ((X>Y && X>Z)?X:(Y>X && Y>Z)?Y:Z)
/// Standard MIN "macro".
template < class T > inline T MIN(T X, T Y)
{
	return ((X < Y) ? X : Y);
}

/// SWAP "macro".
template < class T > inline void SWAP(T & x, T & y)
{
	T       tmp = x;

	x = y;
	y = tmp;
}

#   include <assert.h>
#   include <stdlib.h>
#   define EXIT(X) exit(X)
#   define ASSERT(X) assert(X)
#endif
