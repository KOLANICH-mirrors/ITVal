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

#define SIZE_OF_LEVEL_18 256

Firewall::Firewall (fw_fddl_forest * F)
{
  int ranges[5] = {65536,255,255,255,255};
  FWForest = F;
  num_nat_chains = -1;
  num_chains = -1;
  for (int i = 0; i < 256; i++)
  {
    chain_array[i] = nat_chains[i] = NULL;
  }
  ClassForest = new fw_fddl_forest(5,ranges);
  ClassForest->ToggleSparsity(false);
};

Firewall::Firewall (char *filterName, char *natName, fw_fddl_forest * F, Topology* top)
{
  int ranges[5] = {65536,256,256,256,256};
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
  ClassForest = new fw_fddl_forest(5,ranges);
  ClassForest->ToggleSparsity(false);
}

Firewall::Firewall (char *filterName, char *natName, fw_fddl_forest * F, Topology* top, int verbose)
{
  int ranges[5] = {65536,255,255,255,255};
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
  ClassForest = new fw_fddl_forest(5,ranges);
  ClassForest->ToggleSparsity(false);
}

int Firewall::PrintClasses(){
   mdd_handle FWSourceClass;
   mdd_handle INSourceClass;
   mdd_handle OUTSourceClass;
   
   mdd_handle FWDestClass;
   mdd_handle INDestClass;
   mdd_handle OUTDestClass;

   mdd_handle newChain;
   mdd_handle resultClass;

   int numClasses = 0;

   //FWForest->PrintMDD();
   FWForest->BuildClassMDD(Forward, ClassForest, FWSourceClass, numClasses);
//	printf("There are %d Forward Source classes:\n", numClasses);
   //ClassForest->PrintMDD();
	
//	ClassForest->PrintClasses(FWSourceClass, numClasses);
   FWForest->BuildClassMDD(Input, ClassForest, INSourceClass, numClasses);
//	printf("There are %d Input Source classes:\n", numClasses);
   //ClassForest->PrintMDD();
//	ClassForest->PrintClasses(INSourceClass, numClasses);
   FWForest->BuildClassMDD(Output, ClassForest, OUTSourceClass, numClasses);
//	printf("There are %d Output Source classes:\n", numClasses);
   //ClassForest->PrintMDD();
//	ClassForest->PrintClasses(OUTSourceClass, numClasses);

   //Shift Destination Addresses to Top.
	FWForest->Shift(Forward,15,newChain);
	FWForest->Shift(newChain,15,newChain);
	FWForest->Shift(newChain,15,newChain);
	FWForest->Shift(newChain,15,newChain);
// As we move lower levels to the top, the top levels move down!
//   FWForest->Shift(newChain,16,newChain);
//   FWForest->Shift(newChain,17,newChain);
//   FWForest->Shift(newChain,18,newChain);

   FWForest->BuildClassMDD(newChain, ClassForest, FWDestClass, numClasses);
//	printf("There are %d Forward Destination classes:\n", numClasses);
//	ClassForest->PrintClasses(FWDestClass, numClasses);

	//Debug
//	printf("FWDestClass: %d\n", FWDestClass.index);
//   ClassForest->PrintMDD();
	//End Debug

   FWForest->Shift(Input,15,newChain);
	FWForest->Shift(newChain,15,newChain);
	FWForest->Shift(newChain,15,newChain);
	FWForest->Shift(newChain,15,newChain);
   FWForest->BuildClassMDD(newChain, ClassForest, INDestClass, numClasses);
//	printf("There are %d Input Destination classes:\n", numClasses);
//   ClassForest->PrintMDD();
//   ClassForest->PrintClasses(INDestClass, numClasses);

   FWForest->Shift(Output,15,newChain);
	FWForest->Shift(newChain,15,newChain);
	FWForest->Shift(newChain,15,newChain);
	FWForest->Shift(newChain,15,newChain);
//   FWForest->Shift(newChain,16,newChain);
//   FWForest->Shift(newChain,17,newChain);
//   FWForest->Shift(newChain,18,newChain);
   FWForest->BuildClassMDD(newChain, ClassForest, OUTDestClass, numClasses);
//	printf("There are %d Output Destination classes:\n", numClasses);
   //ClassForest->PrintMDD();
//	ClassForest->PrintClasses(OUTDestClass, numClasses);

	ClassForest->JoinClasses(FWSourceClass,INSourceClass, resultClass,numClasses);
	
	ClassForest->JoinClasses(resultClass,OUTSourceClass, resultClass, numClasses);
	
//   printf("Join Result and OUTSource: \n");
//	ClassForest->PrintClasses(resultClass, numClasses);
	
	ClassForest->JoinClasses(resultClass,FWDestClass, resultClass,numClasses);
	ClassForest->JoinClasses(resultClass,INDestClass, resultClass,numClasses);
	ClassForest->JoinClasses(resultClass,OUTDestClass, resultClass,numClasses);

	printf("There are %d total host classes:\n",numClasses);
	ClassForest->PrintClasses(resultClass, numClasses);
	
}

