AM_YFLAGS = -d
bin_PROGRAMS = ITVal

ITVal_SOURCES = src/fwlang.ll src/fwlang.tab.cc src/ITVal.cc src/chains.cc src/debug.cc src/firewall.cc src/iface.cc src/nat.cc src/nat_iface.cc src/netconvert.cc src/parser_interface.cc src/rule_parser.cc src/rules.cc src/structures.cc src/fwmdd.cc src/topology.cc src/chains.h src/debug.h src/firewall.h src/fwmdd.h src/iface.h src/location.hh src/nat.h src/parser_interface.hh src/position.hh src/ranges.h src/rule_parser.h src/rules.h src/stack.hh src/structures.h src/topology.h src/fwlang.tab.hh

ITVal_LDADD = @LEXLIB@ FDDL/libFDDL.la

SUBDIRS = FDDL
