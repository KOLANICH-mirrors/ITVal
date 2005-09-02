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

#include <stdio.h>
#include "structures.h"
#include "firewall.h"
#include "FDDL/mdd.h"

// Parser hooks.  These objects link bison/flex to our code.
int     yyparse();				  // Initiate Parsing
extern FILE *yyin;				  // Parsed File Handle
extern int FWLANG_LINE_NO;		  // Line number (for error reporting)

// Create a META-Firewall from all the independent firewalls.
Firewall *MergeFWs(fddl_forest * FWForest, Firewall ** fws, int num_fws);

// Free group and service declarations, plus MDDs.
void    DoCleanup();

// Main Routine.  Syntax: ITVal <query file> {<filter1> <nat1> ...}
int main(int argc, char **argv)
{
	int     parseError;			  // Error indicator

	Firewall **fws;				  // Array of independent firewalls 
	int     num_fws;				  // Number of firewalls in the array

	fddl_forest *FWForest;
	Firewall *metaFirewall;

	int     ranges[21] = { 256,  // Target Chain
		1, 1, 1, 1, 1, 1,			  // Flags (FIN, SYN, RST, PSH, ACK, URG)
		3,								  // Connection State
		255, 255,					  // Destination Port
		255, 255,					  // Source Port
		2,								  // Protocol
		255, 255, 255, 255,		  // Destination Address
		255, 255, 255, 255		  // Source Address
	};

	// @IDEA@: Think about using "NULL" to mean use "no" NAT?
	if (argc < 4) {
		printf("Syntax: ITVal <queryfile> { <rulefile> <natfile> ... }\n");
		return 1;
	}

	FWForest = new fddl_forest(21, ranges);
	FWForest->ToggleSparsity(false);	// @BUG@: Sparse nodes don't work
	// ATM.

	// Initialize the firewall array
	num_fws = (argc - 2) / 2;
	fws = new Firewall *[num_fws];

	// Read each firewall and store it in the array.
	for (int i = 1; i <= num_fws; i++) {
		fws[i - 1] = new Firewall(argv[i * 2], argv[i * 2 + 1], FWForest);
	}

	// Create the meta firewall.
	metaFirewall = MergeFWs(FWForest, fws, num_fws);

	// @IDEA@: Is this really a good idea?
	for (int i = 1; i <= num_fws; i++) {
		delete  fws[i - 1];		  // Clean up independent firewalls.
	}
	delete[]fws;

	if (!metaFirewall) {
		printf("No firewalls to merge!\nAborting.\n");
		exit(-1);
	}
	// Connect the Forest to the Query Engine.
	InitializeStructures(metaFirewall);

	// Open the query file.
	yyin = fopen(argv[1], "r");
	if (!yyin) {
		printf("Error: Could not find query file: %s.\n", argv[1]);
		return 0;
	}
	// Parse and apply the query file.
	parseError = yyparse();

	if (parseError != 0) {
		printf("\nAn error occured during parsing: %d.\n", parseError);
	}

	DoCleanup();
	delete  metaFirewall;
	delete  FWForest;

	return parseError;
}

// Bison error handling function.
void yyerror(char *str)
{
	fprintf(stderr, "%s at line %d\n", str, FWLANG_LINE_NO);
}

// Create a Meta-Firewall
Firewall *MergeFWs(fddl_forest * FWForest, Firewall ** fws, int n)
{
	Firewall *f;
	int     prerouting, postrouting;

	int     i;

	if (n == 0)
		return NULL;

	f = new Firewall(FWForest);

	prerouting = fws[0]->FindNATChain("Prerouting");
	postrouting = fws[0]->FindNATChain("Postrouting");

	if (prerouting >= 0) {
		fws[0]->NATChains(postrouting, fws[0]->Forward, f->Forward,
								f->ForwardLog);
		fws[0]->NATChains(postrouting, fws[0]->Input, f->Input, f->InputLog);
		fws[0]->NATChains(postrouting, fws[n - 1]->Output, f->Output,
								f->OutputLog);
	}
	else {
		FWForest->Attach(f->Forward, fws[0]->Forward.index);
		FWForest->Attach(f->ForwardLog, fws[0]->ForwardLog.index);

		FWForest->Attach(f->Input, fws[0]->Input.index);
		FWForest->Attach(f->InputLog, fws[0]->InputLog.index);

		FWForest->Attach(f->Output, fws[n - 1]->Output.index);
		FWForest->Attach(f->OutputLog, fws[n - 1]->OutputLog.index);
	}

	for (i = 1; i < n; i++) {
		FWForest->Min(f->Forward, fws[i]->Forward, f->Forward);
		FWForest->Min(f->Input, fws[i]->Forward, f->Forward);
		FWForest->Min(f->Output, fws[(n - 1) - i]->Forward, f->Forward);

		prerouting = fws[i]->FindNATChain("Prerouting");
		postrouting = fws[i - 1]->FindNATChain("Postrouting");

		// SNAT the chains (and postrouting NETMAP them)
		if (postrouting >= 0) {
			fws[i]->NATChains(postrouting, f->Forward, f->Forward,
									f->ForwardLog);
			fws[i]->NATChains(postrouting, f->Input, f->Input, f->InputLog);
		}
		// DNAT the chains and (Prerouting NETMAP them)
		if (prerouting >= 0) {
			fws[i]->NATChains(prerouting, f->Forward, f->Forward, f->ForwardLog);
			fws[i]->NATChains(prerouting, f->Input, f->Input, f->InputLog);
		}

		prerouting = fws[(n - 1) - i]->FindNATChain("Prerouting");
		postrouting = fws[n - i]->FindNATChain("Postrouting");
		if (postrouting >= 0) {
			fws[n - i]->NATChains(postrouting, f->Output, f->Output,
										 f->OutputLog);
		}
		if (prerouting >= 0) {
			fws[n - i]->NATChains(prerouting, f->Output, f->Output,
										 f->OutputLog);
		}
	}
	// FWForest->PrintMDD();
	return f;
}
