#include "topology.h"

int Topology::FindInterface(char *name){
   int i;
   for (i=0;i<numIfaces;i++){
      if (strncmp(name, ifaces[i]->name, 256) == 0)
         return i;
   }
   return -1;
}

char* Topology::LookupInterface(int idx){
   if (idx<numIfaces)
      return ifaces[idx]->name;
   return NULL;
}

void Topology::PrintMapping(){
   printf("# ----------------------------------------------------\n");
   printf("# TOPOLOGY\n");
   for (int i=0; i<numIfaces;i++){
      printf("# %s %d.%d.%d.%d\n", ifaces[i]->name, 
            ifaces[i]->ip[0],
            ifaces[i]->ip[1],
            ifaces[i]->ip[2],
            ifaces[i]->ip[3]);
   }
   printf("# ----------------------------------------------------\n");
}
