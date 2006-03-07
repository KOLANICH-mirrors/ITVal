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

#include "iface.h"
#include "firewall.h"

#include "debug.h"

/*
 * The following functions, taken together, turn a processed_rule, pr, into
 * a set of rule_tuples suitable for insertion into an MDD.  The
 * resulting tuples are stored on a stack, which is passed as a reference
 * parameter.
 *
 * The current tuple is stored in "tup".  Starting with "ProcessSource",
 * each function sets some elements of tup.  Then, tup is handed to
 * another function in which sets some more elements.  
 * When all elements have been filled, the last function, ProcessTarget,
 * pushes "tup" onto the stack.
 */

/*
 * Store the target of "pr" as tup[0] and push onto the stack.
 */

void
  Firewall::ProcessTarget(processed_rule * pr, rule_tuple * tup,
                          rule_tuple * &stack)
{
   rule_tuple *newTup;
   int val;

   /*
    * If it's a "LOG" mark it specially, so that it can be put in the
    * Log MDD instead of the ACCEPT MDD.
    */

   if (strncmp(pr->target, "LOG", 3) == 0) {
      tup->low[0] = tup->high[0] = LOG;
   }
   else if (strncmp(pr->target, "RETURN", 6) == 0) {
      tup->low[0] = tup->high[0] = RETURN;
   }
   else if (strncmp(pr->target, "ACCEPT", 6) == 0) {
      tup->low[0] = tup->high[0] = ACCEPT;
   }
   else if (strncmp(pr->target, "REJECT", 6) == 0) {    // If it's a
      // "REJECT" 
      tup->low[0] = tup->high[0] = REJECT;
   }
   else if (strncmp(pr->target, "DROP", 4) == 0) {      // If it's a drop.
      tup->low[0] = tup->high[0] = DROP;
   }
   else {
      // If it's not LOG, ACCEPT, DROP, or REJECT, it must be a 
      // user-defined chain.  We add 4 to distinguish it from the
      // builtin targets.
      val = FindChain(pr->target);

      //If it's a special target not handle by ITVal (TCPMSS, i.e.)
      if (val == -2)
         return;

      if (val < 0) {
         printf("Could not find target: %s\n", pr->target);
         assert(0);
      }
      tup->low[0] = tup->high[0] = val + 4;
   }

   // Now push the tuple onto the stack.
   newTup = new rule_tuple;
   for (int i = 0; i < 23; i++) {
      newTup->low[i] = tup->low[i];
      newTup->high[i] = tup->high[i];
   }
   newTup->next = stack;
   stack = newTup;
}

/*
 * Store values of TCP flags FIN, SYN, RST, PSH, ACK, and URG in tup[1]
 * through tup[6].
 */

void Firewall::ProcessFlags(processed_rule * pr, rule_tuple * tup,
                            rule_tuple * &stack)
{
   int i;

   for (i = 0; i < 6; i++) {
      // -1 means the flag is not specified in the rule.  So packets
      // matching either 0 or 1 are acceptable.

      if (pr->flags[i] == -1) {
         tup->low[6 - i] = 0;
         tup->high[6 - i] = 1;
      }
      else {
         tup->low[6 - i] = tup->high[6 - i] = pr->flags[i];
      }
   }
   ProcessTarget(pr, tup, stack);
}

/*
 * Store information about state in the tuple.
 */

void Firewall::ProcessState(processed_rule * pr, rule_tuple * tup,
                            rule_tuple * &stack)
{
   int state = pr->state;

   if (state == 0) {
      // 0 means any state.
      tup->low[7] = 0;
      tup->high[7] = 3;
      ProcessFlags(pr, tup, stack);
   }
   if (state & INVALID) {
      tup->low[7] = tup->high[7] = 0;
      ProcessFlags(pr, tup, stack);
   }
   if (state & NEW) {
      tup->low[7] = tup->high[7] = 1;
      ProcessFlags(pr, tup, stack);
   }
   if (state & ESTABLISHED) {
      tup->low[7] = tup->high[7] = 2;
      ProcessFlags(pr, tup, stack);
   }
   if (state & RELATED) {
      tup->low[7] = tup->high[7] = 3;
      ProcessFlags(pr, tup, stack);
   }
}

void Firewall::ProcessIfaces(processed_rule * pr, rule_tuple * tup,
                             rule_tuple * &stack)
{
   if (pr->in >= 0)
      tup->low[9] = tup->high[9] = pr->in;
   else {
      tup->low[9] = 0;
      tup->high[9] = 255;
   }

   if (pr->out >= 0)
      tup->low[8] = tup->high[8] = pr->out;
   else {
      tup->low[8] = 0;
      tup->high[8] = 255;
   }

   ProcessState(pr, tup, stack);
}

