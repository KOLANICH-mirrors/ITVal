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

#include <stdlib.h>
#include <stdio.h>
#include "structures.h"
#include "FDDL/mdd.h"
#include "fwlang.tab.h"
#include "firewall.h"

// Limit of 256 address groups
group  *groups[256];
int     num_groups = 0;

// Limit of 256 service groups
service *services[256];
int     num_services = 0;

// A firewall object 
Firewall *FW;

// Link the Firewall Forest to the Query Engine.
void InitializeStructures(Firewall * F)
{
	FW = F;
}

// Given the name of a service, find it in the service array and return
// it.  
// If no such service is found, return NULL.

service *ServiceLookup(char *name)
{
	int     i;

	for (i = 0; i < num_services; i++) {
		if (strncmp(name, services[i]->name, 256) == 0) {
			delete[]name;
			return services[i];
		}
	}
	printf("Service %s not found.\n", name);
	exit(-1);
	return NULL;
}

// Given the name of a group, find it in the group array and return it.
// If no such group is found, return NULL.
group  *GroupLookup(char *name)
{
	int     i;

	for (i = 0; i < num_groups; i++) {
		if (strncmp(name, groups[i]->name, 256) == 0) {
			delete[]name;
			return groups[i];
		}
	}
	return NULL;
}

// Construct a new Service, consisting of the single port p;
service *BuildServiceFromPort(port * p)
{
	service *s;
	char    tmp[256];

	s = new service;
	s->list = p;
	sprintf(tmp, "Service %d", p->val);
	strncpy(s->name, tmp, 256);
	s->named = 0;
	return s;
}

// Construct a new Service, consisting of the single port p;
group  *BuildGroupFromAddress(address * a)
{
	group  *g;
	char    tmp[256];

	g = new group;
	g->list = a;
	sprintf(tmp, "Group %d.%d.%d.%d", a->val[0], a->val[1], a->val[2],
			  a->val[3]);
	strncpy(g->name, tmp, 256);
	g->named = 0;
	return g;
}

// Given a string containing the port number, return its value as an
// integer.
port   *ParsePort(char *str)
{
	port   *newPort;

	newPort = new port;
	if (!newPort) {
		printf("Failed to allocate memory for port %s\n", str);
		return NULL;
	}
	newPort->next = NULL;
	if (str[0] == '*') {
		newPort->val = -1;
	}
	else if (sscanf(str, "%d", &newPort->val) == 0) {
		printf("\nInvalid port: %s\n", str);
		delete  newPort;

		return NULL;
	}
	delete[]str;
	return newPort;
}

// Convert the string representation of an address into an address
// struct.
address *ParseAddr(char *val1, char *val2, char *val3, char *val4)
{
	address *newAddr;

	newAddr = new address;
	if (!newAddr) {
		printf("Failed to allocate memory for address %s.%s.%s.%s\n",
				 val1 != NULL ? val1 : "*",
				 val2 != NULL ? val2 : "*",
				 val3 != NULL ? val3 : "*", val4 != NULL ? val4 : "*");
		return NULL;
	}
	if (val1 == NULL || val1[0] == '*')
		newAddr->val[0] = -1;
	else {
		sscanf(val1, "%d", &newAddr->val[0]);
	}
	delete[]val1;
	if (val2 == NULL || val2[0] == '*')
		newAddr->val[1] = -1;
	else {
		sscanf(val2, "%d", &newAddr->val[1]);
	}
	delete[]val2;
	if (val3 == NULL || val3[0] == '*')
		newAddr->val[2] = -1;
	else {
		sscanf(val3, "%d", &newAddr->val[2]);
	}
	delete[]val3;
	if (val4 == NULL || val4[0] == '*')
		newAddr->val[3] = -1;
	else {
		sscanf(val4, "%d", &newAddr->val[3]);
	}
	delete[]val4;
	newAddr->next = NULL;
	return newAddr;
}

// Create a "condition" object representing the set of all logged
// packets.
condition *GetLoggedCondition()
{
	condition *sc;

	sc = new condition;
	FW->FWForest->Attach(sc->h, FW->ForwardLog.index);	// Change to take
	// input chain
	// into account.
	return sc;
}

