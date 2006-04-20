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

#ifndef SRC_FWMDD_H
#   define SRC_FWMDD_H 1

#   include <iostream>
#   include <assert.h>

#   include <FDDL/mdd.h>
#   include "nat.h"
#   include <FDDL/structures.h>

/*
 * The class fw_fddl_forest enhances the fddl_forest by providing
 * certain algorithms specific to firewall representation.  In 
 * particular, we provide algorithms for query intersection, 
 * NAT transformation of the firewall MDD and 
 * printing Firewall query results.
 */

class fw_fddl_forest:public fddl_forest {
 private:
   cache ** NMAPCache;                    //Caches for embedded operations 
   cache **DNATCache;                     //Caches for embedded operations 
   cache **SNATCache;                     //Caches for embedded operations 
   cache **QIntersectCache;
   cache **BuildCache;
   cache **JoinCache;

 public:

     fw_fddl_forest(int numlevels, int *maxvals):fddl_forest(numlevels,
                                                             maxvals) {
      NMAPCache = new cache *[K + 1];
      DNATCache = new cache *[K + 1];
      SNATCache = new cache *[K + 1];
      QIntersectCache = new cache *[K + 1];
      BuildCache = new cache *[K + 1];
      JoinCache = new cache *[K + 1];

      for (int k = 1; k <= K; k++) {
         NMAPCache[k] = new cache;
         DNATCache[k] = new cache;
         SNATCache[k] = new cache;
         QIntersectCache[k] = new cache;
         JoinCache[k] = new cache;
         BuildCache[k] = new cache;
      } JoinCache[0] = new cache;
   }

   //Clean up data structures used by the forest
   ~fw_fddl_forest() {
      for (level k = K; k > 0; k--) {
         if (NMAPCache[k])
            delete NMAPCache[k];
         if (DNATCache[k])
            delete DNATCache[k];
         if (SNATCache[k])
            delete SNATCache[k];
         if (QIntersectCache[k])
            delete QIntersectCache[k];
         if (JoinCache[k])
            delete JoinCache[k];
         if (BuildCache[k])
            delete BuildCache[k];
      }
      if (JoinCache[0])
         delete JoinCache[0];

      delete[]NMAPCache;
      delete[]DNATCache;
      delete[]SNATCache;
      delete[]BuildCache;
      delete[]JoinCache;
      delete[]QIntersectCache;
   }

   int QueryIntersect(mdd_handle p, mdd_handle q, mdd_handle & result);
   node_idx InternalQIntersect(level k, node_idx p, node_idx q);
   int DNAT(mdd_handle p, nat_tuple * pnr, mdd_handle & result);
   node_idx InternalDNAT(level k, node_idx p, node_idx q, nat_tuple * pnr);
   int SNAT(mdd_handle p, nat_tuple * pnr, mdd_handle & result);
   node_idx InternalSNAT(level k, node_idx p, node_idx q, nat_tuple * pnr);
   int NETMAP(mdd_handle p, nat_tuple * pnr, mdd_handle & result);
   node_idx InternalNMAP(level k, node_idx p, node_idx q, nat_tuple * pnr);

   int BuildClassMDD(mdd_handle p, fddl_forest * forest, mdd_handle & r,
                     int &numClasses, int services);
   int InternalBuildClassMDD(fddl_forest * forest, level k, node_idx p,
                             int &numClasses, int services);
   
   int BuildServiceGraphMDD(mdd_handle p, fddl_forest * forest, mdd_handle & r,
                     int &numArcs);
   int InternalBuildServiceGraphMDD(fddl_forest * forest, level k, node_idx p,
                             int &numArcs);

   int JoinClasses(mdd_handle p, mdd_handle q, mdd_handle & r,
                   int &outNumClasses);
   node_idx InternalJoinClasses(level k, node_idx p, node_idx q,
                                int &numClasses);

   int PrintClasses(mdd_handle p, int numClasses);
   void InternalPrintClasses(level k, node_idx p, int *low, int *high,
                             int classNum);

   int PrintServiceClasses(mdd_handle p, int numClasses);
   void InternalPrintServiceClasses(level k, node_idx p, int *low, int *high,
                                    int classNum);

   int GetClasses(mdd_handle p, group ** &output, int numClasses);
   void InternalGetClasses(level k, node_idx p, int *low, int *high,
                           int classNum, group * head);

   int GetServiceClasses(mdd_handle p, service ** &output, int numClasses);
   void InternalGetServiceClasses(level k, node_idx p, int *low, int *high,
                                  int classNum, service * head);

   int GetServiceArcs(mdd_handle p, int* src, int* dst, service*&output, int& numArcs);
   int InternalGetServiceArcs(level k, node_idx p, int* src, int* dst, int* low, int* high, service*&output, int& numArcs);
};

#endif
