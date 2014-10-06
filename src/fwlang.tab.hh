/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_FWLANG_TAB_HH_INCLUDED
# define YY_YY_FWLANG_TAB_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOKEN_EOF = 0,
    GROUP = 258,
    SERVICE = 260,
    QUERY = 262,
    ASSERT = 264,
    INPUT = 266,
    FORWARD = 267,
    OUTPUT = 268,
    EXAMPLE = 269,
    HISTORY = 270,
    PACKET = 271,
    SPORT = 272,
    DPORT = 273,
    SADDY = 274,
    DADDY = 275,
    STATE = 276,
    CLASSES = 277,
    SCLASSES = 278,
    SGRAPH = 279,
    UDP = 280,
    TCP = 281,
    ICMP = 282,
    BOTH = 283,
    NUM = 284,
    DOT = 285,
    IS = 286,
    ISNT = 287,
    SUBSET_OF = 288,
    NOT_SUBSET_OF = 289,
    LOGGED = 290,
    T_INVALID = 291,
    T_NEW = 292,
    T_ESTABLISHED = 293,
    T_RELATED = 294,
    FIN = 295,
    SYN = 296,
    RST = 297,
    PSH = 298,
    ACK = 299,
    URG = 300,
    NAME = 302,
    LPAREN = 321,
    RPAREN = 322,
    SEMI = 323,
    AND = 324,
    OR = 326,
    NOT = 328,
    FROM = 330,
    TO = 331,
    FOR = 332,
    ON = 333,
    IN = 334,
    WITH = 335,
    INFACE = 336,
    OUTFACE = 337,
    ACCEPTED = 338,
    DROPPED = 339
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 17 "fwlang.yy" /* yacc.c:1909  */

   int input_chain;
   char dummy;
   group* group_rec;
   service* service_rec;
   query* query_rec;
   assert* assert_rec;
   condition* condition_rec;
   int sub;
   int sv;
   int fv;
   int assert_op;
   port* port_rec;
   char name[256];
   address* address_rec;
   int prot;
   char val[256];
   int flag;

#line 134 "fwlang.tab.hh" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void);

#endif /* !YY_YY_FWLANG_TAB_HH_INCLUDED  */
