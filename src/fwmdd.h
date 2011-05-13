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

//#define NO_HISTORY

#ifndef SRC_FWMDD_H
#   define SRC_FWMDD_H 1

#   include <iostream>
#   include <assert.h>

#   include <FDDL/mdd.h>
#   include "nat.h"
#   include "structures.h"
#   include "sets.h"
#   include "topology.h"


/*
 * The class FirewallForest enhances the fddl_forest by providing
 * certain algorithms specific to firewall representation.  In 
 * particular, we provide algorithms for query intersection, 
 * NAT transformation of the firewall MDD and 
 * printing Firewall query results.
 */

class FirewallForest:public Forest {
 private:
   Cache **FWCache;        //Cache for all firewall specific operations.

 public:

    FirewallForest(int numlevels, int *maxvals):Forest(numlevels, maxvals){

      FWCache = new Cache *[K + 1];

      for (int k = 0; k <= K; k++) {
         FWCache[k] = new Cache;
      } 
   }

   //Clean up data structures used by the forest
   ~FirewallForest() {
      for (level k = K; k >= 0; k--) {
         if (FWCache[k])
            delete FWCache[k];
      }
      delete[]FWCache;
   }

   int FindElement(MDDHandle p, Topology* T, int*& tup);
   node_idx InternalFindElement(level k, node_idx p, int* vals);
   int PrintElement(Topology* T, int* tup);

   int QueryIntersect(MDDHandle p, MDDHandle q, MDDHandle & result);
   node_idx InternalQIntersect(level k, node_idx p, node_idx q);
   int HistoryIntersect(MDDHandle p, MDDHandle q, MDDHandle & result);
   node_idx InternalHIntersect(level k, node_idx p, node_idx q);

   int Accepted(MDDHandle p, MDDHandle & result);
   node_idx InternalAccepted(level k, node_idx p);
   int Dropped(MDDHandle p, MDDHandle & result);
   node_idx InternalDropped(level k, node_idx p);

   int DisplayHistory(MDDHandle root, int* tup);
   int InternalDisplayHistory(level k, node_idx p, int* tup, int chain);

   int PrintHistory(MDDHandle p);
   void InternalPrintHistory(level k, node_idx p, int chain_num, int rule_num);

   int DNAT(MDDHandle p, nat_tuple * pnr, MDDHandle & result);
   node_idx InternalDNAT(level k, node_idx p, node_idx q, nat_tuple * pnr);
   int SNAT(MDDHandle p, nat_tuple * pnr, MDDHandle & result);
   node_idx InternalSNAT(level k, node_idx p, node_idx q, nat_tuple * pnr);
   int NETMAP(MDDHandle p, nat_tuple * pnr, MDDHandle & result);
   node_idx InternalNMAP(level k, node_idx p, node_idx q, nat_tuple * pnr);

   int BuildClassMDD(MDDHandle p, Forest* forest, MDDHandle & r,
                     int &numClasses, int services);
   int InternalBuildClassMDD(Forest* forest, level k, node_idx p,
                             int &numClasses, int services);
   
   int BuildServiceGraphMDD(MDDHandle p, Forest* forest, MDDHandle & r,
                     int &numArcs);
   int InternalBuildServiceGraphMDD(Forest* forest, level k, node_idx p,
                             int &numArcs);

   int JoinClasses(MDDHandle p, MDDHandle q, MDDHandle & r,
                   int &outNumClasses);
   node_idx InternalJoinClasses(level k, node_idx p, node_idx q,
                                int &numClasses);

   int PrintClasses(MDDHandle p, int numClasses);
   void InternalPrintClasses(level k, node_idx p, int *low, int *high,
                             int classNum);

   int PrintServiceClasses(MDDHandle p, int numClasses);
   void InternalPrintServiceClasses(level k, node_idx p, int *low, int *high,
                                    int classNum);

   int GetClasses(MDDHandle p, group ** &output, int numClasses);
   void InternalGetClasses(level k, node_idx p, int *low, int *high,
                           int classNum, group * head);

   int GetServiceClasses(MDDHandle p, service ** &output, int numClasses);
   void InternalGetServiceClasses(level k, node_idx p, int *low, int *high,
                                  int classNum, service * head);

   int GetServiceArcs(MDDHandle p, int* src, int* dst, service*&output, int& numArcs);
   int InternalGetServiceArcs(level k, node_idx p, int* src, int* dst,
      int* low, int* high, service*&output, int& numArcs);
  void PrintPort (MDDHandle h, level k);
  int PrintPort (level k, node_idx p, int highByte, int depth, portset * ps);
};

#endif
