#include "PythonPipe.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int PythonPipe::OpenPipe(){
   pid_t myPid;
   char* inName;
   char* outName;
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
}

int PythonPipe::ReadList(PyList* l){
   PyList::node* cur;
   char* input;
   l = new PyList();
   input = ReadString();
   if (strncmp(input, "BeginList", 9))
      return -1;
   delete[] input;
   input = ReadString();
   while (strncmp(input, "EndList", 7)){
      cur = new PyList::node();
      cur->str = input;
      input = ReadString();
   }
   delete[] input;
   return 1;
}

int PythonPipe::WriteList(PyList* l){
    PyList::node* cur;
    char* output;
    int length;
   
    WriteString("BeginList\n");
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
    WriteString("EndList\n");
    return 1;
}

char* PythonPipe::ReadString(){
   char* line;
   line = new char[256];
   fgets(line, 256, inFile);
   return line;
}

int PythonPipe::WriteString(char* str){
   printf("Writing: %s\n", str);
   fprintf(outFile, "%s", str);
   fflush(outFile);
   printf("Wrote: %s\n", str);
}