// Create a condition object representing the set of 
// ip addresses in group g.
// If op is 0, they are stored as source addresses.
// If op is 1, they are stored as destination addresses.
condition *BuildConditionFromGroup(group * g, int op)
{

	condition *sc;
	int    *low;
	int    *high;
	address *prev;
	address *cur;
	int     i;

	low = new int[21];
	high = new int[21];

	sc = new condition;

	cur = g->list;
	while (cur != NULL) {
		// Initialize all elements of the tuple to [0-MAX]
		for (i = 20; i >= 1; i--) {
			low[i] = 0;
			high[i] = FW->FWForest->GetMaxVal(i);
		}
		// If it's a source address group, copy the values into positions
		// 17 through 20.
		if (op == 0) {
			for (i = 20; i > 16; i--) {
				low[i] = cur->val[20 - i];
				high[i] = cur->val[20 - i];
				if (cur->val[20 - i] < 0) {
					low[i] = 0;
					high[i] = FW->FWForest->GetMaxVal(i);
				}
			}
			// If it's a destination address group, copy them into
			// positions
			// 13 through 16.
		}
		else {
			for (i = 16; i > 12; i--) {
				low[i] = cur->val[16 - i];
				high[i] = cur->val[16 - i];
				if (cur->val[16 - i] < 0) {
					low[i] = 0;
					high[i] = FW->FWForest->GetMaxVal(i);
				}
			}
		}
		// 1 means in the query, 0 means not in the query.
		high[0] = low[0] = 1;

		// If this is the first address, we use MakeMDDFromTuple
		// Otherwise, we use Assign.
		if (sc->h.index == -1)
			FW->FWForest->MakeMDDFromTuple(low, high, sc->h);
		else
			FW->FWForest->Assign(sc->h, low, high, sc->h);
		prev = cur;
		cur = cur->next;
		if (g->named == 0) {
			delete  prev;
		}
	}
	delete[]high;
	delete[]low;
	if (g->named == 0)
		delete  g;

	return sc;
}

// Create a condition object representing the set of 
// TCP or UDP ports in service s.
// If op is 0, they are stored as source ports.
// If op is 1, they are stored as destination ports.
condition *BuildConditionFromService(service * s, int op)
{
	condition *sc;
	int    *low;
	int    *high;
	port   *cur;
	port   *prev;
	int     i;

	low = new int[21];
	high = new int[21];

	sc = new condition;

	cur = s->list;
	while (cur != NULL) {
		// Initialize all values to [0-MAX]
		for (i = 20; i >= 1; i--) {
			low[i] = 0;
			high[i] = FW->FWForest->GetMaxVal(i);
		}
		// If it's a source port, break it into two bytes
		// and store it in positions 10 and 11.
		if (op == 0) {
			if (cur->val >= 0) {
				high[11] = low[11] = cur->val / 256;
				high[10] = low[10] = cur->val % 256;
			}
		}
		else {
			// If it's a destination port, break it into two bytes
			// and store it in positions 8 and 9.
			if (cur->val >= 0) {
				high[9] = low[9] = cur->val / 256;
				high[8] = low[8] = cur->val % 256;
			}
		}
		// If it's a "BOTH" query, use UDP(1) and TCP(2)
		if (cur->protocol < 0) {
			low[12] = 1;
			high[12] = 2;
		}
		else {
			// Otherwise, just copy the protocol value into position 12.
			high[12] = low[12] = cur->protocol;
		}
		// 1 means in the query, 0 means not in the query.
		high[0] = low[0] = 1;

		// If this is the first port, use MakeMDDFromTuple.
		// Otherwise, use Assign.
		if (sc->h.index == -1)
			FW->FWForest->MakeMDDFromTuple(low, high, sc->h);
		else
			FW->FWForest->Assign(sc->h, low, high, sc->h);
		prev = cur;
		cur = cur->next;
		if (s->named == 0) {
			delete  prev;
		}
	}
#ifdef DEBUG
	printf("%.256s\n", s->name);
	for (level k = 20; k > 0; k--) {
		printf("%d-%d ", low[k], high[k]);
		FW->FWForest->Compact(k);
	}
	printf("\n");
	FW->FWForest->PrintMDD();
#endif
	delete[]high;
	delete[]low;
	if (s->named == 0)
		delete  s;

	return sc;
}

// Build a condition object representing all packets
// with state value equal to "state".
condition *BuildConditionFromState(int state)
{
	condition *sc;
	int    *low;
	int    *high;
	int     i;

	low = new int[21];
	high = new int[21];

	sc = new condition;

	// Initialize all elements to [0-MAX]
	for (i = 20; i >= 1; i--) {
		low[i] = 0;
		high[i] = FW->FWForest->GetMaxVal(i);
	}
	// Set position 7 according to the value of state.  
	high[7] = low[7] = state;

	// 1 means in the query, 0 means not in the query.
	high[0] = low[0] = 1;

	// Make an MDD from the tuple.
	FW->FWForest->MakeMDDFromTuple(low, high, sc->h);
	delete[]high;
	delete[]low;
	return sc;
}

