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

Firewall::Firewall (fw_fddl_forest * F)
{
  FWForest = F;
  num_nat_chains = -1;
  num_chains = -1;
  for (int i = 0; i < 256; i++)
  {
    chain_array[i] = nat_chains[i] = NULL;
  }
};

Firewall::Firewall (char *filterName, char *natName, fw_fddl_forest * F, Topology* top)
{
  int high[23];
  int low[23];

  int input_chain;
  int forward_chain;
  int output_chain;

  FWForest = F;
  T = top;

  num_nat_chains = -1;
  num_chains = -1;
  for (int i = 0; i < 256; i++)
  {
    chain_array[i] = nat_chains[i] = NULL;
  }

  // Create and Initialize the Log MDDs
  for (level k = 0; k < 23; k++)
  {
    low[k] = 0;
    high[k] = F->GetMaxVal(k);
  }
  high[0] = 0;

  FWForest->MakeMDDFromTuple (low, high, InputLog);
  FWForest->MakeMDDFromTuple (low, high, OutputLog);
  FWForest->MakeMDDFromTuple (low, high, ForwardLog);

  BuildFWRules (filterName);
  if (strncmp(natName, "NONAT",5)){
     BuildNATRules (natName);
  }
  forward_chain = FindChain ("FORWARD");
  input_chain = FindChain ("INPUT");
  output_chain = FindChain ("OUTPUT");
  if (forward_chain < 0)
  {
    printf ("No Forward Chain!\n");
    exit (-1);
  }
  if (input_chain < 0)
  {
    printf ("No Input Chain!\n");
    exit (-1);
  }
  if (output_chain < 0)
  {
    printf ("No Output Chain!\n");
    exit (-1);
  }

  BuildChains (forward_chain, Forward, ForwardLog);
  BuildChains (input_chain, Input, InputLog);
  BuildChains (output_chain, Output, OutputLog);

}

Firewall::Firewall (char *filterName, char *natName, fw_fddl_forest * F, Topology* top, int verbose)
{
  int high[23];
  int low[23];

  int input_chain;
  int forward_chain;
  int output_chain;

  FWForest = F;
  T = top;
  num_nat_chains = -1;
  num_chains = -1;
  for (int i = 0; i < 256; i++)
  {
    chain_array[i] = nat_chains[i] = NULL;
  }

  // Create and Initialize the Log MDDs
  for (level k = 0; k < 23; k++)
  {
    low[k] = 0;
    high[k] = F->GetMaxVal(k);
  }
  high[0] = 0;

  FWForest->MakeMDDFromTuple (low, high, InputLog);
  FWForest->MakeMDDFromTuple (low, high, OutputLog);
  FWForest->MakeMDDFromTuple (low, high, ForwardLog);

  BuildVerboseFWRules (filterName);
  if (strncmp(natName, "NONAT",5)){
     BuildNATRules (natName);
  }
  forward_chain = FindChain ("FORWARD");
  input_chain = FindChain ("INPUT");
  output_chain = FindChain ("OUTPUT");
  if (forward_chain < 0)
  {
    printf ("No Forward Chain!\n");
    exit (-1);
  }
  if (input_chain < 0)
  {
    printf ("No Input Chain!\n");
    exit (-1);
  }
  if (output_chain < 0)
  {
    printf ("No Output Chain!\n");
    exit (-1);
  }

  BuildChains (forward_chain, Forward, ForwardLog);
  BuildChains (input_chain, Input, InputLog);
  BuildChains (output_chain, Output, OutputLog);
 
#ifdef DEBUG   
   for (level k = 22; k > 0; k--)
      FWForest->Compact (k);
   FWForest->PrintMDD ();
#endif
}

int Firewall::PrintClasses(){
	eClass* sources;
	int numSources;
   eClass* dests;	
	int numDests;

	//Collect groups by source address
	FWForest->ExtractClasses(Input, sources, numSources);
	
	//Shift Destination Addresses to Top.
   mdd_handle newChain;
   FWForest->Shift(Input,18,22,newChain);
   FWForest->Shift(newChain,17,21,newChain);
   FWForest->Shift(newChain,16,20,newChain);
   FWForest->Shift(newChain,15,19,newChain);

	//Collect groups by destination
	FWForest->ExtractClasses(Input, dests, numDests);
	if (sources == NULL){
			  printf("Could not extract source classes.\n");
			  return 0;
	}
	
	if (dests == NULL){
			  printf("Could not extract destination classes.\n");
			  return 0;
	}
	
   for (int i=0;i<numSources;i++)
   	sources[i].Print();

   for (int i=0;i<numDests;i++)
   	dests[i].Print();

	//TBD: "Intersect" the groups
	//allClasses = IntersectClasses(sources, dests);
   //for (int i=0;i<numDests;i++)
   //	allClasses[i]->Print();
	return 1;
}
