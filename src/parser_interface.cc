#include "parser_interface.hh"
#include "fwlang.tab.hh"

parser_interface::parser_interface():trace_scanning(false),
trace_parsing(false)
{

}

void parser_interface::parse(const std::string & f)
{
   file = f;
   scan_begin();
   yy::parser *parser;
   parser = new yy::parser(*this);
   parser->set_debug_level(trace_parsing);
   parser->parse();
   delete parser;
   scan_end();
}

void parser_interface::error(const yy::location & l, const std::string & m)
{
   std::cerr << l << ": " << m << std::endl;
   exit(-1);
}

void parser_interface::error(const std::string & m)
{
   std::cerr << m << std::endl;
   exit(-1);
}