// Build a condition representing the set of all packets with "flag" set.
condition *BuildConditionFromFlag(int flag)
{
	condition *newCond;
	int    *low;
	int    *high;
	int     i;

	newCond = new condition;
	low = new int[21];
	high = new int[21];

	// Initialize all elements to [0-MAX]
	for (i = 20; i >= 1; i--) {
		low[i] = 0;
		high[i] = FW->FWForest->GetMaxVal(i);
	}

	// Set the appropriate value to 1.
	switch (flag) {
		case 0:						  // FIN
			low[6] = high[6] = 1;
			break;
		case 1:						  // SYN
			low[5] = high[5] = 1;
			break;
		case 2:						  // RST
			low[4] = high[4] = 1;
			break;
		case 3:						  // PSH
			low[3] = high[3] = 1;
			break;
		case 4:						  // ACK
			low[2] = high[2] = 1;
			break;
		case 5:						  // URG
			low[1] = high[1] = 1;
			break;
		default:
			printf("Bad TCP flag: %d.\n", flag);
			exit(-1);
	}
	// 1 means in the query, 0 means not in the query.
	low[0] = high[0] = 1;
	// Make an MDD from the tuple.
	FW->FWForest->MakeMDDFromTuple(low, high, newCond->h);
	delete[]high;
	delete[]low;
	return newCond;
}

// Given a condition c, create a new condition which represents the
// set complement of c.
condition *NegateCondition(condition * c)
{
	condition *newCond;

	newCond = new condition;

	// Use the binary complement operator, which stores the
	// result in newCond->h.
	FW->FWForest->BinaryComplement(c->h, newCond->h);

	// We can now free the initial condition
	FW->FWForest->DestroyMDD(c->h);
	delete  c;

#ifdef DEBUG
	printf("Negate\n");
	for (level k = 20; k > 0; k--)
		FW->FWForest->Compact(k);
	FW->FWForest->PrintMDD();
#endif
	return newCond;
}

// Given two conditions c1 and c2, return the set union of c1 and c2.
condition *UnionConditions(condition * c1, condition * c2)
{
	condition *newCond;

	newCond = new condition;

	// We use the "MAX" operation on MDDs, which stores
	// the result in newCond->h.
	FW->FWForest->Max(c1->h, c2->h, newCond->h);

	// Now c1 and c2 are no longer useful, so they can be freed.
	FW->FWForest->DestroyMDD(c1->h);
	FW->FWForest->DestroyMDD(c2->h);
	delete  c1;
	delete  c2;

#ifdef DEBUG
	printf("Union\n");
	for (level k = 20; k > 0; k--)
		FW->FWForest->Compact(k);
	FW->FWForest->PrintMDD();
#endif
	return newCond;
}

// Given two conditions c1 and c2, return the set intersection of c1 and
// c2.  
condition *IntersectConditions(condition * c1, condition * c2)
{
	condition *newCond;

	newCond = new condition;

	// Use the MIN operation on MDDs.
	FW->FWForest->Min(c1->h, c2->h, newCond->h);

	// Now we can free c1 and c2.

	// If c1 or c2 is a "Group" condition, does this BREAK STUFF?

	FW->FWForest->DestroyMDD(c1->h);
	FW->FWForest->DestroyMDD(c2->h);
	delete  c1;
	delete  c2;

#ifdef DEBUG
	printf("Intersect\n");
	for (level k = 20; k > 0; k--)
		FW->FWForest->Compact(k);
	FW->FWForest->PrintMDD();
#endif
	return newCond;
}

