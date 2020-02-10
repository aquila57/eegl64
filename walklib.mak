# walklib.mak - Compile libwalk.a  Version 0.1.0
# Copyright (C) 2020  aquila57 at github.com

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to:

# 	Free Software Foundation, Inc.
# 	59 Temple Place - Suite 330
# 	Boston, MA  02111-1307, USA.

OBJ=eeglinit.o \
	eegl.o \
	eeglpwr.o \
	eeglint.o \
	eeglabt.o \
	eeglbit.o \
	eeglcrc.o \
	eegldspl.o \
	eeglfrac.o \
	eeglsd.o \
	eeglstrt.o \
	eeglunif.o \
	redraw.o \
	getkey.o \
	ifkey.o \
	initx.o

CC=gcc

CFLAGS=-c -Wall -O2 -I/usr/X11R6/include/X11

LDFLAGS=-L/usr/X11R6/lib -lX11

libwalk.a:		$(OBJ)
		rm -f libwalk.a
		ar r libwalk.a $(OBJ)

eeglinit.o:		eeglinit.c
	$(CC) $(CFLAGS) eeglinit.c

eegl.o:			eegl.c
	$(CC) $(CFLAGS) eegl.c

eeglpwr.o:		eeglpwr.c
	$(CC) $(CFLAGS) eeglpwr.c

eeglint.o:		eeglint.c
	$(CC) $(CFLAGS) eeglint.c

eeglabt.o:		eeglabt.c
	$(CC) $(CFLAGS) eeglabt.c

eeglbit.o:		eeglbit.c
	$(CC) $(CFLAGS) eeglbit.c

eeglcrc.o:		eeglcrc.c
	$(CC) $(CFLAGS) eeglcrc.c

eegldspl.o:		eegldspl.c
	$(CC) $(CFLAGS) eegldspl.c

eeglfrac.o:		eeglfrac.c
	$(CC) $(CFLAGS) eeglfrac.c

eeglsd.o:		eeglsd.c
	$(CC) $(CFLAGS) eeglsd.c

eeglstrt.o:		eeglstrt.c
	$(CC) $(CFLAGS) eeglstrt.c

eeglunif.o:		eeglunif.c
	$(CC) $(CFLAGS) eeglunif.c

redraw.o:		redraw.c
	$(CC) $(CFLAGS) redraw.c

getkey.o:		getkey.c
	$(CC) $(CFLAGS) getkey.c

ifkey.o:		ifkey.c
	$(CC) $(CFLAGS) ifkey.c

initx.o:		initx.c
	$(CC) $(CFLAGS) initx.c

clean:
	rm -f $(OBJ) libwalk.a
