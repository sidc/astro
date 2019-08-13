# $Header$
# this Makefile creates a SwissEph library and a swetest sample on 64-bit
# Redhat Enterprise Linux RHEL 6.

# The mode marked as 'Linux' should also work with the GNU C compiler
# gcc on other systems. 

# If you modify this makefile for another compiler, please
# let us know. We would like to add as many variations as possible.
# If you get warnings and error messages from your compiler, please
# let us know. We like to fix the source code so that it compiles
# free of warnings.
# send email to the Swiss Ephemeris mailing list.
#

CFLAGS = -g -Wall -fPIC  	# for Linux and other gcc systems
OP=$(CFLAGS)  
CC=cc	#for Linux

# compilation rule for general cases
.o :
	$(CC) $(OP) -o $@ $? -lm
.c.o:
	$(CC) -c $(OP) $<     

SWEOBJ = swedate.o swehouse.o swejpl.o swemmoon.o swemplan.o swepcalc.o sweph.o\
	swepdate.o swephlib.o swecl.o swehel.o

swetest: swetest.o libswe.a
	$(CC) $(OP) -o swetest swetest.o -L. -lswe -lm -ldl

swemini: swemini.o libswe.a
	$(CC) $(OP) -o swemini swemini.o -L. -lswe -lm -ldl

AlcorMizar: AlcorMizar.o libswe.a
	$(CC) $(OP) -o AlcorMizar AlcorMizar.o -L. -lswe -lm -ldl

AlcorVasistha: AlcorVasistha.o libswe.a
	$(CC) $(OP) -o AlcorVasistha AlcorVasistha.o -L. -lswe -lm -ldl

Krishna_GS: Krishna_GS.o libswe.a
	$(CC) $(OP) -o Krishna_GS Krishna_GS.o -L. -lswe -lm -ldl

Krishna_Sidereal: Krishna_Sidereal.o libswe.a
	$(CC) $(OP) -o Krishna_Sidereal Krishna_Sidereal.o -L. -lswe -lm -ldl

mb1: mb1.o libswe.a
	$(CC) $(OP) -o mb1 mb1.o -L. -lswe -lm -ldl

mb2: mb2.o libswe.a
	$(CC) $(OP) -o mb2 mb2.o -L. -lswe -lm -ldl

eclipse: eclipse.o libswe.a
	$(CC) $(OP) -o eclipse eclipse.o -L. -lswe -lm -ldl

Krishna_Kham: Krishna_Kham.o libswe.a
	$(CC) $(OP) -o Krishna_Kham Krishna_Kham.o -L. -lswe -lm -ldl

Krishna_Tropical: Krishna_Tropical.o libswe.a
	$(CC) $(OP) -o Krishna_Tropical Krishna_Tropical.o -L. -lswe -lm -ldl

moonRA: moonRA.o libswe.a
	$(CC) $(OP) -o moonRA moonRA.o -L. -lswe -lm -ldl


try1: try1.o libswe.a
	$(CC) $(OP) -o try1 try1.o -L. -lswe -lm

# create an archive and a dynamic link libary fro SwissEph
# a user of this library will inlcude swephexp.h  and link with -lswe

libswe.a: $(SWEOBJ)
	ar r libswe.a	$(SWEOBJ)

libswe.so: $(SWEOBJ)
	$(CC) -shared -o libswe.so $(SWEOBJ)

clean:
	rm -f *.o swetest libswe*
	
###
swecl.o: swejpl.h sweodef.h swephexp.h swedll.h sweph.h swephlib.h
sweclips.o: sweodef.h swephexp.h swedll.h
swedate.o: swephexp.h sweodef.h swedll.h
swehel.o: swephexp.h sweodef.h swedll.h
swehouse.o: swephexp.h sweodef.h swedll.h swephlib.h swehouse.h
swejpl.o: swephexp.h sweodef.h swedll.h sweph.h swejpl.h
swemini.o: swephexp.h sweodef.h swedll.h
swemmoon.o: swephexp.h sweodef.h swedll.h sweph.h swephlib.h
swemplan.o: swephexp.h sweodef.h swedll.h sweph.h swephlib.h swemptab.h
swepcalc.o: swepcalc.h swephexp.h sweodef.h swedll.h
sweph.o: swejpl.h sweodef.h swephexp.h swedll.h sweph.h swephlib.h
swephlib.o: swephexp.h sweodef.h swedll.h sweph.h swephlib.h
swetest.o: swephexp.h sweodef.h swedll.h
