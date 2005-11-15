/* A Bison parser, made by GNU Bison 2.0.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     GROUP = 258,
     SERVICE = 259,
     QUERY = 260,
     INPUT = 261,
     FORWARD = 262,
     OUTPUT = 263,
     PACKET = 264,
     SPORT = 265,
     DPORT = 266,
     SADDY = 267,
     DADDY = 268,
     STATE = 269,
     UDP = 270,
     TCP = 271,
     ICMP = 272,
     BOTH = 273,
     NUM = 274,
     DOT = 275,
     LOGGED = 276,
     T_INVALID = 277,
     T_NEW = 278,
     T_ESTABLISHED = 279,
     T_RELATED = 280,
     FIN = 281,
     SYN = 282,
     RST = 283,
     PSH = 284,
     ACK = 285,
     URG = 286,
     NAME = 287,
     LPAREN = 288,
     RPAREN = 289,
     SEMI = 290,
     AND = 291,
     OR = 292,
     NOT = 293,
     WITH = 294,
     IN = 295,
     ON = 296,
     FOR = 297,
     TO = 298,
     FROM = 299
   };
#endif
#define GROUP 258
#define SERVICE 259
#define QUERY 260
#define INPUT 261
#define FORWARD 262
#define OUTPUT 263
#define PACKET 264
#define SPORT 265
#define DPORT 266
#define SADDY 267
#define DADDY 268
#define STATE 269
#define UDP 270
#define TCP 271
#define ICMP 272
#define BOTH 273
#define NUM 274
#define DOT 275
#define LOGGED 276
#define T_INVALID 277
#define T_NEW 278
#define T_ESTABLISHED 279
#define T_RELATED 280
#define FIN 281
#define SYN 282
#define RST 283
#define PSH 284
#define ACK 285
#define URG 286
#define NAME 287
#define LPAREN 288
#define RPAREN 289
#define SEMI 290
#define AND 291
#define OR 292
#define NOT 293
#define WITH 294
#define IN 295
#define ON 296
#define FOR 297
#define TO 298
#define FROM 299




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 7 "fwlang.y"
typedef union YYSTYPE {
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
} YYSTYPE;
/* Line 1318 of yacc.c.  */
#line 142 "fwlang.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



