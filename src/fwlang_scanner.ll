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
YY_DECL;

int FWLANG_LINE_NO = 0;
%}
%option noyywrap nounput batch debug

NUM [0-9]*|"*"|"["[0-9]*"-"[0-9]*"]"
ALPHANUM [a-zA-Z][_a-zA-Z0-9\+\*]*
COMMENT "#".*


%{
# define YY_USER_ACTION yylloc->columns (yyleng);
%}
%%
{COMMENT} { ECHO; } //Comments
"GROUP" { ECHO; return yy::parser::token::GROUP; }
"SERVICE" { ECHO; return yy::parser::token::SERVICE; }
"QUERY" { ECHO; return yy::parser::token::QUERY; }
"ASSERT" { ECHO; return yy::parser::token::ASSERT; }
"ACCEPTED" { ECHO; return yy::parser::token::ACCEPTED; }
"DROPPED" { ECHO; return yy::parser::token::DROPPED; }
"LOGGED" { ECHO; return yy::parser::token::LOGGED; }
"PACKET" { ECHO; return yy::parser::token::PACKET; }
"SPORT" { ECHO; return yy::parser::token::SPORT; }
"CLASSES" { ECHO; return yy::parser::token::CLASSES; }
"SCLASSES" { ECHO; return yy::parser::token::SCLASSES; }
"SGRAPH" { ECHO; return yy::parser::token::SGRAPH; }
"DPORT" { ECHO; return yy::parser::token::DPORT; }
"SADDY" { ECHO; return yy::parser::token::SADDY; }
"DADDY" { ECHO; return yy::parser::token::DADDY; }
"STATE" { ECHO; return yy::parser::token::STATE; }
"TCP" { ECHO; return yy::parser::token::TCP; }
"UDP" { ECHO; return yy::parser::token::UDP; }
"BOTH" { ECHO; return yy::parser::token::BOTH; }
"ICMP" { ECHO; return yy::parser::token::ICMP; }
"INVALID" { ECHO; return yy::parser::token::T_INVALID;}
"NEW" { ECHO; return yy::parser::token::T_NEW;}
"ESTABLISHED" { ECHO; return yy::parser::token::T_ESTABLISHED;}
"RELATED" { ECHO; return yy::parser::token::T_RELATED;}
"FIN" { ECHO; return yy::parser::token::FIN;}
"SYN" { ECHO; return yy::parser::token::SYN;}
"RST" { ECHO; return yy::parser::token::RST;}
"PSH" { ECHO; return yy::parser::token::PSH;}
"ACK" { ECHO; return yy::parser::token::ACK;}
"URG" { ECHO; return yy::parser::token::URG;}
"FROM" { ECHO; return yy::parser::token::FROM;}
"TO" { ECHO; return yy::parser::token::TO;}
"FOR" {ECHO; return yy::parser::token::FOR;}
"ON" {ECHO; return yy::parser::token::ON;}
"IN" {ECHO; return yy::parser::token::IN;}
"OR" {ECHO; return yy::parser::token::OR;}
"AND" {ECHO; return yy::parser::token::AND;}
"NOT SUBSET OF" {ECHO; return yy::parser::token::NOT_SUBSET_OF;}
"NOT" {ECHO; return yy::parser::token::NOT;}
"WITH" {ECHO; return yy::parser::token::WITH;}
"INFACE" {ECHO; return yy::parser::token::INFACE;}
"OUTFACE" {ECHO; return yy::parser::token::OUTFACE;}
"INPUT" {ECHO; return yy::parser::token::INPUT;}
"FORWARD" {ECHO; return yy::parser::token::FORWARD;}
"OUTPUT" {ECHO; return yy::parser::token::OUTPUT;}
"ISN'T" {ECHO; return yy::parser::token::ISNT;}
"IS" {ECHO; return yy::parser::token::IS;}
"SUBSET OF" {ECHO; return yy::parser::token::SUBSET_OF;}
"EXAMPLE" {ECHO; return yy::parser::token::EXAMPLE;}
"HISTORY" {ECHO; return yy::parser::token::HISTORY;}
"\." {ECHO; return yy::parser::token::DOT;}
{NUM} { ECHO; yylval->val = new char[256]; strncpy(yylval->val, yytext, 256); return yy::parser::token::NUM;}
{ALPHANUM} { ECHO; yylval->name = new char[256]; strncpy(yylval->name,yytext,256); return yy::parser::token::NAME;} 
"\t" {ECHO;}
" " {ECHO;}
"\n" {ECHO; FWLANG_LINE_NO++;}
";" { printf(";\n"); return yy::parser::token::SEMI;}
"(" { ECHO; return yy::parser::token::LPAREN;}
")" { ECHO; return yy::parser::token::RPAREN;}
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
