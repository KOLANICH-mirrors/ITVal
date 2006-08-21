#ifndef __PARSER_INTERFACE_HH
#define __PARSER_INTERFACE_HH

#include <string>

namespace yy
{
  class location;
  class parser;
};

#define YY_DECL int yylex (yy::parser::semantic_type* yylval, yy::location* yylloc, parser_interface& parser)

class parser_interface
{
public:
  parser_interface ();

  // Handling the scanner
  void scan_begin ();
  void scan_end ();
  bool trace_scanning;

  //Handling the parser.
  void parse (const std::string & f);

  std::string file;
  bool trace_parsing;

  // Error handling.
  void error (const yy::location & l, const std::string & m);
  void error (const std::string & m);
};
#endif
