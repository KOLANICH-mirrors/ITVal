
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

#include <stdio.h>
#include <assert.h>
#include "fwmdd.h"

#define MAX(a, b) (a>b ? a : b)
#define MIN(a, b) (a<b ? a : b)

int
fw_fddl_forest::QueryIntersect (mdd_handle root, mdd_handle root2,
				mdd_handle & result)
{
  if (root.index < 0)
    return INVALID_MDD;
  if (root2.index < 0)
    return INVALID_MDD;
  node_idx newresult;

  for (level k = K; k > 0; k--)
  {
    QIntersectCache[k]->Clear ();
  }
  newresult = InternalQIntersect (K, root.index, root2.index);
  if (result.index != newresult)
  {
    ReallocHandle (result);
    Attach (result, newresult);
  }
  return 0;
}

int
fw_fddl_forest::SNAT (mdd_handle root, nat_tuple * pnr, mdd_handle & result)
{
  if (root.index < 0)
    return INVALID_MDD;
  if (pnr == NULL)
    return 0;
  node_idx newresult;

  for (level k = K; k > 0; k--)
  {
    SNATCache[k]->Clear ();
  }
  newresult = InternalSNAT (K, root.index, root.index, pnr);
  if (result.index != newresult)
  {
    ReallocHandle (result);
    Attach (result, newresult);
  }
  return 0;
}

int
fw_fddl_forest::DNAT (mdd_handle root, nat_tuple * pnr, mdd_handle & result)
{
  if (root.index < 0)
    return INVALID_MDD;
  if (pnr == NULL)
    return 0;
  node_idx newresult;

  for (level k = K; k > 0; k--)
  {
    DNATCache[k]->Clear ();
  }
  newresult = InternalDNAT (K, root.index, root.index, pnr);
  if (result.index != newresult)
  {
    ReallocHandle (result);
    Attach (result, newresult);
  }
  return 0;
}

int
fw_fddl_forest::NETMAP (mdd_handle root, nat_tuple * pnr, mdd_handle & result)
{
  if (root.index < 0)
    return INVALID_MDD;
  if (pnr == NULL)
    return 0;
  node_idx newresult;

  for (level k = K; k > 0; k--)
  {
    NMAPCache[k]->Clear ();
  }
  newresult = InternalNMAP (K, root.index, root.index, pnr);
  if (result.index != newresult)
  {
    ReallocHandle (result);
    Attach (result, newresult);
  }
  return 0;
}

node_idx
  fw_fddl_forest::InternalSNAT (level k, node_idx p, node_idx q,
				nat_tuple * pnr)
{
  //Node p is the original address.
  //Node q is the NATTed address.
  arc_idx i;
  node_idx result, u;
  node *nodeP;
  node *nodeQ;
  node *nodeR;
  int psize;
  int qsize;

  if (k < 12)
  {				//If we're beyond the source port
    //return the node pointed to by the NATted address.
    result = CheckIn (k, q);
    return result;
  }

  //If cached, return the cached result.
  result = SNATCache[k]->Hit (p, q);
  if (result >= 0)
    return result;

  result = NewNode (k);

  nodeR = &FDDL_NODE (k, result);

  if (k >= 19 || k < 14)
  {				//If it's a source address node
    if (p != 0)
    {				//And it's not zero.
      nodeP = &FDDL_NODE (k, p);
      for (int i = 0; i < pnr->low[k]; i++)
      {				//For arcs before the range, copy P.
	node_idx pchild;

	if (i < nodeP->size)
	  pchild = FDDL_ARC (k, nodeP, i);
	else
	  pchild = 0;
	SetArc (k, result, i, pchild);
      }

      for (int i = pnr->high[k] + 1; i <= maxVals[k]; i++)
      {				//For arcs after the range, copy P.
	node_idx pchild;

	if (i < nodeP->size)
	  pchild = FDDL_ARC (k, nodeP, i);
	else
	  pchild = 0;
	SetArc (k, result, i, pchild);
      }
    }

    for (int i = pnr->low[k]; i <= pnr->high[k]; i++)
    {				//Addresses in the range, NAT.
      nat_range *cur;

      cur = pnr->nat;
      node_idx pchild;
      node_idx qchild;

      if (p == 0)
	pchild = 0;
      else
      {
	nodeP = &FDDL_NODE (k, p);
	if (i < nodeP->size)
	  pchild = FDDL_ARC (k, nodeP, i);
	else
	  pchild = 0;
      }

      node_idx rchild;

      if (i < nodeR->size)
	rchild = FDDL_ARC (k, nodeR, i);
      else
	rchild = 0;

      while (cur != NULL)
      {				//Need a while loop, because NAT rules can load balance.
	nodeQ = &FDDL_NODE (k, q);
	for (int j = cur->low[k]; j <= cur->high[k]; j++)
	{
	  if (j < nodeQ->size)
	    qchild = FDDL_ARC (k, nodeQ, j);
	  else
	    qchild = 0;
	  u = InternalMax (k - 1, rchild,
			   InternalSNAT (k - 1, pchild, qchild, pnr));
	  SetArc (k, result, i, u);
	}
	cur = cur->next;
      }
    }
  }
  else
  {				//Otherwise, just recurse.
    node_idx pchild;
    node_idx qchild;

    nodeP = &FDDL_NODE (k, p);
    nodeQ = &FDDL_NODE (k, q);
    for (arc_idx i = 0; i <= maxVals[k]; i++)
    {
      if (i < nodeP->size)
	pchild = FDDL_ARC (k, nodeP, i);
      else
	pchild = 0;
      if (i < nodeQ->size)
	qchild = FDDL_ARC (k, nodeQ, i);
      else
	qchild = 0;
      u = InternalSNAT (k - 1, pchild, qchild, pnr);
      SetArc (k, result, i, u);
    }
  }
  result = CheckIn (k, result);
  SNATCache[k]->Add (p, q, result);
  return result;
}

