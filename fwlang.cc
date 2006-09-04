/* A Bison parser, made by GNU Bison 2.2.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++

   Copyright (C) 2002, 2003, 2004, 2005, 2006 Free Software Foundation, Inc.

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
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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


#include "src/fwlang.tab.hh"

/* User implementation prologue.  */
YY_DECL;


/* Line 317 of lalr1.cc.  */
#line 43 "fwlang.cc"

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG							\
  for (bool yydebugcond_ = yydebug_; yydebugcond_; yydebugcond_ = false)	\
    (*yycdebug_)

/* Enable debugging if requested.  */
#if YYDEBUG

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab

namespace yy
{
#if YYERROR_VERBOSE

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              /* Fall through.  */
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

#endif

  /// Build a parser object.
  parser::parser (parser_interface& pi_yyarg)
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
      pi (pi_yyarg)
  {
  }

  parser::~parser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  parser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    switch (yytype)
      {
         default:
	  break;
      }
  }


  void
  parser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif /* ! YYDEBUG */

  void
  parser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
  
	default:
	  break;
      }
  }

  void
  parser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }


  int
  parser::parse ()
  {
    /// Look-ahead and look-ahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the look-ahead.
    semantic_type yylval;
    /// Location of the look-ahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location yyerror_range[2];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;
    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without look-ahead.  */
    yyn = yypact_[yystate];
    if (yyn == yypact_ninf_)
      goto yydefault;

    /* Read a look-ahead token.  */
    if (yychar == yyempty_)
      {
	YYCDEBUG << "Reading a token: ";
	yychar = yylex (&yylval, &yylloc, pi);
      }


    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yyn == 0 || yyn == yytable_ninf_)
	goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Accept?  */
    if (yyn == yyfinal_)
      goto yyacceptlab;

    /* Shift the look-ahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted unless it is eof.  */
    if (yychar != yyeof_)
      yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
	  case 9:
#line 95 "fwlang.yy"
    {(yyval.group_rec) = DefineGroup((yysemantic_stack_[(3) - (2)].name), (yysemantic_stack_[(3) - (3)].address_rec)); delete[] (yysemantic_stack_[(3) - (2)].name);}
    break;

  case 10:
#line 97 "fwlang.yy"
    {(yyval.service_rec) = DefineService((yysemantic_stack_[(3) - (2)].name), (yysemantic_stack_[(3) - (3)].port_rec)); delete[] (yysemantic_stack_[(3) - (2)].name);}
    break;

  case 11:
#line 99 "fwlang.yy"
    {(yyval.address_rec) = AppendAddy((yysemantic_stack_[(2) - (1)].address_rec),(yysemantic_stack_[(2) - (2)].address_rec));}
    break;

  case 12:
#line 100 "fwlang.yy"
    {(yyval.address_rec) = AppendAddy(NULL, (yysemantic_stack_[(1) - (1)].address_rec));}
    break;

  case 13:
#line 102 "fwlang.yy"
    {(yyval.port_rec) = AppendPort((yysemantic_stack_[(2) - (1)].port_rec), (yysemantic_stack_[(2) - (2)].port_rec));}
    break;

  case 14:
#line 103 "fwlang.yy"
    {(yyval.port_rec) = AppendPort(NULL, (yysemantic_stack_[(1) - (1)].port_rec));}
    break;

  case 15:
#line 105 "fwlang.yy"
    {(yyval.query_rec) = PrintClasses();}
    break;

  case 16:
#line 106 "fwlang.yy"
    {(yyval.query_rec) = PrintServiceClasses();}
    break;

  case 17:
#line 107 "fwlang.yy"
    {(yyval.query_rec) = PrintServiceGraph();}
    break;

  case 18:
#line 108 "fwlang.yy"
    {(yyval.query_rec) = PerformQuery((yysemantic_stack_[(3) - (2)].sub), (yysemantic_stack_[(3) - (3)].condition_rec));}
    break;

  case 19:
#line 114 "fwlang.yy"
    {(yyval.assert_rec) = PerformAssertion((yysemantic_stack_[(4) - (2)].condition_rec), (yysemantic_stack_[(4) - (4)].condition_rec), (yysemantic_stack_[(4) - (3)].assert_op));}
    break;

  case 20:
