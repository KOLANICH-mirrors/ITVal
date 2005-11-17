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

#ifndef FDDL_MDD_H
#   define FDDL_MDD_H 1

#   include <iostream>
#   include <assert.h>

#   include <FDDL/mddtypes.h>
#   include <FDDL/caches.h>
#   include <FDDL/dynarray.h>
#   include <FDDL/uniquetable.h>
#   include <FDDL/portset.h>

#   define ARC_STAR -1			  //For "FW mdds"

//#define FDDL_DEBUG

#   define O_LAZY 0
#   define O_STRICT 2

//Node Flag Values

#   define SHARED 1
#   define SPARSE 2
#   define DELETED 4
#   define CHECKED_IN 8
#   define SATURATED 16

//Useful Macros for accessing nodes and arc information

#   define FDDL_NODE(k,p) (*((*nodes[(k)])[(p)]))

#   define FULL_ARC(k,node,i) (*((*arcs[(k)])[(node)->down+(i)]))

#   define SPARSE_INDEX(k,node,i) (*((*arcs[(k)])[((node)->down+(2*(i)))]))
#   define SPARSE_ARC(k,node,i) (*((*arcs[(k)])[((node)->down+(2*(i)+1))]))

#   define IS_SPARSE(node) ((node->flags & SPARSE))
#   define IS_DELETED(node) ((node->flags & DELETED))

#   define FDDL_ARC(k,node, i) (IS_SPARSE(node) ? SPARSE_ARC(k,node,i) : FULL_ARC(k,node,i))

enum mdd_op_return_val {SUCCESS=0, TUPLE_OUT_OF_BOUNDS, INVALID_MDD, MAX_FAILED, MIN_FAILED, COMPLEMENT_FAILED, INVALID_LEVEL};

class fddl_forest;

class print_range{
   public:
      int low;
      int high;

      print_range(int l, int h){
        low = l;
        high = h;
      }
      void Print(){
         if (low==high)
            printf("%d", low);
         else if (low==0 && high==255)
            printf("*");
         else
            printf("[%d-%d]", low,high);
      }
      
};

extern fddl_forest *thisForest;

unsigned int ExternalHashNode(level k, node_idx p);
int     ExternalCompare(level k, node_idx p, node_idx q);

//An MDD node consists of two parts, a node struct stored in a node
//array, and a set of arcs stored in a per-level arc array.
class   node {
 public:
	char    flags;					  //Parameter flags (see above for values)
	int     down;					  //Index into the arc array of the first downpointer for this node
	int     size;					  //Number of arcs leaving this node.  If stored sparsely, 
	//the number of non zeros.
	int     in;						  //Number of incoming Arcs
	        node() {
		flags = 0;
		down = -1;
		size = 0;
		in = 0;
}};

class   val_list {
 public:
	int     low;
	int     high;
	val_list *next;
};
   
class print_node{
   int K;

   public:
   int *low;
   int *high;
   print_node* next;
   int *mV;

   print_node(int num_levels, int* maxVals){
      K = num_levels;
      low = new int[K+1];
      high = new int[K+1];
      mV = maxVals;
   }
   
   ~print_node(){
      delete[] low;
      delete[] high;
   }
 
   void Print(int* mask){
      char ch;
      for (int k=K;k>0;k--){
         if (mask[k] == 1){
            ch = ' ';
            if (k<=22 && k>=20)
               ch = '.';
            if (k<=18 && k>=13)
               ch = '.';
	         if (low[k] == high[k]){
               printf("[%d]%c", high[k],ch);
	         }
	         else if (low[k]==0 && high[k]==mV[k]){
               printf("*%c",ch);
	         }
	         else{
               printf("[%d-%d]%c", low[k], high[k], ch);
	         }
	      }
      }
      printf("\n");
   }
};


//The class fddl_forest stores a forest of MDDs with K levels, where K is
//chosen by the user.  By using a node-sharing technique, we store
//multiple MDDs relatively efficiently. 


