/* A Bison parser, made by GNU Bison 1.875.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

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

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOKEN_EOF = 0,
     GROUP = 259,
     SERVICE = 261,
     QUERY = 263,
     ASSERT = 265,
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
     AND = 325,
     OR = 327,
     NOT = 329,
     DROPPED = 331,
     ACCEPTED = 332,
     OUTFACE = 333,
     INFACE = 334,
     WITH = 335,
     IN = 336,
     ON = 337,
     FOR = 338,
     TO = 339,
     FROM = 340
   };
#endif
#define TOKEN_EOF 0
#define GROUP 259
#define SERVICE 261
#define QUERY 263
#define ASSERT 265
#define INPUT 266
#define FORWARD 267
#define OUTPUT 268
#define EXAMPLE 269
#define HISTORY 270
#define PACKET 271
#define SPORT 272
#define DPORT 273
#define SADDY 274
#define DADDY 275
#define STATE 276
#define CLASSES 277
#define SCLASSES 278
#define SGRAPH 279
#define UDP 280
#define TCP 281
#define ICMP 282
#define BOTH 283
#define NUM 284
#define DOT 285
#define IS 286
#define ISNT 287
#define SUBSET_OF 288
#define NOT_SUBSET_OF 289
#define LOGGED 290
#define T_INVALID 291
#define T_NEW 292
#define T_ESTABLISHED 293
#define T_RELATED 294
#define FIN 295
#define SYN 296
#define RST 297
#define PSH 298
#define ACK 299
#define URG 300
#define NAME 302
#define LPAREN 321
#define RPAREN 322
#define SEMI 323
#define AND 325
#define OR 327
#define NOT 329
#define DROPPED 331
#define ACCEPTED 332
#define OUTFACE 333
#define INFACE 334
#define WITH 335
#define IN 336
#define ON 337
#define FOR 338
#define TO 339
#define FROM 340




/* Copy the first part of user declarations.  */
#line 3 "fwlang.yy"

