#ifndef TOPOLOGY_H__
#define TOPOLOGY_H__
#include <stdio.h>
#include <string.h>

class Interface{
   public:
   char name[256];
   int index; 
   int ip[4];
   Interface(char* n, int* address){
      strncpy(name, n, 256);
      for (int i=0;i<4;i++)
         ip[i] = address[i];
   }
};

class Topology{
	
   private:
   int numIfaces;
   Interface** ifaces;

   public:
   int FindInterface(char *name);
   char* LookupInterface(int idx);
   void PrintMapping();
   
   Topology(char* fname)
   {
      FILE* iFile;
      char name[256];
      int ip[4];
      numIfaces = 0;
      ifaces = new Interface*[256];
      iFile = fopen(fname, "r");
      if (!iFile)
         return;
      while (EOF != fscanf(iFile, "%256s %3d.%3d.%3d.%3d", name, &ip[0], &ip[1],
			      &ip[2], &ip[3]))
      {
         ifaces[numIfaces] = new Interface(name, ip);
	      numIfaces++;
         if (numIfaces>256){
		 printf("Warning: ITVal cannot handle more than 256 interfaces!\n");
		 return;
	 }
      }
      fclose(iFile);
   }
   ~Topology(){
      for (int i=0;i<numIfaces;i++)
	      delete ifaces[i];
      delete[] ifaces;
   }
};
#endif 