class   fddl_forest {
   protected:
	int     K;						  //Number of Non-terminal Levels
	int    *tail;					  //Array [1..K] which records number of arcs per level.
	node_idx *last;				  //Array [1..K] which records number of nodes per level.
	int    *maxVals;				  //Array [0..K] of maximum values for each level.

	cache **ProjectCache;		  //Caches for embedded operations 
	cache **PruneCache;			  //Caches for embedded operations 
	cache **RestrictCache;
	cache **MaxCache;
	cache **MinCache;
	cache **ComplementCache;
	cache **BComplementCache;
	cache **LessThanCache;		  //Cache for "Less Than" operation
	cache **ValRestrictCache;	  //Cache for "ValRestrict" operation
	cache **CombineCache;
	cache **ReplaceCache;
	cache **ProjectOntoCache;
	cache **ReplaceStrictCache;
	tuple_cache **SelectCache;
	cache **PrintCache;

	int     Value(level k, node_idx p, int *tup);

   public:

	void    ReallocHandle(mdd_handle & ref);
	void    Attach(mdd_handle & ref, node_idx i) {
		ref.index = i;
		(*(*nodes[K])[i]).in++;
	} dynarray < node_idx >**node_remap_array;

	dynarray < node > **nodes;	  //An array [1..K] of heaps of MDD nodes.
	dynarray < node_idx >**arcs; //An array [1..L] of heaps of downpointers.

	//Build a new MDD forest of numlevels levels.
	//The domain of each level is specified as an integer range
	//from 0 to maxvals[k] inclusive.

	unsigned int hashnode(level k, node_idx p);
	int     compare(level k, node_idx p, node_idx q);

	fddl_forest(int numlevels, int *maxvals) {
		thisForest = this;
		node_remap_array = NULL;
		sparseEnabled = true;
		K = numlevels - 1;
		maxVals = new int[K + 1];

		for (level k = 0; k <= K; k++)
			maxVals[k] = maxvals[k];

		//Initialize structures for a dynamic array of MDD nodes and arcs
		//for each level of the forest.

		nodes = new dynarray < node > *[K + 1];
		arcs = new dynarray < node_idx >*[K + 1];

		for (int k = 1; k <= K; k++) {
			nodes[k] = new dynarray < node >;
			arcs[k] = new dynarray < node_idx >(0);
		}

		//Keep track of the last used position of the node and arc arrays
		//respectively.

		last = new node_idx[K + 1];
		tail = new int[K + 1];

		for (int k = 1; k <= K; k++) {
			last[k] = 1;			  //Node 0 is reserved.
			tail[k] = 0;
		}

		//Initialize caches for common operations
		node_remap_array = new dynarray < node_idx >*[K + 1];

		for (level k = K; k > 0; k--)
			node_remap_array[k] = NULL;

		MaxCache = new cache *[K + 1];
		ProjectCache = new cache *[K + 1];
		PruneCache = new cache *[K + 1];
		RestrictCache = new cache *[K + 1];
		MinCache = new cache *[K + 1];
		ComplementCache = new cache *[K + 1];
		BComplementCache = new cache *[K + 1];
		ValRestrictCache = new cache *[K + 1];
		LessThanCache = new cache *[K + 1];
		CombineCache = new cache *[K + 1];
		ReplaceCache = new cache *[K + 1];
		ProjectOntoCache = new cache *[K + 1];
		ReplaceStrictCache = new cache *[K + 1];
		PrintCache = new cache *[K + 1];
		SelectCache = new tuple_cache *[K + 1];

		for (int k = 1; k <= K; k++) {
			FDDL_NODE(k, 0).in = 0;
			FDDL_NODE(k, 0).size = 0;
			FDDL_NODE(k, 0).flags = 0;
			FDDL_NODE(k, 0).down = 0;
			ProjectCache[k] = new cache;
			PruneCache[k] = new cache;
			RestrictCache[k] = new cache;
			MaxCache[k] = new cache;
			MinCache[k] = new cache;
			ComplementCache[k] = new cache;
			BComplementCache[k] = new cache;
			ValRestrictCache[k] = new cache;
			LessThanCache[k] = new cache;
			CombineCache[k] = new cache;
			ReplaceCache[k] = new cache;
			ProjectOntoCache[k] = new cache;
			ReplaceStrictCache[k] = new cache;
			SelectCache[k] = new tuple_cache;
			PrintCache[k] = new cache;
		}

		//Create a hashtable of K levels to act as the Unique Table
		UT = new uniquetable(K, ExternalHashNode, ExternalCompare);
		garbage_alg = O_LAZY;
		garbage_threshold = 1;
	}