// Perform the query described by condition object "c" by intersecting
// "c" with the set of accepted packets.  Then, display the appropriate 
// information, as determined by the value of "subject".
query  *PerformQuery(int subject, condition * c, int input_chain)
{
	mdd_handle result;
        int mask[21];
			
	for (int i=0;i<21;i++)
	   mask[i] =0;

	// Intersect the set of accepted packets with the set of packets
	// relevant to the query (stored in condition "c").
	if (input_chain == 0) {
		FW->FWForest->QueryIntersect(FW->Input, c->h, result);
	}
	if (input_chain == 1) {
		FW->FWForest->QueryIntersect(FW->Forward, c->h, result);
	}
	if (input_chain == 2) {
		FW->FWForest->QueryIntersect(FW->Output, c->h, result);
	}
#ifdef DEBUG
	printf("Rules: %d Query: %d\n", FW->Forward.index, c->h.index);
	// FW->FWForest->PruneMDD(result);
	for (level k = 20; k > 0; k--)
		FW->FWForest->Compact(k);
	FW->FWForest->PrintMDD();
#endif

	// "Project" the results to Display the requested information
	switch (subject) {
		case 0:
			FW->FWForest->PruneMDD(result);
			for (level k = 20; k > 0; k--)
				FW->FWForest->Compact(k);
			FW->FWForest->PrintMDD();
			// FW->FWForest->PrintStates(result.index);
			break;
		case 1:
			printf("# Ports: ");
			// Source port starts at level 11
			mask[11]=1;
			mask[10]=1;
			FW->FWForest->PrintRanges(result, mask);
//			FW->FWForest->PrintPort(result, 10);
			break;
		case 2:
			printf("# Ports: ");
			// Destination port starts at level 9
			mask[9]=1;
			mask[8]=1;
			FW->FWForest->PrintRanges(result, mask);
//			FW->FWForest->PrintPort(result, 8);
			break;
		case 3:
			printf("# Addresses: ");
			// Source addresses start at level 20
			mask[20]=1;
			mask[19]=1;
			mask[18]=1;
			mask[17]=1;
			FW->FWForest->PrintRanges(result, mask);
			//FW->FWForest->PrintAddy(result, 20);
			break;
		case 4:
			printf("# Addresses: ");
			// Destination addresses start at level 16
			mask[16]=1;
			mask[15]=1;
			mask[14]=1;
			mask[13]=1;
			FW->FWForest->PrintRanges(result, mask);
			//FW->FWForest->PrintAddy(result, 16);
			break;
		case 5:
			printf("# States: ");
			mask[7]=1;
			FW->FWForest->PrintRanges(result, mask);
			// The state value is stored at level 7
			//FW->FWForest->PrintVals(result, 7);
			break;
	}
	// Now that the query is done, free the query condition.
	FW->FWForest->DestroyMDD(c->h);
	delete  c;

	return NULL;
}

// Add port "newPort" to the port list "list" and return the result.
port   *AppendPort(port * list, port * newPort)
{
	newPort->next = list;
	return newPort;
}

// Add the address "newAddy" to the address list "list" and return the
// result.
address *AppendAddy(address * list, address * newAddy)
{
	newAddy->next = list;
	return newAddy;
}

// From a linked list of ports and a name string, create a 
// service struct and store it in the service array.
service *DefineService(char *name, port * list)
{
	service *s;

	s = new service;
	strncpy(s->name, name, 256);
	delete[]name;
	s->named = 1;
	s->list = list;
	services[num_services] = s;
	num_services++;
	return s;
}

// From a linked list of addresses and a name string, create a 
// group struct and store it in the group array.
group  *DefineGroup(char *name, address * list)
{
	group  *g;

	g = new group;
	strncpy(g->name, name, 256);
	delete[]name;
	g->named = 1;
	g->list = list;
	groups[num_groups] = g;
	num_groups++;
	return g;
}

// Set the protocol for port "p" to "protocol" and return the result.
port   *BuildPort(int protocol, port * p)
{
	p->protocol = protocol;
	return p;
}

void DoCleanup()
{
	int     i;
	address *nextAddy;
	port   *nextPort;

	for (i = 0; i < num_groups; i++) {
		while (groups[i]->list != NULL) {
			nextAddy = groups[i]->list;
			groups[i]->list = groups[i]->list->next;
			delete  nextAddy;
		}
		delete  groups[i];

		groups[i] = NULL;
	}
	for (i = 0; i < num_services; i++) {
		while (services[i]->list != NULL) {
			nextPort = services[i]->list;
			services[i]->list = services[i]->list->next;
			delete  nextPort;
		}
		delete  services[i];

		services[i] = NULL;
	}
	FW->FWForest->DestroyMDD(FW->Input);
	FW->FWForest->DestroyMDD(FW->Output);
	FW->FWForest->DestroyMDD(FW->Forward);
	FW->FWForest->DestroyMDD(FW->InputLog);
	FW->FWForest->DestroyMDD(FW->OutputLog);
	FW->FWForest->DestroyMDD(FW->ForwardLog);
}
