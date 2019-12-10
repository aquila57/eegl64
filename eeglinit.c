/* eeglinit.c - eegl RNG initialization Version 2.0.0                */
/* Copyright (C) 2019 aquila57 at github.com                         */

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
/* This is a 64-bit version of eeglinit.c.                           */
/* It is based on Version 1.1.0 of eeglinit.c                        */
/* at http://www.github.com/aquila62/eegl                            */
/*********************************************************************/

/********************************************************/
/* The LFSR in this generator comes from the following  */
/* http://courses.cse.tamu.edu/walker/csce680/          */
/* lfsr_table.pdf                                       */
/********************************************************/

/* This initialization routine is based on date/time/ticks */
/* RNG is an acronym for random number generator */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>
#include "eegl.h"

#define STATES (16384)

eefmt *eeglinit(void)
   {
   int i;
   unsigned int lfsr;          /* temporary lfsr */
   unsigned int dttk;          /* combined date and #ticks */
   unsigned int *stp,*stq;     /* pointers into state array */
   time_t now;                 /* current date and time */
   clock_t clk;                /* current number of ticks */
   struct tms t;               /* structure used by times() */
   eefmt *ee;                  /* eegl structure */

   /***************************************************/
   /* allocate memory for eegl structure */
   /***************************************************/
   ee = (eefmt *) malloc(sizeof(eefmt));
   if (ee == NULL)
      {
      fprintf(stderr,"eeglinit: out of memory "
      "allocating ee\n");
      exit(1);
      } /* out of memory */
   ee->states = STATES; /* save the number of LFSR registers */

   /***************************************************/
   /* allocate memory for eegl state array            */
   /***************************************************/
   ee->state = (unsigned int *)
      malloc(sizeof(unsigned int)*ee->states);
   if (ee->state == NULL)
      {
      fprintf(stderr,"eeglinit: out of memory "
      "allocating ee->state\n");
      exit(1);
      } /* out of memory */

   /***************************************************/
   /* initialize the first LFSR to date/time/ticks    */
   /***************************************************/
   /* get clock ticks since boot                       */
   clk = times(&t);
   /* get date & time                                  */
   time(&now);
   /* combine date, time, and ticks into a single UINT */
   dttk = (unsigned int) (now ^ clk);
   /* initialize the first LFSR to date,time,#ticks    */
   ee->major = ee->lfsr0 = ee->minor = ee->lfsr = dttk;

   /***************************************************/
   /* initialize the state array to random values     */
   /***************************************************/
   stp = (unsigned int *) ee->state;
   stq = (unsigned int *) ee->state + ee->states;
   while (stp < stq)
      {
      int i;
      unsigned int lfsr;
      lfsr = 0;
      i = 32;
      while (i--)
         {
         LFSR;
	 lfsr = (lfsr << 1) | ee->out;
	 } /* for each bit in lfsr */
      *stp++ = lfsr;      /* set to random UINT */
      } /* for each element in ee->state */

   /***************************************************/
   /* initialize pprev to random values               */
   /* this field is backed up in eegl()               */
   /***************************************************/
   lfsr = 0;
   i = 32;
   while (i--)
      {
      LFSR;
      lfsr = (lfsr << 1) | ee->out;
      } /* for each bit in lfsr */
   ee->pprev = lfsr;      /* set to random UINT */

   /***************************************************/
   /* initialize prev to random values               */
   /* this field is backed up in eegl()               */
   /***************************************************/
   lfsr = 0;
   i = 32;
   while (i--)
      {
      LFSR;
      lfsr = (lfsr << 1) | ee->out;
      } /* for each bit in lfsr */
   ee->prev = lfsr;       /* set to random UINT */

   /***************************************************/
   /* After this subroutine, you may initialize the   */
   /* state array, prev, pprev, and lfsr to your own  */ 
   /* values if you wish to do regression testing.    */
   /***************************************************/
   /* return the eegl structure                       */
   /***************************************************/
   return(ee);
   } /* eeglinit subroutine */
