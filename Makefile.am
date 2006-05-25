AM_YFLAGS = -d
bin_PROGRAMS = ITVal xITVal

ITVal_SOURCES = src/fwlang.ll src/fwlang.tab.cc src/ITVal.cc src/chains.cc src/debug.cc src/firewall.cc src/iface.cc src/nat.cc src/nat_iface.cc src/netconvert.cc src/parser_interface.cc src/rule_parser.cc src/rules.cc src/parser.cc src/fwmdd.cc src/topology.cc src/chains.h src/debug.h src/firewall.h src/fwmdd.h src/iface.h src/location.hh src/nat.h src/parser_interface.hh src/position.hh src/ranges.h src/rule_parser.h src/rules.h src/stack.hh src/parser.h src/topology.h src/fwlang.tab.hh src/getline.cc src/portset.h

xITVal_SOURCES = src/fwlang.ll src/fwlang.tab.cc gui/PythonPipe.cc gui/PythonPipe.h gui/xITVal.cc src/chains.cc src/debug.cc src/firewall.cc src/iface.cc src/nat.cc src/nat_iface.cc src/netconvert.cc src/parser_interface.cc src/rule_parser.cc src/rules.cc src/parser.cc src/fwmdd.cc src/topology.cc src/chains.h src/debug.h src/firewall.h src/fwmdd.h src/iface.h src/location.hh src/nat.h src/parser_interface.hh src/position.hh src/ranges.h src/rule_parser.h src/rules.h src/stack.hh src/parser.h src/topology.h src/fwlang.tab.hh src/getline.cc gui/gui.py src/portset.h

man_MANS = man/ITVal.n

ITVal_LDADD = @LEXLIB@ FDDL/libFDDL.la

xITVal_LDADD = @LEXLIB@ FDDL/libFDDL.la

EXTRA_DIST = COPYING ChangeLog LICENSE man/ITVal.n

SUBDIRS = FDDL doc 
