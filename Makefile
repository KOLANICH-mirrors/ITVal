all: GXX = c++ -g -Wall

debug: GXX = c++ -g -Wall -DDEBUG

all: ITVal 

debug: fwlang.tab.c main.c work/nat.o work/structures.o work/iface.o work/netconvert.o work/rules.o work/rule_parser.o work/build.o FDDL/fddl.so work/nat_iface.o work/firewall.o
	$(GXX) lex.yy.c fwlang.tab.c work/nat.o work/structures.o work/iface.o work/netconvert.o work/rules.o work/rule_parser.o work/build.o work/nat_iface.o main.c work/firewall.o FDDL/fddl.so debug.c -o ITVal 
        
ITVal: fwlang.tab.c main.c work/nat.o work/structures.o work/iface.o work/netconvert.o work/rules.o work/rule_parser.o work/build.o work/firewall.o FDDL/fddl.so work/nat_iface.o
	$(GXX) lex.yy.c fwlang.tab.c work/nat.o work/structures.o work/iface.o work/netconvert.o work/rules.o work/rule_parser.o work/nat_iface.o work/build.o work/firewall.o main.c FDDL/fddl.so debug.c -o ITVal 

fwlang.tab.c: fwlang.y lex.yy.c
	bison -d fwlang.y

lex.yy.c: fwlang.l
	flex fwlang.l
        
work/build.o: build.c rules.h ranges.h iface.h chains.h debug.h
	$(GXX) -c build.c -o work/build.o

work/rule_parser.o: rule_parser.c rules.h
	$(GXX) -c rule_parser.c -o work/rule_parser.o

work/rules.o: rules.c rules.h 
	$(GXX) -c rules.c -o work/rules.o

work/nat.o: nat.cc nat.h FDDL/mdd.h
	$(GXX) -c nat.cc -o work/nat.o

work/nat_iface.o: nat_iface.cc chains.h iface.h 
	$(GXX) -c nat_iface.cc -o work/nat_iface.o

work/netconvert.o: netconvert.c ranges.h
	$(GXX) -c netconvert.c -o work/netconvert.o

work/iface.o: iface.cc iface.h chains.h
	$(GXX) -c iface.cc -o work/iface.o

work/structures.o: structures.c structures.h FDDL/mdd.h
	$(GXX) -c structures.c -o work/structures.o

work/firewall.o: firewall.cc firewall.h FDDL/mdd.h chains.h
	$(GXX) -c firewall.cc -o work/firewall.o

clean: 
	make -C FDDL clean
	rm -f ITVal
	rm -f fwlang.tab.c
	rm -f lex.yy.c
	rm -f work/*.o

FDDL/fddl.so: FDDL/mdd.h 
	make -C FDDL

test:
	iptables -L -n > Rsets/test.filter
	iptables -L -n -t nat > Rsets/test.nat	
	./ITVal Examples/Attacks.fw Rsets/test.filter Rsets/test.nat 
	./ITVal Examples/Trojans.fw Rsets/test.filter Rsets/test.nat 

indent:
	indent -br -bad -bap -bbb -sob -cdb -sc -nce -cdw -cli3 -cbi0 -ss -npcs -cs -bs -saf -sai -saw -nprs -di8 -nbc -T state_triple -T potential_range_element -T range_element -T event -T level -T node_idx -T arc_idx -brs -i3 -ci3 -lp -ts3 -ppi3 -bbo -pmt -npsl *.c 
	indent -br -bad -bap -bbb -sob -cdb -sc -nce -cdw -cli3 -cbi0 -ss -npcs -cs -bs -saf -sai -saw -nprs -di8 -nbc -T state_triple -T potential_range_element -T range_element -T event -T level -T node_idx -T arc_idx -brs -i3 -ci3 -lp -ts3 -ppi3 -bbo -pmt -npsl *.cc
	indent -br -bad -bap -bbb -sob -cdb -sc -nce -cdw -cli3 -cbi0 -ss -npcs -cs -bs -saf -sai -saw -nprs -di8 -nbc -T state_triple -T potential_range_element -T range_element -T event -T level -T node_idx -T arc_idx -brs -i3 -ci3 -lp -ts3 -ppi3 -bbo -pmt -npsl *.h
	indent -br -bad -bap -bbb -sob -cdb -sc -nce -cdw -cli3 -cbi0 -ss -npcs -cs -bs -saf -sai -saw -nprs -di8 -nbc -T state_triple -T potential_range_element -T range_element -T event -T level -T node_idx -T arc_idx -brs -i3 -ci3 -lp -ts3 -ppi3 -bbo -pmt -npsl FDDL/*.h
	indent -br -bad -bap -bbb -sob -cdb -sc -nce -cdw -cli3 -cbi0 -ss -npcs -cs -bs -saf -sai -saw -nprs -di8 -nbc -T state_triple -T potential_range_element -T range_element -T event -T level -T node_idx -T arc_idx -brs -i3 -ci3 -lp -ts3 -ppi3 -bbo -pmt -npsl FDDL/datastructures/*.h
	indent -br -bad -bap -bbb -sob -cdb -sc -nce -cdw -cli3 -cbi0 -ss -npcs -cs -bs -saf -sai -saw -nprs -di8 -nbc -T state_triple -T potential_range_element -T range_element -T event -T level -T node_idx -T arc_idx -brs -i3 -ci3 -lp -ts3 -ppi3 -bbo -pmt -npsl FDDL/*.cc
	indent -br -bad -bap -bbb -sob -cdb -sc -nce -cdw -cli3 -cbi0 -ss -npcs -cs -bs -saf -sai -saw -nprs -di8 -nbc -T state_triple -T potential_range_element -T range_element -T event -T level -T node_idx -T arc_idx -brs -i3 -ci3 -lp -ts3 -ppi3 -bbo -pmt -npsl FDDL/datastructures/*.cc