/*
 * Store the destination port in the tuple.  The port is partitioned
 * into two bytes, to improve performance of the MDD.  Since
 * processed_rules can contain multiple port_ranges in a linked list,
 * we can actually generate several tuples here instead of just one.
 */

void Firewall::ProcessDport(processed_rule * pr, rule_tuple * tup,
                            rule_tuple * &stack)
{
   port_range *cur;

   cur = pr->dports;
   if (cur == NULL) {
      // If no destination port is specified, any port matches.
      tup->low[11] = 0;
      tup->high[11] = 255;
      tup->low[10] = 0;
      tup->high[10] = 255;
      ProcessIfaces(pr, tup, stack);
   }
   else {
      // Loop across the linked list to handle multiple port ranges.
      while (cur != NULL) {
         tup->low[11] = tup->high[11] = cur->port1;
         tup->low[10] = tup->high[10] = cur->port2;
         ProcessIfaces(pr, tup, stack);
         cur = cur->next;
      }
   }
}

/*
 * Store the source port information in the tuple.  Just like
 * ProcessDport, we may push several tuples onto the stack if 
 * pr has multiple port_ranges.
 */

void Firewall::ProcessSport(processed_rule * pr, rule_tuple * tup,
                            rule_tuple * &stack)
{
   port_range *cur;

   cur = pr->sports;
   if (cur == NULL) {
      // If not specified in the rule, any port matches.
      tup->low[13] = 0;
      tup->high[13] = 255;
      tup->low[12] = 0;
      tup->high[12] = 255;
      ProcessDport(pr, tup, stack);
   }
   else {
      // Loop across the linked list to handle multiple port ranges.
      while (cur != NULL) {
         tup->low[13] = tup->high[13] = cur->port1;
         tup->low[12] = tup->high[12] = cur->port2;
         ProcessDport(pr, tup, stack);
         cur = cur->next;
      }
   }
}

/*
 * Store the protocol information in the tuple.  Supported protocols are
 * ICMP, UDP, and TCP.
 */

void Firewall::ProcessProt(processed_rule * pr, rule_tuple * tup,
                           rule_tuple * &stack)
{
   switch (pr->protocol) {
      case 'i':
         tup->low[14] = tup->high[14] = ICMP;   // icmp
         break;
      case 'u':
         tup->low[14] = tup->high[14] = UDP;    // udp
         break;
      case 't':
         tup->low[14] = tup->high[14] = TCP;    // tcp
         break;
      default:
         // If it's 'a', any protocol matches.
         tup->low[14] = 0;
         tup->high[14] = 2;
         break;
   }
   ProcessSport(pr, tup, stack);
}

/*
 * Store the destination address information in the tuple.  IP addresses
 * are partitioned into four bytes to improve performance of the MDD.  
 * (Partitioning also helps readability when debugging).
 */

void Firewall::ProcessDest(processed_rule * pr, rule_tuple * tup,
                           rule_tuple * &stack)
{
   tup->low[15] = pr->to->low % 256;
   tup->low[16] = pr->to->low / 256 % 256;
   tup->low[17] = ((pr->to->low / 256) / 256) % 256;
   tup->low[18] = ((signed int) (((pr->to->low / 256) / 256) / 256)) % 256;
   tup->high[15] = pr->to->high % 256;
   tup->high[16] = (pr->to->high / 256) % 256;
   tup->high[17] = ((pr->to->high / 256) / 256) % 256;
   tup->high[18] = ((signed int) (((pr->to->high / 256) / 256) / 256)) % 256;
   ProcessProt(pr, tup, stack);
}

/*
 * Store the source address information in the tuple.  As in ProcessDest,
 * IP addresses are partitioned into four bytes.
 */

void Firewall::ProcessSource(processed_rule * pr, rule_tuple * tup,
                             rule_tuple * &stack)
{
   tup->low[19] = pr->from->low % 256;
   tup->low[20] = (pr->from->low / 256) % 256;
   tup->low[21] = ((pr->from->low / 256) / 256) % 256;
   tup->low[22] = ((signed int) (((pr->from->low / 256) / 256) / 256)) % 256;
   tup->high[19] = pr->from->high % 256;
   tup->high[20] = (pr->from->high / 256) % 256;
   tup->high[21] = ((pr->from->high / 256) / 256) % 256;
   tup->high[22] =
      ((signed int) (((pr->from->high / 256) / 256) / 256)) % 256;
   ProcessDest(pr, tup, stack);

   if (pr->from->next != NULL) {

      tup->low[19] = pr->from->next->low % 256;
      tup->low[20] = (pr->from->next->low / 256) % 256;
      tup->low[21] = ((pr->from->next->low / 256) / 256) % 256;
      tup->low[22] =
         ((signed int) (((pr->from->next->low / 256) / 256) / 256)) % 256;
      tup->high[19] = pr->from->next->high % 256;
      tup->high[20] = (pr->from->next->high / 256) % 256;
      tup->high[21] = ((pr->from->next->high / 256) / 256) % 256;
      tup->high[22] =
         ((signed int) (((pr->from->next->high / 256) / 256) / 256)) % 256;

      ProcessDest(pr, tup, stack);
   }
}

