/* eegldspl.c - eegl RNG Display the State  Version 0.1.0            */
/* Copyright (C) 2020 aquila57 at github.com                         */

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

/* Display the state of the eegl64 generator, including the current  */
/* 64 bit LFSR, previous, prior-previous, out bit, carry bit,        */
/* and the 16384 word array for the Bays-Durham shuffle.             */
/* Output of this subroutine is to stderr.                           */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "eegl.h"

#define STATES (16384)

void eegldspl(eefmt *ee, int option)
   {
   /*****************************************************/
   /* Print eegl64 state to stderr                      */
   /* If option is not zero, print entire state array   */
   /*****************************************************/
   fprintf(stderr,"upper 32 bit LFSR %08x ", ee->lfsr0);
   fprintf(stderr,"lower 32 bit LFSR %08x\n", ee->lfsr);
   fprintf(stderr,"LFSR out %08x ", ee->out);
   fprintf(stderr,"LFSR carry bit %08x\n", ee->lowbit);
   fprintf(stderr,"previous LFSR %08x ", ee->prev);
   fprintf(stderr,"prior-previous LFSR %08x\n", ee->pprev);
   fprintf(stderr,"eegl output %08x\n",
      ee->pprev ^ ee->prev ^ ee->lfsr);
   if (!option)
      {
      int i;
      unsigned int *p,*q;
      i = 0;
      p = (unsigned int *) ee->state;
      q = (unsigned int *) ee->state + STATES;
      fprintf(stderr,"State array:\n");
      while (p < q)
         {
         fprintf(stderr,"%08x ", *p++);
	 i++;
	 if (i >= 8)
	    {
	    fprintf(stderr,"\n");
	    i = 0;
	    } /* end of line */
	 } /* for each word in the state array */
      if (i) fprintf(stderr,"\n");
      } /* if display the state array */
   } /* eegldspl */
