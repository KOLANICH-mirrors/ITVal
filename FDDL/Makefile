#FDDL: A Free Decision Diagram Library
#Copyright (C) 2004 Robert Marmorstein

#This program is free software; you can redistribute it and/or
#modify it under the terms of the GNU General Public License
#as published by the Free Software Foundation; either version 2
#of the License, or (at your option) any later version.

#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.

#You should have received a copy of the GNU General Public License
#along with this program; if not, write to the Free Software
#Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#A full-text version is located in the LICENSE file distributed with this
#utility.

#You may contact the author at rmmarm@wm.edu or by sending mail to:

#Robert Marmorstein
#Department of Computer Science
#College of William and Mary
#Williamsburg, VA 23185

GXX = g++ -g 

fddl.so: working/mdd.o working/uniquetable.o working/api.o working/caches.o 
	ar r fddl.so working/mdd.o working/uniquetable.o working/api.o working/caches.o 
	ranlib fddl.so 
clean:
	rm -r -f *.o core.* working/*.o test? test?? fddl.so 
        
working/api.o: api.cc mdd.h mddtypes.h datastructures/dynarray.h
	$(GXX) -c api.cc -g -o working/api.o

working/mdd.o: mdd.cc mdd.h mddtypes.h datastructures/dynarray.h datastructures/portset.h
	$(GXX) -c mdd.cc -g -o working/mdd.o

working/uniquetable.o: datastructures/uniquetable.cc datastructures/uniquetable.h mdd.h mddtypes.h datastructures/dynarray.h
	$(GXX) -c datastructures/uniquetable.cc -g -o working/uniquetable.o

working/caches.o: datastructures/caches.cc datastructures/caches.h mdd.h mddtypes.h
	$(GXX) -c datastructures/caches.cc -g -o working/caches.o
