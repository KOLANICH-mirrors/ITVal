#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class PyList{
   
   public:

      class node{
         public:
            char* str;
            node* next;
            node* prev;
            node(){
               str = NULL;
               next = NULL;
               prev = NULL;
            }
      };
   
      int numItems;
      node* head;
      node* tail;

      PyList(){
         numItems = 0;
         head = NULL;
         tail = NULL;
      }
      
      ~PyList(){
         node* cur;
         while (head != NULL){
            cur = head;
            head = head->next;
            delete[] cur->str;
            delete cur;
         }

      }
      
      int AddItem(char* item){
         node* newNode;
         int length;
         
         length = strlen(item);

         if (length > 0){
            newNode = new node;
            newNode->str = new char[length+1];
            strncpy(newNode->str, item, length+1);
            
            if (tail == NULL){
               tail = newNode;
            }
            
            newNode->next = head;

            if (head != NULL){
               head->prev = newNode;
            }

            head = newNode;
            numItems++;
         }
      }
};

class PythonPipe{
      char* inName;
      char* outName;
      FILE* inFile;
      FILE* outFile;
   public:
      int OpenPipe();
      int ClosePipe();
      int ReadList(PyList*& l);
      int WriteList(PyList* l);
      char* ReadString();
      int WriteString(char* str);
};