group* Firewall::GetClasses(){
   mdd_handle FWSourceClass;
   mdd_handle INSourceClass;
   mdd_handle OUTSourceClass;
   
   mdd_handle FWDestClass;
   mdd_handle INDestClass;
   mdd_handle OUTDestClass;

   mdd_handle newChain;
   mdd_handle resultClass;

   int numClasses = 0;

   FWForest->BuildClassMDD(Forward, ClassForest, FWSourceClass, numClasses);
   FWForest->BuildClassMDD(Input, ClassForest, INSourceClass, numClasses);
   FWForest->BuildClassMDD(Output, ClassForest, OUTSourceClass, numClasses);
   
   //Shift Destination Addresses to Top.
   FWForest->Shift(Forward,15,newChain);
   FWForest->Shift(newChain,15,newChain);
   FWForest->Shift(newChain,15,newChain);
   FWForest->Shift(newChain,15,newChain);

   FWForest->BuildClassMDD(newChain, ClassForest, FWDestClass, numClasses);
   FWForest->Shift(Input,15,newChain);
   FWForest->Shift(newChain,15,newChain);
   FWForest->Shift(newChain,15,newChain);
   FWForest->Shift(newChain,15,newChain);
   FWForest->BuildClassMDD(newChain, ClassForest, INDestClass, numClasses);
   FWForest->Shift(Output,15,newChain);
   FWForest->Shift(newChain,15,newChain);
   FWForest->Shift(newChain,15,newChain);
   FWForest->Shift(newChain,15,newChain);
   FWForest->BuildClassMDD(newChain, ClassForest, OUTDestClass, numClasses);
   ClassForest->JoinClasses(FWSourceClass,INSourceClass, resultClass,numClasses);
   ClassForest->JoinClasses(resultClass,OUTSourceClass, resultClass, numClasses);
   ClassForest->JoinClasses(resultClass,FWDestClass, resultClass,numClasses);
   ClassForest->JoinClasses(resultClass,INDestClass, resultClass,numClasses);
   ClassForest->JoinClasses(resultClass,OUTDestClass, resultClass,numClasses);

   //printf("There are %d total host classes:\n",numClasses);
   //ClassForest->PrintClasses(resultClass, numClasses);
   return ClassForest->GetClasses(resultClass, numClasses);
}

/* Create a Meta-Firewall */
/* Need to do something about Topologies, here. */
Firewall *
MergeFWs (fw_fddl_forest * FWForest, Firewall ** fws, int n)
{
  Firewall *f;
  int prerouting, postrouting;

  int i;

  if (n == 0)
    return NULL;

  f = new Firewall (FWForest);

  prerouting = fws[0]->FindNATChain ("Prerouting");
  postrouting = fws[0]->FindNATChain ("Postrouting");

  if (prerouting >= 0)
  {
    fws[0]->NATChains (postrouting, fws[0]->Forward, f->Forward,
		       f->ForwardLog);
    fws[0]->NATChains (postrouting, fws[0]->Input, f->Input, f->InputLog);
    fws[0]->NATChains (postrouting, fws[n - 1]->Output, f->Output,
		       f->OutputLog);
  }
  else
  {
    FWForest->Attach (f->Forward, fws[0]->Forward.index);
    FWForest->Attach (f->ForwardLog, fws[0]->ForwardLog.index);

    FWForest->Attach (f->Input, fws[0]->Input.index);
    FWForest->Attach (f->InputLog, fws[0]->InputLog.index);

    FWForest->Attach (f->Output, fws[n - 1]->Output.index);
    FWForest->Attach (f->OutputLog, fws[n - 1]->OutputLog.index);
  }

  for (i = 1; i < n; i++)
  {
    FWForest->Min (f->Forward, fws[i]->Forward, f->Forward);
    FWForest->Min (f->Input, fws[i]->Forward, f->Forward);
    FWForest->Min (f->Output, fws[(n - 1) - i]->Forward, f->Forward);

    prerouting = fws[i]->FindNATChain ("Prerouting");
    postrouting = fws[i - 1]->FindNATChain ("Postrouting");

    /* SNAT the chains (and postrouting NETMAP them) */
    if (postrouting >= 0)
    {
      fws[i]->NATChains (postrouting, f->Forward, f->Forward, f->ForwardLog);
      fws[i]->NATChains (postrouting, f->Input, f->Input, f->InputLog);
    }
    /* DNAT the chains and (Prerouting NETMAP them) */
    if (prerouting >= 0)
    {
      fws[i]->NATChains (prerouting, f->Forward, f->Forward, f->ForwardLog);
      fws[i]->NATChains (prerouting, f->Input, f->Input, f->InputLog);
    }

    prerouting = fws[(n - 1) - i]->FindNATChain ("Prerouting");
    postrouting = fws[n - i]->FindNATChain ("Postrouting");
    if (postrouting >= 0)
    {
      fws[n - i]->NATChains (postrouting, f->Output, f->Output, f->OutputLog);
    }
    if (prerouting >= 0)
    {
      fws[n - i]->NATChains (prerouting, f->Output, f->Output, f->OutputLog);
    }
  }
  return f;
}