/*
 * In reverse order(to preserve the IP tables semantics), turn a linked
 * list of processed_rules beginning with "head" into a stack of tuples 
 * suitable for insertion into the MDD.
 */

void Firewall::BuildRules(processed_rule * head, rule_tuple * &stack)
{
   rule_tuple *tup;                       // A placeholder output tuple

   if (head == NULL)            // If the list is empty, we're done.
      return;

   tup = new rule_tuple;
   BuildRules(head->next, stack);       // In Reverse order.
   if (head->pktcond <=1)               // Temporarily, ignore PKTTYPE flags.
      ProcessSource(head, tup, stack);     // Initiate the processing chain.
   delete tup;
}

// Turn a stack of rule_tuples into an MDD describing the set of accepted
// packets and an MDD describing the set of logged packets.

// Tuples that point to another chain are "intersected" with the MDD for
// that chain until their final fate becomes clear.  Then, they are
// inserted into outMDD.  This confusing recursive algorithm is
// the guts of this tool.

// chain_array is the array of iptables chains.  inMDD is an MDD
// representing the tuples in the chain that have already been processed.
// "tup" is the tuple to be inserted.  outMDD and logMDD are the outputs
// of the function.

void Firewall::ProcessChain(chain ** chain_array, mdd_handle inMDD,
                            rule_tuple * tup, mdd_handle & outMDD,
                            mdd_handle & logMDD)
{
   // criteriaMDD represents the set of packets that match tup.
   mdd_handle criteriaMDD;

   // We process the rules of the chains in reverse order to preserve IP
   // tables sematics.
   // 
   if (tup == NULL) {
      // If we've gotten past the last chain, we just copy the inputMDD
      // and return.
      FWForest->Attach(outMDD, inMDD.index);
      return;
   }
   ProcessChain(chain_array, inMDD, tup->next, outMDD, logMDD);

#ifdef VERBOSE_DEBUG
   PrintRuleTuple(tup);         // For debugging
   printf("Before:\n");
   for (level k = 22; k > 0; k--)
      FWForest->Compact(k);
   FWForest->PrintMDD();
#endif

   // If it's a log rule, insert it into the Log MDD and return.
   if (tup->high[0] == -1) {
      tup->low[0] = tup->high[0] = 1;
      FWForest->Assign(logMDD, tup->low, tup->high, logMDD);
      tup->low[0] = tup->high[0] = -1;

      //FWForest->DestroyMDD(inMDD);
      return;
   }
   // Otherwise, take the output of the previous function off the stack
   // and make it the input MDD.


//   FWForest->DestroyMDD(inMDD);
   FWForest->Attach(inMDD, outMDD.index);

   // The old output MDD can be cleaned.
   FWForest->DestroyMDD(outMDD);

   // Create the intermediate MDD
   FWForest->MakeMDDFromTuple(tup->low, tup->high, criteriaMDD);

#ifdef VERBOSE_DEBUG
   printf("Make Criteria MDD: %d\n", criteriaMDD.index);
   for (level k = 22; k > 0; k--)
      FWForest->Compact(k);
   FWForest->PrintMDD();
#endif

   // If the rule is a terminating rule (ACCEPT, DROP, OR REJECT)
   // We simply insert it into the MDD.
   if (tup->low[0] < 4) {

      // Insert it into the MDD.  Replace takes a flag
      // parameter that indicates whether to insert new
      // tuples.  When passed "true" it copies the tuples in
      // interMDD into inMDD whether they already have values
      // or not.  The result is stored in outMDD.

//      FWForest->Replace(inMDD, criteriaMDD, true, outMDD);
      FWForest->Assign(inMDD, tup->low, tup->high, outMDD);

      // Clean up inMDD and interMDD since we don't need 'em anymore.
//      FWForest->DestroyMDD(inMDD);  
      FWForest->DestroyMDD(criteriaMDD);

      for (level k = 22; k > 0; k--)
         FWForest->Compact(k);

#ifdef VERBOSE_DEBUG
      printf("Assign Target: %d\n", outMDD.index);
      PrintRuleTuple(tup);      // For debugging
      for (level k = 22; k > 0; k--)
         FWForest->Compact(k);
      FWForest->PrintMDD();
#endif

      // Since we are doing things in reverse order, it's possible
      // that a packet that matches a log rule later in the chain 
      // has already been inserted into logMDD, but can't get there
      // because we dropped or accepted it.  So, we erase it from the
      // log right here.

      tup->low[0] = tup->high[0] = 0;
      FWForest->Assign(logMDD, tup->low, tup->high, logMDD);
      tup->low[0] = tup->high[0] = -1;  // In case a later query
      // needs it.

   }
   else {
      // If the target is another chain, we have to construct the other
      // chain first.  But only that PART of the chain which matches
      // the tuple we're working on.  So . . .

      chain *nextChain;                   // The chain this rule targets.

      nextChain = chain_array[tup->low[0] - 4];

      // Build the other chain, passing interMDD as the input and
      // output.
      // FWForest->Attach(interMDD,interMDD.index); //Artificially
      // inflate the incoming arc counter.

      mdd_handle targetMDD;
      mdd_handle resultMDD;

      ProcessChain(chain_array, inMDD, nextChain->tup, targetMDD, logMDD);
      FWForest->ProjectOnto(targetMDD, criteriaMDD, resultMDD);

#ifdef VERBOSE_DEBUG
      printf("Restrict: %d\n", resultMDD.index);
      PrintRuleTuple(tup);      // For debugging
      for (level k = 22; k > 0; k--)
         FWForest->Compact(k);
      FWForest->PrintMDD();
#endif


      // Clean up criteriaMDD.
      FWForest->DestroyMDD(criteriaMDD);

#ifdef VERBOSE_DEBUG
      printf("Clean Up Criteria MDD\n");
      PrintRuleTuple(tup);      // For debugging
      for (level k = 22; k > 0; k--)
         FWForest->Compact(k);
      FWForest->PrintMDD();
#endif


      FWForest->Replace(inMDD, resultMDD, true, outMDD);

      // Clean up inMDD, resultMDD, and targetMDD, 
      // since they have served their purposes.
//      FWForest->DestroyMDD(inMDD);

#ifdef VERBOSE_DEBUG
      printf("Replace: %d\n", targetMDD.index);
      PrintRuleTuple(tup);      // For debugging
      for (level k = 22; k > 0; k--)
         FWForest->Compact(k);
      FWForest->PrintMDD();
#endif

      FWForest->DestroyMDD(resultMDD);
#ifdef VERBOSE_DEBUG
      printf("Clean Result MDD:\n");
      PrintRuleTuple(tup);      // For debugging
      for (level k = 22; k > 0; k--)
         FWForest->Compact(k);
      FWForest->PrintMDD();
#endif
      FWForest->DestroyMDD(targetMDD);
#ifdef VERBOSE_DEBUG
      printf("Clean Target MDD:\n");
      PrintRuleTuple(tup);      // For debugging
      for (level k = 22; k > 0; k--)
         FWForest->Compact(k);
      FWForest->PrintMDD();
#endif
   }
}

