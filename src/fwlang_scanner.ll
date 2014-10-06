/*
ITVal: The IPTables Firewall Validator
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
%{
#include "src/structures.h"
#include "src/parser.h"
#include "src/fwlang.tab.hh"

int FWLANG_LINE_NO = 0;
%}

%option noyywrap nounput batch 

NUM [0-9]*|"*"|"["[0-9]*"-"[0-9]*"]"
ALPHANUM [a-zA-Z][_a-zA-Z0-9\+\*]*
COMMENT "#".*

%{
//# define YY_USER_ACTION yylloc->columns (yyleng);
%}
%%
{COMMENT} { ECHO; }
"GROUP" { ECHO; return GROUP; }
"group" { ECHO; return GROUP; }
"SERVICE" { ECHO; return SERVICE; }
"service" { ECHO; return SERVICE; }
"QUERY" { ECHO; return QUERY; }
"query" { ECHO; return QUERY; }
"ASSERT" { ECHO; return ASSERT; }
"assert" { ECHO; return ASSERT; }
"ACCEPTED" { ECHO; return ACCEPTED; }
"accepted" { ECHO; return ACCEPTED; }
"DROPPED" { ECHO; return DROPPED; }
"dropped" { ECHO; return DROPPED; }
"logged" { ECHO; return LOGGED; }
"PACKET" { ECHO; return PACKET; }
"packet" { ECHO; return PACKET; }
"SPORT" { ECHO; return SPORT; }
"sport" { ECHO; return SPORT; }
"classes" { ECHO; return CLASSES; }
"CLASSES" { ECHO; return CLASSES; }
"SCLASSES" { ECHO; return SCLASSES; }
"sclasses" { ECHO; return SCLASSES; }
"SGRAPH" { ECHO; return SGRAPH; }
"sgraph" { ECHO; return SGRAPH; }
"DPORT" { ECHO; return DPORT; }
"dport" { ECHO; return DPORT; }
"SADDY" { ECHO; return SADDY; }
"saddy" { ECHO; return SADDY; }
"DADDY" { ECHO; return DADDY; }
"daddy" { ECHO; return DADDY; }
"STATE" { ECHO; return STATE; }
"state" { ECHO; return STATE; }
"TCP" { ECHO; return TCP; }
"tcp" { ECHO; return TCP; }
"UDP" { ECHO; return UDP; }
"udp" { ECHO; return UDP; }
"BOTH" { ECHO; return BOTH; }
"both" { ECHO; return BOTH; }
"ICMP" { ECHO; return ICMP; }
"icmp" { ECHO; return ICMP; }
"INVALID" { ECHO; return T_INVALID;}
"invalid" { ECHO; return T_INVALID;}
"NEW" { ECHO; return T_NEW;}
"new" { ECHO; return T_NEW;}
"ESTABLISHED" { ECHO; return T_ESTABLISHED;}
"established" { ECHO; return T_ESTABLISHED;}
"RELATED" { ECHO; return T_RELATED;}
"related" { ECHO; return T_RELATED;}
"FIN" { ECHO; return FIN;}
"fin" { ECHO; return FIN;}
"SYN" { ECHO; return SYN;}
"syn" { ECHO; return SYN;}
"RST" { ECHO; return RST;}
"rst" { ECHO; return RST;}
"PSH" { ECHO; return PSH;}
"psh" { ECHO; return PSH;}
"ACK" { ECHO; return ACK;}
"ack" { ECHO; return ACK;}
"URG" { ECHO; return URG;}
"urg" { ECHO; return URG;}
"FROM" { ECHO; return FROM;}
"from" { ECHO; return FROM;}
"TO" { ECHO; return TO;}
"to" { ECHO; return TO;}
"FOR" {ECHO; return FOR;}
"for" {ECHO; return FOR;}
"ON" {ECHO; return ON;}
"on" {ECHO; return ON;}
"IN" {ECHO; return IN;}
"in" {ECHO; return IN;}
"OR" {ECHO; return OR;}
"or" {ECHO; return OR;}
"AND" {ECHO; return AND;}
"and" {ECHO; return AND;}
"NOT SUBSET OF" {ECHO; return NOT_SUBSET_OF;}
"not SUBSET OF" {ECHO; return NOT_SUBSET_OF;}
"NOT subset OF" {ECHO; return NOT_SUBSET_OF;}
"not subset OF" {ECHO; return NOT_SUBSET_OF;}
"NOT SUBSET of" {ECHO; return NOT_SUBSET_OF;}
"not SUBSET of" {ECHO; return NOT_SUBSET_OF;}
"NOT subset Of" {ECHO; return NOT_SUBSET_OF;}
"not subset Of" {ECHO; return NOT_SUBSET_OF;}
"NOT" {ECHO; return NOT;}
"not" {ECHO; return NOT;}
"WITH" {ECHO; return WITH;}
"with" {ECHO; return WITH;}
"INFACE" {ECHO; return INFACE;}
"inface" {ECHO; return INFACE;}
"OUTFACE" {ECHO; return OUTFACE;}
"outface" {ECHO; return OUTFACE;}
"INPUT" {ECHO; return INPUT;}
"input" {ECHO; return INPUT;}
"FORWARD" {ECHO; return FORWARD;}
"forward" {ECHO; return FORWARD;}
"OUTPUT" {ECHO; return OUTPUT;}
"output" {ECHO; return OUTPUT;}
"ISN'T" {ECHO; return ISNT;}
"isn't" {ECHO; return ISNT;}
"IS" {ECHO; return IS;}
"is" {ECHO; return IS;}
"SUBSET OF" {ECHO; return SUBSET_OF;}
"subset OF" {ECHO; return SUBSET_OF;}
"SUBSET of" {ECHO; return SUBSET_OF;}
"subset of" {ECHO; return SUBSET_OF;}
"EXAMPLE" {ECHO; return EXAMPLE;}
"example" {ECHO; return EXAMPLE;}
"HISTORY" {ECHO; return HISTORY;}
"history" {ECHO; return HISTORY;}
"\." {ECHO; return DOT;}
{NUM} { ECHO; strncpy(yylval->val, yytext, 256); return NUM;}
{ALPHANUM} { ECHO; strncpy(yylval->name,yytext,256); return NAME;} 
"\t" {ECHO;}
" " {ECHO;}
"\n" {ECHO; FWLANG_LINE_NO++;}
";" { printf(";\n"); return SEMI;}
"(" { ECHO; return LPAREN;}
")" { ECHO; return RPAREN;}
. {printf("Illegal Token: (%s)\n", yytext);exit(1);}