#line 118 "fwlang.yy"
    {(yyval.assert_op) = 0;}
    break;

  case 21:
#line 119 "fwlang.yy"
    {(yyval.assert_op)=1;}
    break;

  case 22:
#line 120 "fwlang.yy"
    {(yyval.assert_op) = 2;}
    break;

  case 23:
#line 121 "fwlang.yy"
    {(yyval.assert_op) = 3;}
    break;

  case 24:
#line 124 "fwlang.yy"
    {(yyval.input_chain) = 0;}
    break;

  case 25:
#line 125 "fwlang.yy"
    {(yyval.input_chain) = 1;}
    break;

  case 26:
#line 126 "fwlang.yy"
    {(yyval.input_chain) = 2;}
    break;

  case 27:
#line 129 "fwlang.yy"
    {(yyval.sub)=0;}
    break;

  case 28:
#line 130 "fwlang.yy"
    {(yyval.sub)=1;}
    break;

  case 29:
#line 131 "fwlang.yy"
    {(yyval.sub)=2;}
    break;

  case 30:
#line 132 "fwlang.yy"
    {(yyval.sub)=3;}
    break;

  case 31:
#line 133 "fwlang.yy"
    {(yyval.sub)=4;}
    break;

  case 32:
#line 134 "fwlang.yy"
    {(yyval.sub)=5;}
    break;

  case 33:
#line 138 "fwlang.yy"
    {(yyval.condition_rec) = (yysemantic_stack_[(1) - (1)].condition_rec);}
    break;

  case 34:
#line 139 "fwlang.yy"
    {(yyval.condition_rec) = IntersectConditions((yysemantic_stack_[(3) - (1)].condition_rec),(yysemantic_stack_[(3) - (3)].condition_rec));}
    break;

  case 35:
#line 140 "fwlang.yy"
    {(yyval.condition_rec) = UnionConditions((yysemantic_stack_[(3) - (1)].condition_rec),(yysemantic_stack_[(3) - (3)].condition_rec));}
    break;

  case 36:
#line 141 "fwlang.yy"
    {(yyval.condition_rec) = NegateCondition((yysemantic_stack_[(2) - (2)].condition_rec));}
    break;

  case 37:
#line 142 "fwlang.yy"
    {(yyval.condition_rec) = (yysemantic_stack_[(3) - (2)].condition_rec);}
    break;

  case 38:
#line 143 "fwlang.yy"
    { (yyval.condition_rec) = GetLoggedCondition((yysemantic_stack_[(2) - (2)].input_chain));}
    break;

  case 39:
#line 146 "fwlang.yy"
    {(yyval.condition_rec)=BuildConditionFromGroup((yysemantic_stack_[(2) - (2)].group_rec), 0);}
    break;

  case 40:
#line 147 "fwlang.yy"
    {(yyval.condition_rec)=BuildConditionFromGroup((yysemantic_stack_[(2) - (2)].group_rec),1);}
    break;

  case 41:
#line 148 "fwlang.yy"
    {(yyval.condition_rec)=BuildConditionFromService((yysemantic_stack_[(2) - (2)].service_rec), 0);}
    break;

  case 42:
#line 149 "fwlang.yy"
    {(yyval.condition_rec)=BuildConditionFromService((yysemantic_stack_[(2) - (2)].service_rec), 1);}
    break;

  case 43:
#line 150 "fwlang.yy"
    {(yyval.condition_rec)=BuildConditionFromState((yysemantic_stack_[(2) - (2)].sv));}
    break;

  case 44:
#line 151 "fwlang.yy"
    {(yyval.condition_rec)=BuildConditionFromFlag((yysemantic_stack_[(2) - (2)].fv));}
    break;

  case 45:
#line 152 "fwlang.yy"
    {(yyval.condition_rec)=BuildConditionFromIface((yysemantic_stack_[(2) - (2)].name), 0); delete[] (yysemantic_stack_[(2) - (2)].name);}
    break;

  case 46:
#line 153 "fwlang.yy"
    {(yyval.condition_rec)=BuildConditionFromIface((yysemantic_stack_[(2) - (2)].name), 1); delete[] (yysemantic_stack_[(2) - (2)].name);}
    break;

  case 47:
#line 154 "fwlang.yy"
    {(yyval.condition_rec)=BuildAcceptCondition((yysemantic_stack_[(2) - (2)].input_chain));}
    break;

  case 48:
#line 155 "fwlang.yy"
    {(yyval.condition_rec)=BuildDropCondition((yysemantic_stack_[(2) - (2)].input_chain));}
    break;

  case 49:
#line 158 "fwlang.yy"
    {(yyval.group_rec) = GroupLookup((yysemantic_stack_[(1) - (1)].name)); delete[] (yysemantic_stack_[(1) - (1)].name);}
    break;

  case 50:
#line 159 "fwlang.yy"
    {(yyval.group_rec) = BuildGroupFromAddress((yysemantic_stack_[(1) - (1)].address_rec));}
    break;

  case 51:
#line 161 "fwlang.yy"
    {(yyval.service_rec) = ServiceLookup((yysemantic_stack_[(1) - (1)].name)); delete[] (yysemantic_stack_[(1) - (1)].name);}
    break;

  case 52:
#line 162 "fwlang.yy"
    {(yyval.service_rec) = BuildServiceFromPort((yysemantic_stack_[(1) - (1)].port_rec));}
    break;

  case 53:
#line 164 "fwlang.yy"
    {(yyval.sv)=0;}
    break;

  case 54:
#line 164 "fwlang.yy"
    {(yyval.sv)=1;}
    break;

  case 55:
#line 164 "fwlang.yy"
    {(yyval.sv)=2;}
    break;

  case 56:
#line 164 "fwlang.yy"
    {(yyval.sv)=3;}
    break;

  case 57:
#line 166 "fwlang.yy"
    {(yyval.fv)=0;}
    break;

  case 58:
#line 166 "fwlang.yy"
    {(yyval.fv)=1;}
    break;

  case 59:
#line 166 "fwlang.yy"
    {(yyval.fv)=2;}
    break;

  case 60:
#line 166 "fwlang.yy"
    {(yyval.fv)=3;}
    break;

  case 61:
#line 166 "fwlang.yy"
    {(yyval.fv)=4;}
    break;

  case 62:
#line 166 "fwlang.yy"
    {(yyval.fv)=5;}
    break;

  case 63:
#line 168 "fwlang.yy"
    {(yyval.port_rec) = BuildPort((yysemantic_stack_[(2) - (1)].prot), (yysemantic_stack_[(2) - (2)].port_rec));}
    break;

  case 64:
#line 170 "fwlang.yy"
    {(yyval.prot) = 0;}
    break;

  case 65:
#line 170 "fwlang.yy"
    {(yyval.prot) = 1;}
    break;

  case 66:
#line 170 "fwlang.yy"
    { (yyval.prot) = 2;}
    break;

  case 67:
#line 170 "fwlang.yy"
    { (yyval.prot) = -1;}
    break;

  case 68:
#line 172 "fwlang.yy"
    {(yyval.address_rec) = ParseAddr((yysemantic_stack_[(7) - (1)].val),(yysemantic_stack_[(7) - (3)].val),(yysemantic_stack_[(7) - (5)].val),(yysemantic_stack_[(7) - (7)].val));}
    break;

  case 69:
#line 173 "fwlang.yy"
    {(yyval.address_rec)=ParseAddr((yysemantic_stack_[(5) - (1)].val),(yysemantic_stack_[(5) - (3)].val),(yysemantic_stack_[(5) - (5)].val),NULL);}
    break;

  case 70:
#line 174 "fwlang.yy"
    {(yyval.address_rec)=ParseAddr((yysemantic_stack_[(3) - (1)].val),(yysemantic_stack_[(3) - (3)].val),NULL,NULL);}
    break;

  case 71:
#line 175 "fwlang.yy"
    {(yyval.address_rec)=ParseAddr((yysemantic_stack_[(1) - (1)].val),NULL,NULL,NULL);}
    break;

  case 72:
#line 177 "fwlang.yy"
    {(yyval.port_rec)=ParsePort((yysemantic_stack_[(1) - (1)].val));}
    break;


    /* Line 675 of lalr1.cc.  */