// Initiate construction of outMDD and logMDD.
void Firewall::AssembleChains(chain ** chain_array, chain * chain,
                              mdd_handle & outMDD, mdd_handle & logMDD)
{
   // Here we set the default policy for the builtin chain.

   mdd_handle initMDD;

   int low[23];
   int high[23];

   low[0] = high[0] = chain->Default;   // Set default policy
   low[1] = 0;
   high[1] = 1;                 // Any value for FIN flag
   low[2] = 0;
   high[2] = 1;                 // SYN flag
   low[3] = 0;
   high[3] = 1;                 // RST flag
   low[4] = 0;
   high[4] = 1;                 // PSH flag
   low[5] = 0;
   high[5] = 1;                 // ACK flag
   low[6] = 0;
   high[6] = 1;                 // URG flag
   low[7] = 0;
   high[7] = 3;                 // Any state
   low[8] = 0;
   high[8] = 255;               // Any Output Interface
   low[9] = 0;
   high[9] = 255;               // Any Input Interface
   low[10] = 0;

   high[10] = 255;              // Any destination port
   low[11] = 0;
   high[11] = 255;
   low[12] = 0;

   high[12] = 255;              // Any source port
   low[13] = 0;
   high[13] = 255;
   low[14] = 0;

   high[14] = 2;                // Any Protocol
   low[15] = 0;

   high[15] = 255;              // Any destination IP
   low[16] = 0;
   high[16] = 255;
   low[17] = 0;
   high[17] = 255;
   low[18] = 0;
   high[18] = 255;
   low[19] = 0;

   high[19] = 255;              // Any source IP
   low[20] = 0;
   high[20] = 255;
   low[21] = 0;
   high[21] = 255;
   low[22] = 0;
   high[22] = 255;

   // Create an MDD representing the default policy
   FWForest->MakeMDDFromTuple(low, high, initMDD);

   // It becomes the initial "inMDD" to ProcessChain.
   if (chain->tup != NULL) {
      ProcessChain(chain_array, initMDD, chain->tup, outMDD, logMDD);
      FWForest->DestroyMDD(initMDD);
   }
   else {
      FWForest->Attach(outMDD, initMDD.index);
   }
}
