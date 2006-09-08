/*
 * ITVal: The IPTables Firewall Validator Copyright (C) 2004 Robert
 * Marmorstein
 * 
 * This program is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with this program; if not, write to the Free Software Foundation, Inc., 
 * 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. A full-text
 * version is located in the LICENSE file distributed with this utility.
 * 
 * You may contact the author at rmmarm@wm.edu or by sending mail to:
 * 
 * Robert Marmorstein Department of Computer Science College of William
 * and Mary Williamsburg, VA 23185 
 */

#include "ranges.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

// Turn a address/mask pair into a (low, high) pair of integers.  
// Store them in the address_range struct "ar".

void create_range(unsigned int *addy, unsigned int mask, address_range * ar,
                  int invert)
{
   unsigned int low;
   unsigned int high;
   unsigned int mval;

   if (mask == 0) {
      if (invert) {
         ar->low = 1;
         ar->high = 0;
         return;
      }
      ar->low = 0;
      ar->high = UINT_MAX;
      return;
   }
   mval = 0xFFFFFFFF << (32 - mask);

   low = addy[0] * 256 * 256 * 256;
   low += addy[1] * 256 * 256;
   low += addy[2] * 256;
   low += addy[3];

   low = low & mval;
   high = low | ~mval;

   if (!invert) {
      ar->low = low;
      ar->high = high;
   }
   else {
      ar->next = new address_range;

      if (low == 0) {
         ar->low = 1;
         ar->high = 0;
      }
      else {
         ar->low = 0;
         ar->high = low - 1;
      }

      if (high == UINT_MAX) {
         ar->next->low = 1;
         ar->next->high = 0;
      }
      else {
         ar->next->low = high + 1;
         ar->next->high = UINT_MAX;
      }
      //printf("low: %u high:%u %u-%u %u-%u \n", low, high, ar->low, ar->high, ar->next->low, ar->next->high);
   }
}

// Convert a net/mask string into a (low, high) pair describing
// a range of IP addresses
void ConvertARange(char *range, address_range * ar)
{
   int invert;                            // Should we negate the address?

   // The elements of the IP address
   char bytes[4][256];

   // The mask
   char mask[256];

   // The value of each IP element
   unsigned int vals[4];

   // The integer value of the mask.
   unsigned int mval;

   // The current character to be processed
   char *ch;

   // The beginning of the string
   char *start;

   // Number of IP elements processed
   int num;

   // Length of the string
   int length;

   length = strlen(range);

   // Start at the beginning
   invert = 0;

   ch = range;
   start = range;

   if (*ch == '!') {
      invert = 1;
      ch++;
      start++;
   }
   num = 0;
   // Grab the four elements
   while (num < 4) {
      while (ch - range < length && *ch != '.' && *ch != ' ' && *ch != '/') {
         (bytes[num])[ch - start] = *ch;
         ch++;
      }
      (bytes[num])[ch - start] = '\0';
      if (*ch == '.')           // Advance past a dot
         ch++;

      // Convert the element string to an integer
      vals[num] = atoi(bytes[num]);
      num++;
      start = ch;
   }
   // If a mask has been specified, grab it.  Otherwise, it defaults to
   // 32 (all bits significant).

   if (*ch == '/') {
      ch++;                     // Advance past '/'
      start = ch;
      while (ch - range < length && *ch != ' ') {
         mask[ch - start] = *ch;
         ch++;
      }
      mask[ch - start] = '\0';
      // Convert the mask string to an integer
      mval = atoi(mask);
   }
   else {
      mval = 32;
   }
   // Now turn the mask/val pair into a (low, high) pair.
   create_range(vals, mval, ar, invert);
}
