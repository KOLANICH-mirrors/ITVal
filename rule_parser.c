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

#include <string.h>
#include "rules.h"
#include <stdlib.h>

// Parse a TCP or UDP port value from a string into parts.
// Store the protocol name (tcp or udp) in "which"
// Store the port list in "port"
void BreakPort(char *word, char *which, char *port)
{
	// Current character
	char   *ch;

	// Length of the string
	int     length;

	length = strlen(word);

	// Start at the beginning of the string
	ch = word;

	// The protocol precedes the colon.
	while (ch - word < length && *ch != ':') {
		which[ch - word] = *ch;
		ch++;
	}
	which[ch - word] = '\0';
	ch++;								  // Advance past ':'

	// Now grab the list of ports.
	word = ch;
	while (ch - word < length) {
		port[ch - word] = *ch;
		ch++;
	}
	port[ch - word] = '\0';
}

// Convert the textual state information into an integer.
void BreakState(char *word, int *state)
{
	// The current word to examine
	char    curword[4096];

	// The current character to copy
	char   *ch;

	// The length of the string
	int     length;

	length = strlen(word);

	// Start at the beginning.
	ch = word;
	// Initially assume no state is mentioned.
	*state = 0;
	while (ch - word < length) {
		// Grab each element of the comma seperated list.
		while (ch - word < length && *ch != ',') {
			curword[ch - word] = *ch;
			ch++;
		}
		curword[ch - word] = '\0';

		// Now, "or in" the value for the state it matches.
		if (!strncmp(curword, "INVALID", 4096))
			*state |= INVALID;
		else if (!strncmp(curword, "ESTABLISHED", 4096))
			*state |= ESTABLISHED;
		else if (!strncmp(curword, "NEW", 4096))
			*state |= NEW;
		else if (!strncmp(curword, "RELATED", 4096))
			*state |= RELATED;
		ch++;							  // Advance past comma
		word = ch;
		length -= (strlen(curword) + 1);
	}
}

// Convert the textual representation of TCP flags into an array of
// six integers.

void BreakFlags(char *word, int *flags)
{
	char    word1[4096];			  // Flags to examine (Hex string)
	char    word2[4096];			  // Flags that must be set to match 

	// (Hex string)

	int     mask_num;				  // Flags to examine (integer)
	int     val_num;				  // Flags that must be set to match

	// (integer)

	int     mask[6];				  // Boolean array of flags to examine 
	int     value[6];				  // Boolean array of flags that must be set

	char   *ch;						  // Current character to consider.
	int     length;				  // Length of the string.

	int     i;

	length = strlen(word);

	// Start at the beginning of the string
	ch = word;

	while (ch - word < length) {

		ch += 6;
		word = ch;					  // Consume the word "flags"
		length -= 6;

		// Grab the mask part
		while (ch - word < length && *ch != '/') {
			word1[ch - word] = *ch;
			ch++;
		}
		word1[ch - word] = '\0';
		ch++;
		word = ch;
		length -= strlen(word1);

		// Grab the value part.
		while (ch - word < length && *ch != ',') {
			word2[ch - word] = *ch;
			ch++;
		}
		word2[ch - word] = '\0';
		ch++;
	}
	// Parse the two parts into integers
	sscanf(word1, "%x", &mask_num);
	sscanf(word2, "%x", &val_num);

	// Convert the integers into boolean arrays.
	mask[0] = mask_num & 1;
	mask[1] = mask_num & 2;
	mask[2] = mask_num & 4;
	mask[3] = mask_num & 8;
	mask[4] = mask_num & 16;
	mask[5] = mask_num & 32;

	value[0] = val_num & 1;
	value[1] = (val_num & 2) / 2;
	value[2] = (val_num & 4) / 4;
	value[3] = (val_num & 8) / 8;
	value[4] = (val_num & 16) / 16;
	value[5] = (val_num & 32) / 32;

	// For each flag, assign the appropriate value to flags[i].
	// If it's not in the mask, it can have any value.
	// If it IS in the mask, it must have the value specified.
	for (i = 0; i < 6; i++) {
		if (mask[i] == 0) {
			flags[i] = -1;
		}
		else {
			flags[i] = value[i];
		}
	}
}

// Read a rule from the rule file.  Store it in a rule struct.
int ReadRule(rule * newRule, char *line, size_t length)
{
	char   *ch;
   if (line[0]==' ' || line[0]=='\t'){
      newRule->target[0]='\0';
   }
   else{
   	ch = line;
   	line = ch;
   	while ((unsigned) (ch - line) < length && (*ch != ' ' && *ch != '\t')) {
   		newRule->target[ch - line] = *ch;
	   	ch++;
   	}
   	newRule->target[ch - line] = '\0';
	   length -= (ch - line);
   }
	// Consume Whitespace
	line = ch;
	while ((unsigned) (ch - line) < length && (*ch == ' ' || *ch == '\t')) {
		ch++;
	}
	length -= (ch - line);

	// Read protocol field
	line = ch;
	while ((unsigned) (ch - line) < length && (*ch != ' ' && *ch != '\t')) {
		newRule->protocol[ch - line] = *ch;
		ch++;
	}
	newRule->protocol[ch - line] = '\0';
	length -= (ch - line);

	// Consume Whitespace
	line = ch;
	while ((unsigned) (ch - line) < length && (*ch == ' ' || *ch == '\t')) {
		ch++;
	}
	length -= (ch - line);

	// Read opt field
	line = ch;
	while ((unsigned) (ch - line) < length && (*ch != ' ' && *ch != '\t')) {
		newRule->opt[ch - line] = *ch;
		ch++;
	}
	newRule->opt[ch - line] = '\0';
	length -= (ch - line);

	// Consume Whitespace
	line = ch;
	while ((unsigned) (ch - line) < length && (*ch == ' ' || *ch == '\t')) {
		ch++;
	}
	length -= (ch - line);

	// Read source address/mask
	line = ch;
	while ((unsigned) (ch - line) < length && (*ch != ' ' && *ch != '\t')) {
		newRule->source[ch - line] = *ch;
		ch++;
	}
	newRule->source[ch - line] = '\0';
	length -= (ch - line);

	// Consume Whitespace
	line = ch;
	while ((unsigned) (ch - line) < length && (*ch == ' ' || *ch == '\t')) {
		ch++;
	}
	length -= (ch - line);

	// Read dest address/mask
	line = ch;
	while ((unsigned) (ch - line) < length && (*ch != ' ' && *ch != '\t')) {
		newRule->dest[ch - line] = *ch;
		ch++;
	}
	newRule->dest[ch - line] = '\0';
	length -= (ch - line);

	// Consume Whitespace
	line = ch;
	while ((unsigned) (ch - line) < length && (*ch == ' ' || *ch == '\t')) {
		ch++;
	}
	length -= (ch - line);

	// Read extra stuff at the end (ports, state, flags, etc.)
	line = ch;
	while ((unsigned) (ch - line) < length + 1) {
		newRule->info[ch - line] = *ch;
		ch++;
	}
	newRule->info[ch - line] = '\0';
	return 0;
}