	//Clean up data structures used by the forest
	~fddl_forest() {
		for (level k = K; k > 0; k--) {
			if (nodes[k])
				delete  nodes[k];

			if (node_remap_array)
				if (node_remap_array[k])
					delete  node_remap_array[k];

			if (arcs[k])
				delete  arcs[k];

			if (ProjectCache[k])
				delete  ProjectCache[k];

			if (PruneCache[k])
				delete  PruneCache[k];

			if (RestrictCache[k])
				delete  RestrictCache[k];

			if (MaxCache[k])
				delete  MaxCache[k];

			if (MinCache[k])
				delete  MinCache[k];

			if (ComplementCache[k])
				delete  ComplementCache[k];

			if (BComplementCache[k])
				delete  BComplementCache[k];

			if (ValRestrictCache[k])
				delete  ValRestrictCache[k];

			if (LessThanCache[k])
				delete  LessThanCache[k];

			if (CombineCache[k])
				delete  CombineCache[k];

			if (ReplaceCache[k])
				delete  ReplaceCache[k];
			
                        if (ProjectOntoCache[k])
				delete  ProjectOntoCache[k];

			if (ReplaceStrictCache[k])
				delete  ReplaceStrictCache[k];

			if (SelectCache[k])
				delete  SelectCache[k];

			if (PrintCache[k])
				delete  PrintCache[k];
		}

		if (node_remap_array)
			delete[]node_remap_array;

		delete[]ProjectCache;
		delete[]PruneCache;
		delete[]RestrictCache;
		delete[]MaxCache;
		delete[]MinCache;
		delete[]ComplementCache;
		delete[]BComplementCache;
		delete[]ValRestrictCache;
		delete[]LessThanCache;
		delete[]CombineCache;
		delete[]ReplaceCache;
		delete[]ProjectOntoCache;
		delete[]ReplaceStrictCache;
		delete[]SelectCache;
		delete[]PrintCache;
		delete[]arcs;
		delete[]nodes;
		delete[]maxVals;
		delete[]last;
		delete[]tail;
		delete  UT;
	}
	int     Last(level k) {
		return last[k];
	}
	int     GetMaxVal(level k);
	int     ChangeMaxVal(level k, int maxval);

	int     MakeMDDFromTuple(int *low, int *high, mdd_handle & ref);
	int     Assign(mdd_handle root, int *low, int *high, mdd_handle & result);
	int     DestroyMDD(mdd_handle mdd);
	int     IsElementOf(mdd_handle root, int *tup, bool & result);
	int     Value(mdd_handle root, int *tup, int &result);

	int     Max(mdd_handle p, mdd_handle q, mdd_handle & result);
	int     Min(mdd_handle p, mdd_handle q, mdd_handle & result);
	int     Complement(mdd_handle p, mdd_handle & result);
	int     BinaryComplement(mdd_handle p, mdd_handle & result);
	int     LessThan(mdd_handle p, int value, mdd_handle & result);
	int     ValRestrict(mdd_handle p, int value, mdd_handle & result);
	int     Combine(mdd_handle p, mdd_handle q, int cache_index,
						 mdd_handle & result);
	int     Select(mdd_handle p, int num_chains, mdd_handle * chains,
						mdd_handle & result);
	