node_idx
  fw_fddl_forest::InternalDNAT (level k, node_idx p, node_idx q,
				nat_tuple * pnr)
{
  //Node p is the original address.
  //Node q is the NATTed address.
  arc_idx i;
  node_idx result, u;
  node *nodeP;
  node *nodeQ;
  node *nodeR;
  int psize;
  int qsize;

  if (k < 10)
  {				//If we're beyond the destination and port
    //return the node pointed to by the NATted address.
    result = CheckIn (k, q);
    return result;
  }

  //If cached, return the cached result.
  result = DNATCache[k]->Hit (p, q);
  if (result >= 0)
    return result;

  result = NewNode (k);

  nodeR = &FDDL_NODE (k, result);

  if (k > 18)
  {
    assert (p == q);

    if (q == 0)			//If no address to NAT to, return 0.
      return 0;

    nodeQ = &FDDL_NODE (k, q);
    qsize = nodeQ->size;

    for (int i = 0; i <= maxVals[k]; i++)
    {
      node_idx child;
      node_idx rnode;

      if (i < nodeQ->size)
	child = FDDL_ARC (k, nodeQ, i);
      else
	child = 0;
      rnode = InternalDNAT (k - 1, child, child, pnr);
      SetArc (k, result, i, rnode);
    }
  }
  else
  {
    if (p != 0)
    {
      nodeP = &FDDL_NODE (k, p);
      for (int i = 0; i < pnr->low[k]; i++)
      {
	node_idx pchild;

	if (i < nodeP->size)
	  pchild = FDDL_ARC (k, nodeP, i);
	else
	  pchild = 0;
	SetArc (k, result, i, pchild);
      }
      for (int i = pnr->high[k] + 1; i <= maxVals[k]; i++)
      {
	node_idx pchild;

	if (i < nodeP->size)
	  pchild = FDDL_ARC (k, nodeP, i);
	else
	  pchild = 0;
	SetArc (k, result, i, pchild);
      }
    }
    for (int i = pnr->low[k]; i <= pnr->high[k]; i++)
    {
      nat_range *cur;

      cur = pnr->nat;
      node_idx pchild;
      node_idx qchild;

      if (p == 0)
	pchild = 0;
      else
      {
	nodeP = &FDDL_NODE (k, p);
	if (i < nodeP->size)
	  pchild = FDDL_ARC (k, nodeP, i);
	else
	  pchild = 0;
      }

      node_idx rchild;

      if (i < nodeR->size)
	rchild = FDDL_ARC (k, nodeR, i);
      else
	rchild = 0;

      while (cur != NULL)
      {
	nodeQ = &FDDL_NODE (k, q);
	for (int j = cur->low[k]; j <= cur->high[k]; j++)
	{
	  if (j < nodeQ->size)
	    qchild = FDDL_ARC (k, nodeQ, j);
	  else
	    qchild = 0;
	  u = InternalMax (k - 1, rchild,
			   InternalDNAT (k - 1, pchild, qchild, pnr));
	  SetArc (k, result, i, u);
	}
	cur = cur->next;
      }
    }
  }
  result = CheckIn (k, result);
  DNATCache[k]->Add (p, q, result);
  return result;
}

