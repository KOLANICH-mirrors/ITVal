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
#include "firewall.h"

Firewall::Firewall(fddl_forest * F)
{
	FWForest = F;
	num_nat_chains = -1;
	num_chains = -1;
	for (int i = 0; i < 256; i++) {
		chain_array[i] = nat_chains[i] = NULL;
	}
};

Firewall::Firewall(char *filterName, char *natName, fddl_forest * F)
{
	int     high[21];
	int     low[21];

	int     input_chain;
	int     forward_chain;
	int     output_chain;

	FWForest = F;
	num_nat_chains = -1;
	num_chains = -1;
	for (int i = 0; i < 256; i++) {
		chain_array[i] = nat_chains[i] = NULL;
	}

	// Create and Initialize the Log MDDs
	for (level k = 0; k < 21; k++) {
		low[k] = 0;
		high[k] = F->GetMaxVal(k);
	}
	high[0] = 0;

	FWForest->MakeMDDFromTuple(low, high, InputLog);
	FWForest->MakeMDDFromTuple(low, high, OutputLog);
	FWForest->MakeMDDFromTuple(low, high, ForwardLog);

	BuildFWRules(filterName);
	BuildNATRules(natName);
	forward_chain = FindChain("FORWARD");
	input_chain = FindChain("INPUT");
	output_chain = FindChain("OUTPUT");
	if (forward_chain < 0) {
		printf("No Forward Chain!\n");
		exit(-1);
	}
	if (input_chain < 0) {
		printf("No Input Chain!\n");
		exit(-1);
	}
	if (output_chain < 0) {
		printf("No Output Chain!\n");
		exit(-1);
	}

	BuildChains(forward_chain, Forward, ForwardLog);
	BuildChains(input_chain, Input, InputLog);
	BuildChains(output_chain, Output, OutputLog);
}
