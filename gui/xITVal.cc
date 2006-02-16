#include "PythonPipe.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main ( void ){
   char* cmd = NULL;
   PythonPipe* pp = NULL;
   PyList *filters = NULL;
   PyList *nats = NULL;
   
   pp = new PythonPipe();
   
   if (pp->OpenPipe() <0){
      exit(-1);
   }

   while (cmd == NULL || (strncmp(cmd, "QUIT", 4) != 0)){
      cmd = pp->ReadString();
      printf("GotCommand: %s\n", cmd);
      if (!strncmp(cmd, "Get Classes", 11)){
         pp->WriteString("Send Filter Names\n");
         pp->ReadList(filters);
         pp->WriteString("Send NAT Names\n");
         pp->ReadList(nats);
      }
   }

   delete nats;
   delete filters;
   delete pp;
   delete[] cmd;
}
