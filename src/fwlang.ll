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
#include "src/parser.h"
#include "src/fwlang.tab.hh"
#include "src/parser_interface.hh"
int FWLANG_LINE_NO = 0;
%}
%option noyywrap nounput batch debug

NUM [0-9]*|"*"
ALPHANUM [a-zA-Z][_a-zA-Z0-9\+\*]*
COMMENT "#".*

%{
# define YY_USER_ACTION yylloc->columns (yyleng);
%}
%%
{COMMENT} { ECHO; } //Comments
"GROUP" { ECHO; return GROUP; }
"SERVICE" { ECHO; return SERVICE; }
"QUERY" { ECHO; return QUERY;}
"LOGGED" { ECHO; return LOGGED;}
"PACKET" { ECHO; return PACKET; }
"SPORT" { ECHO; return SPORT; }
"CLASSES" { ECHO; return CLASSES; }
"DPORT" { ECHO; return DPORT; }
"SADDY" { ECHO; return SADDY; }
"DADDY" { ECHO; return DADDY; }
"STATE" { ECHO; return STATE; }
"TCP" { ECHO; return TCP; }
"UDP" { ECHO; return UDP; }
"BOTH" { ECHO; return BOTH; }
"ICMP" { ECHO; return ICMP; }
"INVALID" { ECHO; return T_INVALID;}
"NEW" { ECHO; return T_NEW;}
"ESTABLISHED" { ECHO; return T_ESTABLISHED;}
"RELATED" { ECHO; return T_RELATED;}
"FIN" { ECHO; return FIN;}
"SYN" { ECHO; return SYN;}
"RST" { ECHO; return RST;}
"PSH" { ECHO; return PSH;}
"ACK" { ECHO; return ACK;}
"URG" { ECHO; return URG;}
"FROM" { ECHO; return FROM;}
"TO" { ECHO; return TO;}
"FOR" {ECHO; return FOR;}
"ON" {ECHO; return ON;}
"IN" {ECHO; return IN;}
"OR" {ECHO; return OR;}
"AND" {ECHO; return AND;}
"NOT" {ECHO; return NOT;}
"WITH" {ECHO; return WITH;}
"INFACE" {ECHO; return INFACE;}
"OUTFACE" {ECHO; return OUTFACE;}
"INPUT" {ECHO; return INPUT;}
"FORWARD" {ECHO; return FORWARD;}
"OUTPUT" {ECHO; return OUTPUT;}
"\." {ECHO; return DOT;}
{NUM} { ECHO; yylval->val = new char[256]; strncpy(yylval->name, yytext, 256); return NUM;}
{ALPHANUM} { ECHO; yylval->name = new char[256]; strncpy(yylval->name,yytext,256); return NAME;}
" " {ECHO;}
"\n" {ECHO; FWLANG_LINE_NO++;}
";" { printf(";\n"); return SEMI;}
"(" { ECHO; return LPAREN;}
")" { ECHO; return RPAREN;}
. {printf("Illegal Token: (%s)\n", yytext);}
%%
void
parser_interface::scan_begin ()
{
   yy_flex_debug = trace_scanning;
   if (!(yyin = fopen (file.c_str (), "r")))
   error (std::string ("cannot open ") + file);
}

void
parser_interface::scan_end ()
{
   fclose (yyin);
}