#include <string>
#include "src/parser.h"
#include "src/structures.h"
int yyerror(char* str);


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 13 "fwlang.yy"
typedef union YYSTYPE {
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
   char *name;
   address* address_rec;
   int prot;
   char* val;
   int flag;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 220 "fwlang.cc"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */
#line 33 "fwlang.yy"


YY_DECL;



/* Line 214 of yacc.c.  */
#line 237 "fwlang.cc"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  41
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   132

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  22
/* YYNRULES -- Number of rules. */
#define YYNRULES  77
/* YYNRULES -- Number of states. */
#define YYNSTATES  119

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   340

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    14,    17,    20,    22,
      26,    30,    33,    35,    38,    40,    43,    46,    49,    53,
      58,    64,    70,    77,    79,    81,    83,    85,    87,    89,
      91,    93,    95,    97,    99,   101,   103,   105,   109,   113,
     116,   120,   123,   126,   129,   132,   135,   138,   141,   144,
     147,   150,   153,   155,   157,   159,   161,   163,   165,   167,
     169,   171,   173,   175,   177,   179,   181,   183,   185,   188,
     190,   192,   194,   196,   204,   210,   214,   216
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      87,     0,    -1,    88,    -1,    88,    87,    -1,    89,    68,
      -1,    90,    68,    -1,    93,    68,    -1,    94,    68,    -1,
      68,    -1,     4,    47,    91,    -1,     6,    47,    92,    -1,
      91,   106,    -1,   106,    -1,    92,   104,    -1,   104,    -1,
       8,    22,    -1,     8,    23,    -1,     8,    24,    -1,     8,
      97,    98,    -1,    10,    98,    95,    98,    -1,    10,    14,
      98,    95,    98,    -1,    10,    15,    98,    95,    98,    -1,
      10,    14,    15,    98,    95,    98,    -1,    31,    -1,    33,
      -1,    32,    -1,    34,    -1,    11,    -1,    12,    -1,    13,
      -1,    16,    -1,    17,    -1,    18,    -1,    19,    -1,    20,
      -1,    21,    -1,    99,    -1,    98,    70,    98,    -1,    98,
      72,    98,    -1,    74,    98,    -1,    66,    98,    67,    -1,
      35,    96,    -1,    85,   100,    -1,    84,   100,    -1,    82,
     101,    -1,    83,   101,    -1,    81,   102,    -1,    80,   103,
      -1,    79,    47,    -1,    78,    47,    -1,    77,    96,    -1,
      76,    96,    -1,    77,    -1,    76,    -1,    47,    -1,   106,
      -1,    47,    -1,   104,    -1,    36,    -1,    37,    -1,    38,
      -1,    39,    -1,    40,    -1,    41,    -1,    42,    -1,    43,
      -1,    44,    -1,    45,    -1,   105,   107,    -1,    27,    -1,
      25,    -1,    26,    -1,    28,    -1,    29,    30,    29,    30,
      29,    30,    29,    -1,    29,    30,    29,    30,    29,    -1,
      29,    30,    29,    -1,    29,    -1,    29,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned char yyrline[] =
{
       0,    88,    88,    88,    89,    90,    91,    92,    93,    96,
      98,   100,   101,   103,   104,   106,   107,   108,   109,   115,
     116,   117,   118,   121,   122,   123,   124,   127,   128,   129,
     132,   133,   134,   135,   136,   137,   141,   142,   143,   144,
     145,   146,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   163,   164,   166,   167,   169,   169,
     169,   169,   171,   171,   171,   171,   171,   171,   173,   175,
     175,   175,   175,   177,   178,   179,   180,   182
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "$undefined", "\"group\"", "GROUP", 
  "\"service\"", "SERVICE", "\"query\"", "QUERY", "\"assert\"", "ASSERT", 
  "INPUT", "FORWARD", "\"selected chain\"", "EXAMPLE", 
  "\"ASSERTION flag\"", "PACKET", "SPORT", "DPORT", "SADDY", "DADDY", 
  "\"query subject\"", "\"equivalence host classes\"", 
  "\"equivalence service classes\"", "\"equivalence class graph\"", "UDP", 
  "TCP", "ICMP", "\"protocol\"", "\"number\"", "\".\"", "IS", "ISNT", 
  "SUBSET_OF", "\"assertion operators\"", "\"logged condition\"", 
  "T_INVALID", "T_NEW", "T_ESTABLISHED", "\"connection state\"", "FIN", 
  "SYN", "RST", "PSH", "ACK", "\"tcp flag\"", "\"address\"", "\"name\"", 
  "\"port number\"", "\"compound port\"", "\"complete port\"", 
  "\"compound address\"", "\"simple condition\"", "\"state value\"", 
  "\"flag name\"", "\"query condition\"", "\"subject keyword\"", 
  "\"input chain\"", "\"protocol keyword\"", "\"assert expression\"", 
  "\"query expression\"", "\"service declaration\"", 
  "\"address group declaration\"", "\"address list\"", "\"port list\"", 
  "\"assertion operator\"", "LPAREN", "RPAREN", "SEMI", "\"AND\"", "AND", 
  "\"OR\"", "OR", "\"NOT\"", "NOT", "\"query primitive\"", "DROPPED", 
  "ACCEPTED", "OUTFACE", "INFACE", "WITH", "IN", "ON", "FOR", "TO", 
  "FROM", "$accept", "statement", "expression", "group_expression", 
  "service_expression", "addy_list", "port_list", "query_expression", 
  "assert_expression", "assert_op", "input_chain", "subject", "condition", 
  "simple_condition", "compound_addy", "compound_port", "state_value", 
  "flag_name", "complete_port", "protocol", "addr", "port", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    86,    87,    87,    88,    88,    88,    88,    88,    89,
      90,    91,    91,    92,    92,    93,    93,    93,    93,    94,
      94,    94,    94,    95,    95,    95,    95,    96,    96,    96,
      97,    97,    97,    97,    97,    97,    98,    98,    98,    98,
      98,    98,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,   100,   100,   101,   101,   102,   102,
     102,   102,   103,   103,   103,   103,   103,   103,   104,   105,
     105,   105,   105,   106,   106,   106,   106,   107
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     2,     2,     2,     2,     2,     1,     3,
       3,     2,     1,     2,     1,     2,     2,     2,     3,     4,
       5,     5,     6,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     2,
       3,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     7,     5,     3,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,     0,     8,     0,     2,     0,     0,
       0,     0,     0,     0,    30,    31,    32,    33,    34,    35,
      15,    16,    17,     0,     0,     0,     0,     0,     0,    53,
      52,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      36,     1,     3,     4,     5,     6,     7,    76,     9,    12,
      70,    71,    69,    72,    10,    14,     0,    18,     0,     0,
       0,    27,    28,    29,    41,     0,    39,    51,    50,    49,
      48,    62,    63,    64,    65,    66,    67,    47,    58,    59,
      60,    61,    46,    56,    44,    57,    45,    54,    43,    55,
      42,    23,    25,    24,    26,     0,     0,     0,     0,    11,
      13,    77,    68,     0,     0,     0,    40,    37,    38,    19,
      75,     0,    20,    21,     0,    22,    74,     0,    73
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     6,     7,     8,     9,    48,    54,    10,    11,    97,
      64,    23,    39,    40,    88,    84,    82,    77,    85,    56,
      89,   102
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -51
static const yysigned_char yypact[] =
{
       2,   -38,   -26,   104,    13,   -51,    29,     2,   -28,   -27,
     -22,   -21,    22,    58,   -51,   -51,   -51,   -51,   -51,   -51,
     -51,   -51,   -51,   -24,    34,   -24,     3,   -24,   -24,     3,
       3,    24,    31,    23,    65,    -2,    -2,   -16,   -16,     5,
     -51,   -51,   -51,   -51,   -51,   -51,   -51,    46,    22,   -51,
     -51,   -51,   -51,   -51,    58,   -51,    51,   -40,   -24,     5,
       5,   -51,   -51,   -51,   -51,   -50,   -51,   -51,   -51,   -51,
     -51,   -51,   -51,   -51,   -51,   -51,   -51,   -51,   -51,   -51,
     -51,   -51,   -51,   -51,   -51,   -51,   -51,   -51,   -51,   -51,
     -51,   -51,   -51,   -51,   -51,   -24,   -24,   -24,    70,   -51,
     -51,   -51,   -51,     5,   -24,   -24,   -51,    33,   -51,   -40,
      76,   -24,   -40,   -40,    78,   -40,    79,   100,   -51
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
     -51,   123,   -51,   -51,   -51,   -51,   -51,   -51,   -51,   -41,
       4,   -51,   -23,   -51,    93,    96,   -51,   -51,   -10,   -51,
      -5,   -51
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
      57,    59,    60,    55,    65,    66,     1,    49,     2,    12,
       3,    26,     4,    47,    61,    62,    63,   106,   104,   105,
      95,    13,    96,    50,    51,    52,    53,    24,    25,    41,
      95,    87,    96,    67,    68,   103,    91,    92,    93,    94,
      43,    44,    27,    99,   100,    83,    45,    46,    26,    58,
      28,    47,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,   111,    71,    72,    73,    74,    75,    76,    26,
       5,    69,   107,   108,   109,    95,    98,    96,    70,    27,
     101,   112,   113,    50,    51,    52,    53,    28,   115,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,   110,
      27,    78,    79,    80,    81,    96,   114,   116,    28,   117,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      14,    15,    16,    17,    18,    19,    20,    21,    22,   118,
      42,    90,    86
};

static const unsigned char yycheck[] =
{
      23,    24,    25,    13,    27,    28,     4,    12,     6,    47,
       8,    35,    10,    29,    11,    12,    13,    67,    59,    60,
      70,    47,    72,    25,    26,    27,    28,    14,    15,     0,
      70,    47,    72,    29,    30,    58,    31,    32,    33,    34,
      68,    68,    66,    48,    54,    47,    68,    68,    35,    15,
      74,    29,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,   103,    40,    41,    42,    43,    44,    45,    35,
      68,    47,    95,    96,    97,    70,    30,    72,    47,    66,
      29,   104,   105,    25,    26,    27,    28,    74,   111,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    29,
      66,    36,    37,    38,    39,    72,    30,    29,    74,    30,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    29,
       7,    38,    36
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     4,     6,     8,    10,    68,    87,    88,    89,    90,
      93,    94,    47,    47,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    97,    14,    15,    35,    66,    74,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    98,
      99,     0,    87,    68,    68,    68,    68,    29,    91,   106,
      25,    26,    27,    28,    92,   104,   105,    98,    15,    98,
      98,    11,    12,    13,    96,    98,    98,    96,    96,    47,
      47,    40,    41,    42,    43,    44,    45,   103,    36,    37,
      38,    39,   102,    47,   101,   104,   101,    47,   100,   106,
     100,    31,    32,    33,    34,    70,    72,    95,    30,   106,
     104,    29,   107,    98,    95,    95,    67,    98,    98,    98,
      29,    95,    98,    98,    30,    98,    29,    30,    29
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1

/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylineno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylineno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  /* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 9:
#line 96 "fwlang.yy"
    {yyval.group_rec = DefineGroup(yyvsp[-1].name, yyvsp[0].address_rec); delete[] yyvsp[-1].name;}
    break;

  case 10:
#line 98 "fwlang.yy"
    {yyval.service_rec = DefineService(yyvsp[-1].name, yyvsp[0].port_rec); delete[] yyvsp[-1].name;}
    break;

  case 11:
#line 100 "fwlang.yy"
    {yyval.address_rec = AppendAddy(yyvsp[-1].address_rec,yyvsp[0].address_rec);}
    break;

  case 12:
#line 101 "fwlang.yy"
    {yyval.address_rec = AppendAddy(NULL, yyvsp[0].address_rec);}
    break;

  case 13:
#line 103 "fwlang.yy"
    {yyval.port_rec = AppendPort(yyvsp[-1].port_rec, yyvsp[0].port_rec);}
    break;

  case 14:
#line 104 "fwlang.yy"
    {yyval.port_rec = AppendPort(NULL, yyvsp[0].port_rec);}
    break;

  case 15:
#line 106 "fwlang.yy"
    {yyval.query_rec = PrintClasses();}
    break;

  case 16:
#line 107 "fwlang.yy"
    {yyval.query_rec = PrintServiceClasses();}
    break;

  case 17:
#line 108 "fwlang.yy"
    {yyval.query_rec = PrintServiceGraph();}
    break;

  case 18:
#line 109 "fwlang.yy"
    {yyval.query_rec = PerformQuery(yyvsp[-1].sub, yyvsp[0].condition_rec);}
    break;

  case 19:
#line 115 "fwlang.yy"
    {yyval.assert_rec = PerformAssertion(yyvsp[-2].condition_rec, yyvsp[0].condition_rec, yyvsp[-1].assert_op, 0, 0);}
    break;

  case 20:
#line 116 "fwlang.yy"
    {yyval.assert_rec = PerformAssertion(yyvsp[-2].condition_rec, yyvsp[0].condition_rec, yyvsp[-1].assert_op, 1, 0);}
    break;

  case 21:
#line 117 "fwlang.yy"
    {yyval.assert_rec = PerformAssertion(yyvsp[-2].condition_rec, yyvsp[0].condition_rec, yyvsp[-1].assert_op, 0, 1);}
    break;

  case 22:
#line 118 "fwlang.yy"
    {yyval.assert_rec = PerformAssertion(yyvsp[-2].condition_rec, yyvsp[0].condition_rec, yyvsp[-1].assert_op, 1,1);}
    break;

  case 23:
#line 121 "fwlang.yy"
    {yyval.assert_op = OP_IS;}
    break;

  case 24:
#line 122 "fwlang.yy"
    {yyval.assert_op= OP_SUBSET;}
    break;

  case 25:
#line 123 "fwlang.yy"
    {yyval.assert_op = OP_NOT_IS;}
    break;

  case 26:
#line 124 "fwlang.yy"
    {yyval.assert_op = OP_NOT_SUBSET;}
    break;

  case 27:
#line 127 "fwlang.yy"
    {yyval.input_chain = 0;}
    break;

  case 28:
#line 128 "fwlang.yy"
    {yyval.input_chain = 1;}
    break;

  case 29:
#line 129 "fwlang.yy"
    {yyval.input_chain = 2;}
    break;

  case 30:
#line 132 "fwlang.yy"
    {yyval.sub=0;}
    break;

  case 31:
#line 133 "fwlang.yy"
    {yyval.sub=1;}
    break;

  case 32:
#line 134 "fwlang.yy"
    {yyval.sub=2;}
    break;

  case 33:
#line 135 "fwlang.yy"
    {yyval.sub=3;}
    break;

  case 34:
#line 136 "fwlang.yy"
    {yyval.sub=4;}
    break;

  case 35:
#line 137 "fwlang.yy"
    {yyval.sub=5;}
    break;

  case 36:
#line 141 "fwlang.yy"
    {yyval.condition_rec = yyvsp[0].condition_rec;}
    break;

  case 37:
#line 142 "fwlang.yy"
    {yyval.condition_rec = IntersectConditions(yyvsp[-2].condition_rec,yyvsp[0].condition_rec);}
    break;

  case 38:
#line 143 "fwlang.yy"
    {yyval.condition_rec = UnionConditions(yyvsp[-2].condition_rec,yyvsp[0].condition_rec);}
    break;

  case 39:
#line 144 "fwlang.yy"
    {yyval.condition_rec = NegateCondition(yyvsp[0].condition_rec);}
    break;

  case 40:
#line 145 "fwlang.yy"
    {yyval.condition_rec = yyvsp[-1].condition_rec;}
    break;

  case 41:
#line 146 "fwlang.yy"
    { yyval.condition_rec = GetLoggedCondition(yyvsp[0].input_chain);}
    break;

  case 42:
#line 149 "fwlang.yy"
    {yyval.condition_rec=BuildConditionFromGroup(yyvsp[0].group_rec, 0);}
    break;

  case 43:
#line 150 "fwlang.yy"
    {yyval.condition_rec=BuildConditionFromGroup(yyvsp[0].group_rec,1);}
    break;

  case 44:
#line 151 "fwlang.yy"
    {yyval.condition_rec=BuildConditionFromService(yyvsp[0].service_rec, 0);}
    break;

  case 45:
#line 152 "fwlang.yy"
    {yyval.condition_rec=BuildConditionFromService(yyvsp[0].service_rec, 1);}
    break;

  case 46:
#line 153 "fwlang.yy"
    {yyval.condition_rec=BuildConditionFromState(yyvsp[0].sv);}
    break;

  case 47:
#line 154 "fwlang.yy"
    {yyval.condition_rec=BuildConditionFromFlag(yyvsp[0].fv);}
    break;

  case 48:
#line 155 "fwlang.yy"
    {yyval.condition_rec=BuildConditionFromIface(yyvsp[0].name, 0); delete[] yyvsp[0].name;}
    break;

  case 49:
#line 156 "fwlang.yy"
    {yyval.condition_rec=BuildConditionFromIface(yyvsp[0].name, 1); delete[] yyvsp[0].name;}
    break;

  case 50:
#line 157 "fwlang.yy"
    {yyval.condition_rec=BuildAcceptCondition(yyvsp[0].input_chain);}
    break;

  case 51:
#line 158 "fwlang.yy"
    {yyval.condition_rec=BuildDropCondition(yyvsp[0].input_chain);}
    break;

  case 52:
#line 159 "fwlang.yy"
    {yyval.condition_rec=BuildAcceptCondition(1);}
    break;

  case 53:
#line 160 "fwlang.yy"
    {yyval.condition_rec=BuildDropCondition(1);}
    break;

  case 54:
#line 163 "fwlang.yy"
    {yyval.group_rec = GroupLookup(yyvsp[0].name); delete[] yyvsp[0].name;}
    break;

  case 55:
#line 164 "fwlang.yy"
    {yyval.group_rec = BuildGroupFromAddress(yyvsp[0].address_rec);}
    break;

  case 56:
#line 166 "fwlang.yy"
    {yyval.service_rec = ServiceLookup(yyvsp[0].name); delete[] yyvsp[0].name;}
    break;

  case 57:
#line 167 "fwlang.yy"
    {yyval.service_rec = BuildServiceFromPort(yyvsp[0].port_rec);}
    break;

  case 58:
#line 169 "fwlang.yy"
    {yyval.sv=0;}
    break;

  case 59:
#line 169 "fwlang.yy"
    {yyval.sv=1;}
    break;

  case 60:
#line 169 "fwlang.yy"
    {yyval.sv=2;}
    break;

  case 61:
#line 169 "fwlang.yy"
    {yyval.sv=3;}
    break;

  case 62:
#line 171 "fwlang.yy"
    {yyval.fv=0;}
    break;

  case 63:
#line 171 "fwlang.yy"
    {yyval.fv=1;}
    break;

  case 64:
#line 171 "fwlang.yy"
    {yyval.fv=2;}
    break;

  case 65:
#line 171 "fwlang.yy"
    {yyval.fv=3;}
    break;

  case 66:
#line 171 "fwlang.yy"
    {yyval.fv=4;}
    break;

  case 67:
#line 171 "fwlang.yy"
    {yyval.fv=5;}
    break;

  case 68:
#line 173 "fwlang.yy"
    {yyval.port_rec = BuildPort(yyvsp[-1].prot, yyvsp[0].port_rec);}
    break;

  case 69:
#line 175 "fwlang.yy"
    {yyval.prot = 0;}
    break;

  case 70:
#line 175 "fwlang.yy"
    {yyval.prot = 1;}
    break;

  case 71:
#line 175 "fwlang.yy"
    { yyval.prot = 2;}
    break;

  case 72:
#line 175 "fwlang.yy"
    { yyval.prot = -1;}
    break;

  case 73:
#line 177 "fwlang.yy"
    {yyval.address_rec = ParseAddr(yyvsp[-6].val,yyvsp[-4].val,yyvsp[-2].val,yyvsp[0].val); delete[] yyvsp[-6].val; delete[] yyvsp[-4].val; delete[] yyvsp[-2].val; delete[] yyvsp[0].val;}
    break;

  case 74:
#line 178 "fwlang.yy"
    {yyval.address_rec=ParseAddr(yyvsp[-4].val,yyvsp[-2].val,yyvsp[0].val,NULL); delete[] yyvsp[-4].val; delete[] yyvsp[-2].val; delete[] yyvsp[0].val;}
    break;

  case 75:
#line 179 "fwlang.yy"
    {yyval.address_rec=ParseAddr(yyvsp[-2].val,yyvsp[0].val,NULL,NULL); delete[] yyvsp[-2].val; delete[] yyvsp[0].val;}
    break;

  case 76:
#line 180 "fwlang.yy"
    {yyval.address_rec=ParseAddr(yyvsp[0].val,NULL,NULL,NULL); delete[] yyvsp[0].val;}
    break;

  case 77:
#line 182 "fwlang.yy"
    {yyval.port_rec=ParsePort(yyvsp[0].val); delete[] yyvsp[0].val;}
    break;


    }

/* Line 991 of yacc.c.  */
#line 1593 "fwlang.cc"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("syntax error, unexpected ") + 1;
	  yysize += yystrlen (yytname[yytype]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab2;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:

  /* Suppress GCC warning that yyerrlab1 is unused when no action
     invokes YYERROR.  */
#if defined (__GNUC_MINOR__) && 2093 <= (__GNUC__ * 1000 + __GNUC_MINOR__) \
    && !defined __cplusplus
  __attribute__ ((__unused__))
#endif


  goto yyerrlab2;


/*---------------------------------------------------------------.
| yyerrlab2 -- pop states until the error token can be shifted.  |
`---------------------------------------------------------------*/
yyerrlab2:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 184 "fwlang.yy"


int yyerror(char* str){
   printf("%s\n", str);
}