#line 709 "fwlang.cc"
	default: break;
      }
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[0] = yylloc;
    if (yyerrstatus_ == 3)
      {
	/* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

	if (yychar <= yyeof_)
	  {
	  /* Return failure if at end of input.  */
	  if (yychar == yyeof_)
	    YYABORT;
	  }
	else
	  {
	    yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
	    yychar = yyempty_;
	  }
      }

    /* Else will try to reuse look-ahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;

    yyerror_range[0] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (yyn != yypact_ninf_)
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	YYABORT;

	yyerror_range[0] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    if (yyn == yyfinal_)
      goto yyacceptlab;

    yyerror_range[1] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the look-ahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		   &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyeof_ && yychar != yyempty_)
      yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval, &yylloc);

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (yystate_stack_.height () != 1)
      {
	yydestruct_ ("Cleanup: popping",
		   yystos_[yystate_stack_[0]],
		   &yysemantic_stack_[0],
		   &yylocation_stack_[0]);
	yypop_ ();
      }

    return yyresult;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (int yystate, int tok)
  {
    std::string res;
    YYUSE (yystate);
#if YYERROR_VERBOSE
    int yyn = yypact_[yystate];
    if (yypact_ninf_ < yyn && yyn <= yylast_)
      {
	/* Start YYX at -YYN if negative to avoid negative indexes in
	   YYCHECK.  */
	int yyxbegin = yyn < 0 ? -yyn : 0;

	/* Stay within bounds of both yycheck and yytname.  */
	int yychecklim = yylast_ - yyn + 1;
	int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
	int count = 0;
	for (int x = yyxbegin; x < yyxend; ++x)
	  if (yycheck_[x + yyn] == x && x != yyterror_)
	    ++count;

	// FIXME: This method of building the message is not compatible
	// with internationalization.  It should work like yacc.c does it.
	// That is, first build a string that looks like this:
	// "syntax error, unexpected %s or %s or %s"
	// Then, invoke YY_ on this string.
	// Finally, use the string as a format to output
	// yytname_[tok], etc.
	// Until this gets fixed, this message appears in English only.
	res = "syntax error, unexpected ";
	res += yytnamerr_ (yytname_[tok]);
	if (count < 5)
	  {
	    count = 0;
	    for (int x = yyxbegin; x < yyxend; ++x)
	      if (yycheck_[x + yyn] == x && x != yyterror_)
		{
		  res += (!count++) ? ", expecting " : " or ";
		  res += yytnamerr_ (yytname_[x]);
		}
	  }
      }
    else