node_idx
  fw_fddl_forest::InternalNMAP (level k, node_idx p, node_idx q,
				nat_tuple * pnr)
{				//MODIFY!
  //Node p is the original address.
  //Node q is the NATTed address.

  arc_idx i;
  node_idx result, u;
  node *nodeP;
  node *nodeQ;
  node *nodeR;
  int psize;
  int qsize;

  if (k < 10)
  {				//If we're beyond the destination and port
    //return the node pointed to by the NATted address.
    result = CheckIn (k, q);
    return result;
  }

  //If cached, return the cached result.
  result = NMAPCache[k]->Hit (p, q);
  if (result >= 0)
    return result;

  result = NewNode (k);

  nodeR = &FDDL_NODE (k, result);

  if (k > 18)
  {
    assert (p == q);

    if (q == 0)			//If no address to NAT to, return 0.
      return 0;

    nodeQ = &FDDL_NODE (k, q);
    qsize = nodeQ->size;

    for (int i = 0; i <= maxVals[k]; i++)
    {
      node_idx child;
      node_idx rnode;

      if (i < nodeQ->size)
	child = FDDL_ARC (k, nodeQ, i);
      else
	child = 0;
      rnode = InternalNMAP (k - 1, child, child, pnr);
      SetArc (k, result, i, rnode);
    }
  }
  else
  {
    if (p != 0)
    {
      nodeP = &FDDL_NODE (k, p);
      for (int i = 0; i < pnr->low[k]; i++)
      {
	node_idx pchild;

	if (i < nodeP->size)
	  pchild = FDDL_ARC (k, nodeP, i);
	else
	  pchild = 0;
	SetArc (k, result, i, pchild);
      }
      for (int i = pnr->high[k] + 1; i <= maxVals[k]; i++)
      {
	node_idx pchild;

	if (i < nodeP->size)
	  pchild = FDDL_ARC (k, nodeP, i);
	else
	  pchild = 0;
	SetArc (k, result, i, pchild);
      }
    }
    for (int i = pnr->low[k]; i <= pnr->high[k]; i++)
    {
      nat_range *cur;

      cur = pnr->nat;
      node_idx pchild;
      node_idx qchild;

      if (p == 0)
	pchild = 0;
      else
      {
	nodeP = &FDDL_NODE (k, p);
	if (i < nodeP->size)
	  pchild = FDDL_ARC (k, nodeP, i);
	else
	  pchild = 0;
      }

      node_idx rchild;

      if (i < nodeR->size)
	rchild = FDDL_ARC (k, nodeR, i);
      else
	rchild = 0;

      while (cur != NULL)
      {
	nodeQ = &FDDL_NODE (k, q);
	for (int j = cur->low[k]; j <= cur->high[k]; j++)
	{
	  if (j < nodeQ->size)
	    qchild = FDDL_ARC (k, nodeQ, j);
	  else
	    qchild = 0;
	  u = InternalMax (k - 1, rchild,
			   InternalNMAP (k - 1, pchild, qchild, pnr));
	  SetArc (k, result, i, u);
	}
	cur = cur->next;
      }
    }
  }
  result = CheckIn (k, result);
  NMAPCache[k]->Add (p, q, result);
  return result;
}

