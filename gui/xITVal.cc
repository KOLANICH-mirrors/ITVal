#include "PythonPipe.h"
#include "../src/firewall.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int BuildMetaFirewall(PythonPipe* pp, Firewall*& mf){
   Firewall** fws;
   int num_fws;
   fw_fddl_forest* f;
   PyList *filters = NULL;
   PyList *nats = NULL;
   PyList *tops = NULL;
   PyList::node *curFilter;
   PyList::node *curNAT;
   PyList::node *curTop;
   Topology* top;
   int i;
   
   int ranges[23] = { 256,       /* Target Chain                 */
       1, 1, 1, 1, 1, 1,           /* Flags (FIN, SYN, RST, PSH, ACK, URG) */
       3,                          /* Connection State             */
       255, 255,                   /* Output and Input Interface   */
       255, 255,                   /* Destination Port             */
       255, 255,                   /* Source Port                  */
       2,                          /* Protocol                     */
       255, 255, 255, 255,         /* Destination Address          */
       255, 255, 255, 255          /* Source Address               */
   };
 
   
   f = new fw_fddl_forest(23, ranges);
   f->ToggleSparsity(false); //Fix this @BUG@ later.

   
   pp->WriteString("Send Filter Names\n");
   num_fws = pp->ReadList(filters);
   if (num_fws<0){
      printf("Error: Reading List Failed in \"BuildMetaFirewall\"\n");
      exit(-1);
   }

   pp->WriteString("Send NAT Names\n");
   if (pp->ReadList(nats) != num_fws){
      printf("Error: Not enough NAT rule files\n");
      exit(-1);
   }

   pp->WriteString("Send Topology Names\n");
   if (pp->ReadList(tops) != num_fws){
      printf("Error: Not enough Topology files\n");
      exit(-1);
   }
   
   fws = new Firewall*[num_fws];
   
   curFilter = filters->head;
   curNAT = nats->head;
   curTop = tops->head;
   i = 0;
   while (curFilter != NULL){
      if (!strncmp(curTop->str, "NOTOP", 5)){
         top = NULL;
      }
      else{
         top = new Topology(curTop->str);
      }
      fws[i] = new Firewall (curFilter->str, curNAT->str, f, top, 1);
      i = i + 1;
      curFilter = curFilter->next;
      curNAT = curNAT->next;
      curTop = curTop->next;
   }
   delete filters;
   delete nats;
   delete tops;
   
   mf = MergeFWs(f, fws, num_fws);
   for (i=0;i<num_fws;i++){
      delete fws[i];
   }
   delete[] fws;
   if (!mf){
      printf("No firewalls to merge!\n");
      return -2;
   }
}

int main ( void ){
   char* cmd = NULL;
   PythonPipe* pp = NULL;
   Firewall* fw; 
   
   pp = new PythonPipe();
   
   if (pp->OpenPipe() <0){
      exit(-1);
   }

   while (cmd == NULL || (strncmp(cmd, "QUIT", 4) != 0)){
      cmd = pp->ReadString();
      printf("GotCommand: %s\n", cmd);
      if (!strncmp(cmd, "Get Classes", 11)){
         BuildMetaFirewall(pp, fw);
         fw->PrintClasses();
      }
   }
   
   pp->ClosePipe();

   delete pp;
   delete[] cmd;
}
