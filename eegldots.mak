#!/usr/bin/make

# eegldots.mak Version 1.0.0. Compile eegldots.c.
# Copyright (C) 2019-2020 aquila57 at github.com

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

#----------------------------------------------------------------------
#  The LFSR in this generator comes from the following
#  http://courses.cse.tamu.edu/walker/csce680/
#  lfsr_table.pdf
#  64 bit LFSR is 64,63,61,60 with low order bit equal
#  to 64
#----------------------------------------------------------------------

OBJ=eegldots.o

CC=gcc

CFLAGS=-c -Wall -O2 -I/usr/X11R6/include/X11

LDFLAGS=-L. -leegl -L/usr/X11R6/lib -lX11

eegldots:			$(OBJ)
		$(CC) -Wall -O2 $(OBJ) -o eegldots $(LDFLAGS)

eegldots.o:			eegldots.c
		$(CC) $(CFLAGS) eegldots.c

clean:
		rm -f $(OBJ) eegldots