node_idx fw_fddl_forest::InternalQIntersect (level k, node_idx p, node_idx q)
{
  arc_idx i;
  node_idx result, u;
  node * nodeP, * nodeQ;
  int psize, qsize;
  int dummy;
  arc_idx * ptemp;
  arc_idx * qtemp;

  if (p == 0)
    return 0;			//If it's not accepted
  if (q == 0)
    return 0;			//Or not relevant to the query
  if (k == 0)
  {
    if (q == 2)
      return 1;			//If it's a log rule return 1.
    if (p == 3 && q == 1)
    {				//If it's relevant and accepted.
      return 1;
    }
    return 0;
  }
  result = QIntersectCache[k]->Hit (p, q);
  if (result >= 0)
    return result;

  result = NewNode (k);
  nodeP = &FDDL_NODE (k, p);
  nodeQ = &FDDL_NODE (k, q);

  if (IS_SPARSE (nodeP))
  {				//If node <k.p> is stored sparsely, unpack it into a static array of appropriate size
    psize = UnpackNode (k, p, ptemp);
  }
  else
  {
    psize = nodeP->size;
    ptemp = new node_idx[psize];

    for (i = 0; i < psize; i++)
      ptemp[i] = FULL_ARC (k, nodeP, i);
  }
  if (IS_SPARSE (nodeQ))
  {				//If node <k.q> is stored sparsely, unpack it into a static array of appropriate size
    qsize = UnpackNode (k, q, qtemp);
  }
  else
  {
    qsize = nodeQ->size;
    qtemp = new node_idx[qsize];

    for (i = 0; i < qsize; i++)
      qtemp[i] = FULL_ARC (k, nodeQ, i);
  }
  for (i = 0; i <= maxVals[k]; i++)
  {
    u = InternalQIntersect (k - 1, i < psize ? ptemp[i] : 0,
			    i < qsize ? qtemp[i] : 0);
    SetArc (k, result, i, u);
  }
  delete[]qtemp;
  delete[]ptemp;
  result = CheckIn (k, result);
  QIntersectCache[k]->Add (p, q, result);
  return result;
}

int fw_fddl_forest::ExtractClasses(mdd_handle p, eClass*& output, int& numClasses){
   eClass* cur;
	int* low;
	int* high;
	low = new int[4];
	high = new int[4];
//   printf("Warning: Class Extraction has not yet been implemented.\n");
	numClasses = 0;
	PrintMDD();
   output = NULL;
   InternalExtract(K, p.index, low, high, output, numClasses);
   delete[] low;
   delete[] high;
	return 1;
}

int fw_fddl_forest::InternalExtract(level k, node_idx p, int* low, int* high, eClass*& output, int& numClasses){
   node* nodeP;
	printf("Extracting <%d,%d>\n", k, p);
	nodeP = &FDDL_NODE(k,p);
	if (k==19){ //Level fourth from the top is special.
		int lastVal;
		int first;
	   eClass* newClass;
		eClass::eNode* node;
		newClass = new eClass;
		if (output == NULL)
		   newClass->head = NULL;
		else
		   newClass->head = output->head;	

		first = 0;
      lastVal = FDDL_ARC(k,nodeP,0);
      for (int i=0;i<nodeP->size;i++){
         if (lastVal != FDDL_ARC(k,nodeP,i)){
		      low[22-k] = first;
			   high[22-k] = i;
				node = new eClass::eNode;
				numClasses++;
				node->next = newClass->head;
				for (int j=0;j<4;j++){
				   node->high[j]=high[j];
				   node->low[j]=low[j];
				}
				newClass->head = node;
            first = i;
				lastVal = FDDL_ARC(k,nodeP,i);
			}
		}
      if (lastVal == FDDL_ARC(k,nodeP, nodeP->size-1)){
		   low[22-k] = first;
			high[22-k] = nodeP->size-1;
			node = new eClass::eNode;
			numClasses++;
			node->next = newClass->head;
			for (int j=0;j<4;j++){
			   node->high[j]=high[j];
				node->low[j]=low[j];
			}
			newClass->head = node;
		}
		output = newClass;
	}
	else{
		int lastVal;
		int first;
		first = 0;
      lastVal = FDDL_ARC(k,nodeP,0);
      for (int i=0;i<nodeP->size;i++){
         if (lastVal != FDDL_ARC(k,nodeP,i)){
		      low[22-k] = first;
			   high[22-k] = i;
			   InternalExtract(k-1, FDDL_ARC(k,nodeP,i),low,high,output,numClasses);	
            first = i;
				lastVal = FDDL_ARC(k,nodeP,i);
			}
		}
		if (lastVal == FDDL_ARC(k,nodeP,nodeP->size-1)){
		      low[22-k] = first;
			   high[22-k] = nodeP->size-1;
			   InternalExtract(k-1, FDDL_ARC(k,nodeP,nodeP->size-1),low,high,output,numClasses);	
		}
	}
   return 1;
}
void eClass::Print(){
			eNode* cur;
			char ch;

			cur = head;
			printf("%s: \n", name);
			while (cur != NULL){
			   printf("   ");
			   ch = '.';
            for (int i=0;i<4;i++){
					if (i==3)
					   ch = '\n';
               printf("%d-%d%c", cur->low[i],cur->high[i],ch);
		}
	   cur = cur->next;
   }
}
