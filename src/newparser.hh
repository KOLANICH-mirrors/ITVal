#define MAX_NAME_SIZE 44
#include "ranges.h"
#include <unistd.h>

enum NodeType{NODE_INVALID=-1,NODE_GROUP=1, NODE_SERVICE=2,NODE_QUERY=3,NODE_FOR=4};
enum ConditionType{TO_CONDITION,FROM_CONDITION,ON_CONDITION,FOR_CONDITION,IN_CONDITION,WITH_CONDITION,INFACE_CONDITION,OUTFACE_CONDITION,NOT_CONDITION,OR_CONDITION,AND_CONDITION};

typedef int StateType;
typedef int FlagType;

class Group{
   public:
      char name[MAX_NAME_SIZE];
      address_range* members;
      Group(){
         members = NULL;
      }
};

class Service{
   public:
      char name[MAX_NAME_SIZE];
      port_range* members;
      Service(){
         members = NULL;
      }
};

class Interface{
   public:
      char name[MAX_NAME_SIZE];
      int id;
      Interface(){
         id = -1;
      }
};

class Condition{
   ConditionType type;
   union{
      Condition* left; //Use with NOT
      Condition* right;//NULL with NOT
      Group* address;
      Service* port;
      Interface* iface;
      StateType state;
      FlagType flags;
   };
};

class Statement{
   public:
   Statement* next;
   NodeType type;
   Statement(){
      next = NULL;
      type = NODE_INVALID;
   }
};

class GroupStatement : public Statement{
    public:
       Group* member;
       GroupStatement() : Statement(){
          member = NULL;
       }
};

class ServiceStatement : public Statement{
    public:
       Service* member;

       ServiceStatement() : Statement(){
          member = NULL;
       }
};

class QueryStatement : public Statement{
   public:
      int subject;
      int chain;
      Condition* condition;
      QueryStatement() : Statement(){
	 chain = -1;
	 subject = -1; //Forward??
         condition = NULL;
      }
};

class ForStatement : public Statement{
   public:
      char varName[MAX_NAME_SIZE];
      NodeType type;
      union{
         Group* groupMember;
	 Service* serviceMember;
      };
      Statement* body;
      ForStatement() : Statement(){
         type = NODE_INVALID;
      }
};
