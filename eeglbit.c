/* eeglbit.c - random number generator Version 2.0.0                 */
/* Copyright (C) 2019-2020 aquila57 at github.com                    */

/* This program is free software; you can redistribute it and/or     */
/* modify it under the terms of the GNU General Public License as    */
/* published by the Free Software Foundation; either version 2 of    */
/* the License, or (at your option) any later version.               */

/* This program is distributed in the hope that it will be useful,   */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of    */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the      */
/* GNU General Public License for more details.                      */

/* You should have received a copy of the GNU General Public License */
/* along with this program; if not, write to:                        */

   /* Free Software Foundation, Inc.                                 */
   /* 59 Temple Place - Suite 330                                    */
   /* Boston, MA 02111-1307, USA.                                    */

/*********************************************************************/
/* This is a 64-bit version of eeglbit.c.                            */
/* It is based on Version 1.0.0 of eeglbit.c                         */
/* at http://www.github.com/aquila62/eegl                            */
/*********************************************************************/

/********************************************************/
/* The LFSR in this generator comes from the following  */
/* http://courses.cse.tamu.edu/walker/csce680/          */
/* lfsr_table.pdf                                       */
/* 64 bit LFSR is 64,63,61,60 with low order bit equal  */
/* to 64                                                */
/********************************************************/

/* this subroutine generates a random bit                 */

#include "eegl.h"

int eeglbit(eefmt *ee)
   {
   int i;
   int bit;                 /* random bit output */
   unsigned int lfsr;
   /* The output bit is the result of XOR'ing           */
   /* all 32 bits of a random UINT                      */
   /* A faster way to produce a single random bit is    */
   /* bit = eegl(ee) & 1;                               */
   i = 32;
   bit = 0;
   lfsr = eegl(ee);
   while (i--)
      {
      bit ^= lfsr;
      lfsr >>= 1;
      } /* for each bit in ee->lfsr */
   return(bit & 1);         /* return random bit */
   } /* eeglbit */
