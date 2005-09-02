%{
int yylex();
int yyerror(char* str);
#include "structures.h"
%}

%union{
   int input_chain;
   char dummy;
   group* group_rec;
   service* service_rec;
   query* query_rec;
   condition* condition_rec;
   int sub;
   int sv;
   int fv;
   port* port_rec;
   char *name;
   address* address_rec;
   int prot;
   char* val;
}

%left <group_rec> GROUP
%left <service_rec> SERVICE
%left <query_rec> QUERY

%token <input_chain> INPUT FORWARD OUTPUT
%token <sub> PACKET SPORT DPORT SADDY DADDY STATE
%token <prot> UDP TCP ICMP BOTH
%token <val> NUM
%token <char> DOT

%token <condition_rec> LOGGED
%token <sv> T_INVALID T_NEW T_ESTABLISHED T_RELATED
%token <fv> FIN SYN RST PSH ACK URG
%type <address_rec> addr
%token <name> NAME
%type <port_rec> port
%type <service_rec> compound_port
%type <port_rec> complete_port
%type <group_rec> compound_addy
%type <condition_rec> simple_condition
%type <sv> state_value
%type <fv> flag_name 
%type <condition_rec> condition
%type <sub> subject
%type <input_chain> input_chain
%type <prot> protocol
%type <query_rec> query_expression
%type <service_rec> service_expression

%type <group_rec> group_expression
%type <address_rec> addy_list
%type <port_rec> port_list 

%token <dummy> LPAREN RPAREN SEMI
%left <condition_rec> AND
%left <condition_rec> OR 
%right <condition_rec> NOT
%left <condition_rec> FROM TO FOR ON IN WITH 

%%
statement: expression | expression statement;
expression: group_expression SEMI 
        | service_expression SEMI 
        | query_expression SEMI
        | SEMI
        ;
        
group_expression: GROUP NAME addy_list {$$ = DefineGroup($2, $3);};

service_expression: SERVICE NAME port_list {$$ = DefineService($2, $3);};

addy_list: addy_list addr {$$ = AppendAddy($1,$2);}
            | addr {$$ = AppendAddy(NULL, $1);};

port_list: port_list complete_port {$$ = AppendPort($1, $2);}
            | complete_port {$$ = AppendPort(NULL, $1);};

query_expression:  QUERY subject condition {$$ = PerformQuery($2, $3, 1);}
          | QUERY subject input_chain condition{$$ = PerformQuery($2, $4, $3)} ;

input_chain: INPUT {$$ = 0;}
           | FORWARD {$$ = 1;}
           | OUTPUT {$$ = 2;};

subject: PACKET{$$=0;} 
       | SPORT{$$=1;} 
       | DPORT{$$=2;} 
       | SADDY{$$=3;} 
       | DADDY{$$=4;} 
       | STATE{$$=5;}
       ;

condition: simple_condition {$$ = $1;}
        | condition AND condition {$$ = IntersectConditions($1,$3);}
        | condition OR condition {$$ = UnionConditions($1,$3);}
        | NOT condition {$$ = NegateCondition($2);}
        | LPAREN condition RPAREN {$$ = $2;}
        | LOGGED { $$ = GetLoggedCondition();}
        ;
        
simple_condition: FROM compound_addy {$$=BuildConditionFromGroup($2, 0);}
        | TO compound_addy {$$=BuildConditionFromGroup($2,1);}
        | ON compound_port {$$=BuildConditionFromService($2, 0);}
        | FOR compound_port {$$=BuildConditionFromService($2, 1);}
        | IN state_value {$$=BuildConditionFromState($2);}
        | WITH flag_name {$$=BuildConditionFromFlag($2);}
        ;

compound_addy: NAME {$$ = GroupLookup($1);}
                | addr {$$ = BuildGroupFromAddress($1);};

compound_port: NAME {$$ = ServiceLookup($1);}
                | complete_port {$$ = BuildServiceFromPort($1);};

state_value: T_INVALID{$$=0;} | T_NEW{$$=1;} | T_ESTABLISHED{$$=2;} | T_RELATED{$$=3;};

flag_name: FIN {$$=0;}| SYN {$$=1;}| RST {$$=2;}| PSH {$$=3;}| ACK{$$=4;} | URG {$$=5;};

complete_port: protocol port {$$ = BuildPort($1, $2);};

protocol: ICMP {$$ = 0;} | UDP {$$ = 1;} | TCP { $$ = 2;} | BOTH { $$ = -1;};

addr: NUM DOT NUM DOT NUM DOT NUM {$$ = ParseAddr($1,$3,$5,$7);} 
    | NUM DOT NUM DOT NUM {$$=ParseAddr($1,$3,$5,NULL);} 
    | NUM DOT NUM{$$=ParseAddr($1,$3,NULL,NULL);} 
    | NUM {$$=ParseAddr($1,NULL,NULL,NULL);};

port: NUM {$$=ParsePort($1);};
