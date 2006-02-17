#include "PythonPipe.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char* Addy2Text(address* g){
   char* name;
  
   name = new char[256];
   sprintf(name, "%d-%d.%d-%d.%d-%d.%d-%d\n", 
         g->low[0], g->high[0], g->low[1], g->high[1], g->low[2], 
         g->high[2], g->low[3], g->high[3]);
   return name;
}

char* Port2Text(port* p){
   char* name;
  
   name = new char[256];
   sprintf(name, "%d-%d\n", p->low, p->high);
   return name;
}

int PythonPipe::OpenPipe(){
   pid_t myPid;
   char prefix[5];

   //Create two FIFO queues with unique names that start with "ITV"
   
   strncpy(prefix, "ITV", 5);
   inName = tempnam("/tmp/", prefix);
   outName = tempnam("/tmp/", prefix);

   if (mkfifo(inName, 0666) < 0){
      perror("xITVal");
      return -1;
   }

   if (mkfifo(outName, 0666) < 0){
      perror("xITVal");
      return -1;
   }

   //Fork off a child and exec the GUI code, connecting the FIFO queues to the child process.
   
   myPid = fork();
   if (myPid < 0){
      perror("xITVal");
      return -1;
   }
   if (myPid == 0){ //Child
      if (execlp("/home/robert/ITVal/gui/gui.py", "/home/robert/ITVal/gui/gui.py", outName, inName, NULL) != 0){
         perror("xITVal");
         return -1;
      }
   }

   //Open the files
   inFile = fopen(inName, "r");
   if (!inFile){
      perror("xITVal");
      return -1;
   }

   outFile = fopen(outName, "w");
   if (!outFile){
      perror("xITVal");
      return -1;
   }
   
   return 1;
}

int PythonPipe::ClosePipe(){
   fclose(inFile);
   fclose(outFile);
   unlink(inName);
   unlink(outName);
   free(inName);
   free(outName);
}

int PythonPipe::ReadList(PyList*& l){
   PyList::node* cur;
   char* input;
   int size;
   
   l = new PyList();
   size = 0;
   
   input = ReadString();
   if (strncmp(input, "Begin List", 9))
      return -1;

   delete[] input;
   input = ReadString();
   while (strncmp(input, "End List", 7)){
      cur = new PyList::node();
      cur->str = input;
      input = ReadString();
      cur->next = l->head;
      l->head = cur;
      size++;
   }
   delete[] input;
   return size;
}

int PythonPipe::WriteClasses(group** classes, int num_classes){
   address* cur;
   WriteString("Begin Classes\n");
   for (int i=0;i<num_classes;i++){
      WriteString(classes[i]->name);
      WriteString("\n");
      WriteString("Begin Addresses\n");
      cur = classes[i]->list;
      while (cur != NULL){
         WriteString(Addy2Text(cur));
         cur = cur->next;
      }
      WriteString("End Addresses\n");
   }
   WriteString("End Classes\n");
}

int PythonPipe::WriteServiceClasses(service** classes, int num_classes){
   port* cur;
   WriteString("Begin Classes\n");
   for (int i=0;i<num_classes;i++){
      WriteString(classes[i]->name);
      WriteString("\n");
      WriteString("Begin Addresses\n");
      cur = classes[i]->list;
      while (cur != NULL){
         WriteString(Port2Text(cur));
         cur = cur->next;
      }
      WriteString("End Addresses\n");
   }
   WriteString("End Classes\n");
}

int PythonPipe::WriteList(PyList* l){
    PyList::node* cur;
    char* output;
    int length;
   
    WriteString("Begin List\n");
    cur = l->head;
    while (cur != NULL){
       if (cur->str == NULL)
          return 0;
       length = strlen(cur->str);
       output = new char[length+1];
       strncpy(output,cur->str, length);
       output[length]='\n';
       WriteString(output);
       delete[] output;
       output = NULL;
       cur = cur->next;
    }
    WriteString("End List\n");
    return 1;
}

char* PythonPipe::ReadString(){
   char* line;
   int length;
   line = new char[256];
   fgets(line, 256, inFile);
   length = strlen(line);
   if (length == 0)
      return NULL;
   line[length-1]='\0';
   return line;
}

int PythonPipe::WriteString(char* str){
   fprintf(outFile, "%s", str);
   fflush(outFile);
}
