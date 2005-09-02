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
#include "chains.h"
#include "FDDL/mdd.h"

class   Firewall {
	int     num_chains;
	int     num_nat_chains;

	//Can handle up to 256 seperate chains per firewall.
	chain  *chain_array[256];
	nat_chain *nat_chains[256];

	//Linked lists of processed(netmasks->ranges, strings->values) rules.
	processed_rule *phead;
	processed_nat_rule *natHead;

	void    ReadChain(char *line, ssize_t length, chain * newChain);
	void    BuildFWRules(char *fname);
	void    BuildNATRules(char *fname);
	void    BuildChains(int input_chain, mdd_handle & outputMDD,
							  mdd_handle & logMDD);

	void    AssembleChains(chain ** chain_array, chain * ch,
								  mdd_handle & outMDD, mdd_handle & logMDD);

	void    ProcessChain(chain ** chain_array, mdd_handle inMDD,
								rule_tuple * tup, mdd_handle & outMDD,
								mdd_handle & logMDD);

	void    BuildRules(processed_rule * pr, rule_tuple * &tup);

	void    ProcessSource(processed_rule * pr, rule_tuple * tup,
								 rule_tuple * &stack);
	void    ProcessDest(processed_rule * pr, rule_tuple * tup,
							  rule_tuple * &stack);
	void    ProcessProt(processed_rule * pr, rule_tuple * tup,
							  rule_tuple * &stack);
	void    ProcessSport(processed_rule * pr, rule_tuple * tup,
								rule_tuple * &stack);
	void    ProcessDport(processed_rule * pr, rule_tuple * tup,
								rule_tuple * &stack);
	void    ProcessState(processed_rule * pr, rule_tuple * tup,
								rule_tuple * &stack);
	void    ProcessFlags(processed_rule * pr, rule_tuple * tup,
								rule_tuple * &stack);
	void    ProcessTarget(processed_rule * pr, rule_tuple * tup,
								 rule_tuple * &stack);

	void    ConvertNATRules(processed_nat_rule * pnr, nat_tuple * &stack);
	void    DoNAT(nat_tuple * tup, mdd_handle inMDD,
					  mdd_handle & outMDD, mdd_handle & logMDD);

	void    ProcessNATSource(processed_nat_rule * pr,
									 nat_tuple * tup, nat_tuple * &stack);
	void    ProcessNATDest(processed_nat_rule * pr,
								  nat_tuple * tup, nat_tuple * &stack);
	void    ProcessNATProt(processed_nat_rule * pr,
								  nat_tuple * tup, nat_tuple * &stack);
	void    ProcessNATSport(processed_nat_rule * pr,
									nat_tuple * tup, nat_tuple * &stack);
	void    ProcessNATDport(processed_nat_rule * pr,
									nat_tuple * tup, nat_tuple * &stack);
	void    ProcessNATState(processed_nat_rule * pr,
									nat_tuple * tup, nat_tuple * &stack);
	void    ProcessNATFlags(processed_nat_rule * pr,
									nat_tuple * tup, nat_tuple * &stack);
	void    ProcessNATTarget(processed_nat_rule * pr,
									 nat_tuple * tup, nat_tuple * &stack);

 public:
	        fddl_forest * FWForest;
	mdd_handle Input;
	mdd_handle InputLog;
	mdd_handle Output;
	mdd_handle OutputLog;
	mdd_handle Forward;
	mdd_handle ForwardLog;

	int     FindChain(char *name);
	int     FindNATChain(char *name);
	void    NATChains(int input_chain, mdd_handle inMDD,
							mdd_handle & outMDD, mdd_handle & logMDD);

	        Firewall(fddl_forest * F);
	//Firewall(Firewall* Front, Firewall* Back, fddl_forest* F);

	        Firewall(char *filterName, char *natName, fddl_forest * F);

	       ~Firewall() {
		for (int i = 0; i < num_chains; i++)
			if (chain_array[i] != NULL)
				delete  chain_array[i];

		for     (int i = 0; i < num_nat_chains; i++)
			if      (nat_chains[i] != NULL)
				delete  nat_chains[i];

		        FWForest->DestroyMDD(Input);
		        FWForest->DestroyMDD(InputLog);
		        FWForest->DestroyMDD(Output);
		        FWForest->DestroyMDD(OutputLog);
		        FWForest->DestroyMDD(Forward);
		        FWForest->DestroyMDD(ForwardLog);
}};