        int     Replace(mdd_handle p, mdd_handle q, bool strict,
						 mdd_handle & result);

	int     ProjectOnto(mdd_handle p, mdd_handle q, mdd_handle & result);


	void    PrintVals(mdd_handle root, level k);
	node_idx ProjectVals(level k, node_idx p, level cutoff);
   node_idx Projection(level k, node_idx p, level* mask);
	int     InternalPrintVals(level k, node_idx p);
	void    PrintPort(mdd_handle root, level k);
	void    PrintRanges(mdd_handle root, level* mask);
	void    PrintRanges(level k, node_idx p, level* mask, print_node*& stack, int* low, int* high);
	void    PrintAddy(mdd_handle root, level k);
	void    PrintAddy(level k, node_idx p, int *vals, int depth);
	int     PrintPort(level k, node_idx p, int highByte, int depth,
							portset * p);
	void    PrintStates(node_idx root);
	void    PrintStates(level k, node_idx root, int *states);
	void    PrintByRange(mdd_handle root);
	void    InternalPrintByRange(level k, node_idx root, val_list ** vals);

	int     CountNodes(node_idx);
	int     CountNodes(level k, node_idx p);
	int     ComputeMemUsed();
	int     RealMemUsed(node_idx);
	int     RealMemUsed(level k, node_idx p);

	void    ToggleSparsity(bool SparseSwitch);
	void    SetGarbageCollection(int alg, int threshold);
	void    PruneMDD(mdd_handle p);
	void    PruneMDD(node_idx p);
	void    PrintMDD();
	void    PrintMDD(int top, int bottom);

	//Functions to create, manipulate, and destroy MDD nodes.
	node_idx NewNode(level k);
	void    DeleteNode(level k, node_idx p);
	node_idx CheckIn(level k, node_idx p);
	int     UnpackNode(level k, arc_idx p, int *&fullarray);
	void    DeleteDownstream(level k, node_idx p);

	//Switch levels k1 and k2 in the MDD (maybe save space or time?)
	typedef struct state_triple {
		arc_idx from;
		arc_idx to;
		node_idx child;
	} state_triple;

	//Set <k:p>[i] = j, updating incoming arc information in the node
	//which the arc currently points to as well as the node we are 
	//assigning the arc to.
	void    SetArc(level k, node_idx p, arc_idx i, node_idx j);

	//Do Garbage Collection
	void    Compact(level k);
	void    CompactTopLevel();

	uniquetable *UT;				  //A special hashtable, the unique table, for storing

	//node information.

	node_idx InternalReplace(level k, node_idx p, node_idx q);
	node_idx InternalProjectOnto(level k, node_idx p, node_idx q);
	node_idx InternalReplaceStrict(level k, node_idx p, node_idx q);
	node_idx InternalRestrict(level k, node_idx p, node_idx q);
	node_idx InternalMax(level k, node_idx p, node_idx q);
	node_idx InternalMin(level k, node_idx p, node_idx q);
	node_idx InternalComplement(level k, node_idx p);
	node_idx InternalBComplement(level k, node_idx p);
	node_idx InternalLessThan(level k, node_idx p, int value);
	node_idx InternalValRestrict(level k, node_idx p, int value);
	node_idx InternalCombine(level k, node_idx p, node_idx q, int chain_index);
	node_idx InternalSelect(level k, node_idx p, int num_chains,
									node_idx *all_chains);
	void    InternalPruneMDD(level k, node_idx p, int flag);
	void    FlushCaches(level k);

	int     garbage_alg;
	int     garbage_threshold;
	bool    sparseEnabled;

	void    SaveMDD(char *filename);
	void    LoadMDD(char *filename);
};

#endif