#endif
      res = YY_("syntax error");
    return res;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const signed char parser::yypact_ninf_ = -60;
  const signed char
  parser::yypact_[] =
  {
         0,   -33,   -27,    43,   -32,   -60,    23,     0,   -42,   -29,
     -28,   -13,    28,    10,   -60,   -60,   -60,   -60,   -60,   -60,
     -60,   -60,   -60,   -32,    69,   -32,   -32,    69,    69,    29,
      38,   -12,    42,    -4,    -4,   -20,   -20,   -16,   -60,   -60,
     -60,   -60,   -60,   -60,   -60,    56,    28,   -60,   -60,   -60,
     -60,   -60,    10,   -60,    58,   -59,   -60,   -60,   -60,   -60,
       5,   -60,   -60,   -60,   -60,   -60,   -60,   -60,   -60,   -60,
     -60,   -60,   -60,   -60,   -60,   -60,   -60,   -60,   -60,   -60,
     -60,   -60,   -60,   -60,   -60,   -60,   -60,   -60,   -60,   -60,
     -32,   -32,   -32,    59,   -60,   -60,   -60,   -60,   -60,    17,
     -60,   -59,    60,    62,    63,    65,   -60
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  parser::yydefact_[] =
  {
         0,     0,     0,     0,     0,     8,     0,     2,     0,     0,
       0,     0,     0,     0,    27,    28,    29,    30,    31,    32,
      15,    16,    17,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    33,     1,
       3,     4,     5,     6,     7,    71,     9,    12,    65,    66,
      64,    67,    10,    14,     0,    18,    24,    25,    26,    38,
       0,    36,    48,    47,    46,    45,    57,    58,    59,    60,
      61,    62,    44,    53,    54,    55,    56,    43,    51,    41,
      52,    42,    49,    40,    50,    39,    20,    22,    21,    23,
       0,     0,     0,     0,    11,    13,    72,    63,    37,    34,
      35,    19,    70,     0,    69,     0,    68
  };

  /* YYPGOTO[NTERM-NUM].  */
  const signed char
  parser::yypgoto_[] =
  {
       -60,    83,   -60,   -60,   -60,   -60,   -60,   -60,   -60,   -60,
      44,   -60,   -23,   -60,    57,    61,   -60,   -60,     4,   -60,
      -7,   -60
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  parser::yydefgoto_[] =
  {
        -1,     6,     7,     8,     9,    46,    52,    10,    11,    92,
      59,    23,    37,    38,    83,    79,    77,    72,    80,    54,
      84,    97
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char parser::yytable_ninf_ = -1;
  const unsigned char
  parser::yytable_[] =
  {
        55,    24,    60,    61,     1,    47,     2,    45,     3,    90,
       4,    91,    12,    86,    87,    88,    89,    53,    13,    48,
      49,    50,    51,    39,    41,    82,    66,    67,    68,    69,
      70,    71,    25,    48,    49,    50,    51,    42,    43,    94,
      26,    78,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    90,    44,    91,    45,    95,    14,    15,    16,
      17,    18,    19,    20,    21,    22,     5,    99,   100,   101,
      98,    62,    63,    90,    64,    91,    73,    74,    75,    76,
      56,    57,    58,    65,    93,    96,   102,    91,   103,   104,
      40,   105,   106,    85,     0,    81
  };

  /* YYCHECK.  */
  const signed char
  parser::yycheck_[] =
  {
        23,    33,    25,    26,     4,    12,     6,    27,     8,    68,
      10,    70,    45,    29,    30,    31,    32,    13,    45,    23,
      24,    25,    26,     0,    66,    45,    38,    39,    40,    41,
      42,    43,    64,    23,    24,    25,    26,    66,    66,    46,
      72,    45,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    68,    66,    70,    27,    52,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    66,    90,    91,    92,
      65,    27,    28,    68,    45,    70,    34,    35,    36,    37,
      11,    12,    13,    45,    28,    27,    27,    70,    28,    27,
       7,    28,    27,    36,    -1,    34
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  parser::yystos_[] =
  {
         0,     4,     6,     8,    10,    66,    85,    86,    87,    88,
      91,    92,    45,    45,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    95,    33,    64,    72,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    96,    97,     0,
      85,    66,    66,    66,    66,    27,    89,   104,    23,    24,
      25,    26,    90,   102,   103,    96,    11,    12,    13,    94,
      96,    96,    94,    94,    45,    45,    38,    39,    40,    41,
      42,    43,   101,    34,    35,    36,    37,   100,    45,    99,
     102,    99,    45,    98,   104,    98,    29,    30,    31,    32,
      68,    70,    93,    28,   104,   102,    27,   105,    65,    96,
      96,    96,    27,    28,    27,    28,    27
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  parser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  parser::yyr1_[] =
  {
         0,    84,    85,    85,    86,    86,    86,    86,    86,    87,
      88,    89,    89,    90,    90,    91,    91,    91,    91,    92,
      93,    93,    93,    93,    94,    94,    94,    95,    95,    95,
      95,    95,    95,    96,    96,    96,    96,    96,    96,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    98,
      98,    99,    99,   100,   100,   100,   100,   101,   101,   101,
     101,   101,   101,   102,   103,   103,   103,   103,   104,   104,
     104,   104,   105
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  parser::yyr2_[] =
  {
         0,     2,     1,     2,     2,     2,     2,     2,     1,     3,
       3,     2,     1,     2,     1,     2,     2,     2,     3,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     2,     3,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     7,     5,
       3,     1,     1
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const parser::yytname_[] =
  {
    "\"end of file\"", "error", "$undefined", "\"group\"", "GROUP",
  "\"service\"", "SERVICE", "\"query\"", "QUERY", "\"assert\"", "ASSERT",
  "INPUT", "FORWARD", "\"selected chain\"", "PACKET", "SPORT", "DPORT",
  "SADDY", "DADDY", "\"query subject\"", "\"equivalence host classes\"",
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
  "ACCEPTED", "OUTFACE", "INFACE", "WITH", "IN", "ON", "FOR", "TO", "FROM",
  "$accept", "statement", "expression", "group_expression",
  "service_expression", "addy_list", "port_list", "query_expression",
  "assert_expression", "assert_op", "input_chain", "subject", "condition",
  "simple_condition", "compound_addy", "compound_port", "state_value",
  "flag_name", "complete_port", "protocol", "addr", "port", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const parser::rhs_number_type
  parser::yyrhs_[] =
  {
        85,     0,    -1,    86,    -1,    86,    85,    -1,    87,    66,
      -1,    88,    66,    -1,    91,    66,    -1,    92,    66,    -1,
      66,    -1,     4,    45,    89,    -1,     6,    45,    90,    -1,
      89,   104,    -1,   104,    -1,    90,   102,    -1,   102,    -1,
       8,    20,    -1,     8,    21,    -1,     8,    22,    -1,     8,
      95,    96,    -1,    10,    96,    93,    96,    -1,    29,    -1,
      31,    -1,    30,    -1,    32,    -1,    11,    -1,    12,    -1,
      13,    -1,    14,    -1,    15,    -1,    16,    -1,    17,    -1,
      18,    -1,    19,    -1,    97,    -1,    96,    68,    96,    -1,
      96,    70,    96,    -1,    72,    96,    -1,    64,    96,    65,
      -1,    33,    94,    -1,    83,    98,    -1,    82,    98,    -1,
      80,    99,    -1,    81,    99,    -1,    79,   100,    -1,    78,
     101,    -1,    77,    45,    -1,    76,    45,    -1,    75,    94,
      -1,    74,    94,    -1,    45,    -1,   104,    -1,    45,    -1,
     102,    -1,    34,    -1,    35,    -1,    36,    -1,    37,    -1,
      38,    -1,    39,    -1,    40,    -1,    41,    -1,    42,    -1,
      43,    -1,   103,   105,    -1,    25,    -1,    23,    -1,    24,
      -1,    26,    -1,    27,    28,    27,    28,    27,    28,    27,
      -1,    27,    28,    27,    28,    27,    -1,    27,    28,    27,
      -1,    27,    -1,    27,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned char
  parser::yyprhs_[] =
  {
         0,     0,     3,     5,     8,    11,    14,    17,    20,    22,
      26,    30,    33,    35,    38,    40,    43,    46,    49,    53,
      58,    60,    62,    64,    66,    68,    70,    72,    74,    76,
      78,    80,    82,    84,    86,    90,    94,    97,   101,   104,
     107,   110,   113,   116,   119,   122,   125,   128,   131,   134,
     136,   138,   140,   142,   144,   146,   148,   150,   152,   154,
     156,   158,   160,   162,   165,   167,   169,   171,   173,   181,
     187,   191,   193
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned char
  parser::yyrline_[] =
  {
         0,    87,    87,    87,    88,    89,    90,    91,    92,    95,
      97,    99,   100,   102,   103,   105,   106,   107,   108,   114,
     118,   119,   120,   121,   124,   125,   126,   129,   130,   131,
     132,   133,   134,   138,   139,   140,   141,   142,   143,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   158,
     159,   161,   162,   164,   164,   164,   164,   166,   166,   166,
     166,   166,   166,   168,   170,   170,   170,   170,   172,   173,
     174,   175,   177
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "), ";
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  parser::token_number_type
  parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
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
      75,    76,    77,    78,    79,    80,    81,    82,    83
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int parser::yyeof_ = 0;
  const int parser::yylast_ = 95;
  const int parser::yynnts_ = 22;
  const int parser::yyempty_ = -2;
  const int parser::yyfinal_ = 39;
  const int parser::yyterror_ = 1;
  const int parser::yyerrcode_ = 256;
  const int parser::yyntokens_ = 84;

  const unsigned int parser::yyuser_token_number_max_ = 338;
  const parser::token_number_type parser::yyundef_token_ = 2;

} // namespace yy

#line 179 "fwlang.yy"

void
yy::parser::error (const yy::parser::location_type& l, const std::string& m)
{
   pi.error(l, m);
}

