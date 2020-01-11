#  eegllib.mak - Compile eegl64 library Version 0.1.0
#  Copyright (C) 2020 aquila57 at github.com

#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License as
#  published by the Free Software Foundation; either version 2 of
#  the License, or (at your option) any later version.

#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.

#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to:

   #  Free Software Foundation, Inc.
   #  59 Temple Place - Suite 330
   #  Boston, MA 02111-1307, USA.

#--------------------------------------------------------
#  The LFSR in this generator comes from the following
#  website http://www.xilinx.com/support/documentation/
#  application_notes/xapp052.pdf
#--------------------------------------------------------

OBJ=eeglcrc.o \
	eeglsd.o \
	eeglinit.o \
	eeglstrt.o \
	eegl.o \
	eeglint.o \
	eeglpwr.o \
	eeglbit.o \
	eeglunif.o \
	eeglfrac.o \
	eegldspl.o \
	eeglabt.o

CC=gcc

AR=ar

CFLAGS=-c -Wall -O2

LDFLAGS=

libeegl.a:			$(OBJ)
		rm -f libeegl.a
		$(AR) r libeegl.a $(OBJ)

eeglcrc.o:			eeglcrc.c
		$(CC) $(CFLAGS) eeglcrc.c

eeglsd.o:			eeglsd.c
		$(CC) $(CFLAGS) eeglsd.c

eeglinit.o:			eeglinit.c
		$(CC) $(CFLAGS) eeglinit.c

eeglstrt.o:			eeglstrt.c
		$(CC) $(CFLAGS) eeglstrt.c

eegl.o:				eegl.c
		$(CC) $(CFLAGS) eegl.c

eeglint.o:			eeglint.c
		$(CC) $(CFLAGS) eeglint.c

eeglpwr.o:			eeglpwr.c
		$(CC) $(CFLAGS) eeglpwr.c

eeglbit.o:			eeglbit.c
		$(CC) $(CFLAGS) eeglbit.c

eeglunif.o:			eeglunif.c
		$(CC) $(CFLAGS) eeglunif.c

eeglfrac.o:			eeglfrac.c
		$(CC) $(CFLAGS) eeglfrac.c

eegldspl.o:			eegldspl.c
		$(CC) $(CFLAGS) eegldspl.c

eeglabt.o:			eeglabt.c
		$(CC) $(CFLAGS) eeglabt.c

clean:
		rm -f $(OBJ) libeegl.a
