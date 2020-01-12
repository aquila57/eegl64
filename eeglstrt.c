/* eeglstrt.c - eegl RNG initialization Version 2.0.0                */
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

/* This initialization routine is based on an input parameter */
/* Use this routine instead of eeglinit() for compiling */
/* on Windows using the mingw compiler */
/* This initialization routine may be used for regression testing */
/* RNG is an acronym for random number generator */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>
#include "eegl.h"

#define STATES (16384)

#define EMM (65539)

void eeglcrct(eefmt *ee);

eefmt *eeglstrt(unsigned int seed)
   {
   int i;
   unsigned char str[16];      /* string to crc */
   unsigned int *stp,*stq;     /* pointers into state array */
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
   /* initialize the first LFSR to input parameter    */
   /***************************************************/
   eeglcrct(ee);      /* initialize crc table */
   ee->seed = seed | 1;   /* initial seed = parm */
   i = 256;    /* warm up ee->seed 256 times */
   while (i--) ee->seed *= EMM;    /* warm up ee->seed */
   str[0] = (ee->seed >> 24) & 255;
   ee->seed *= EMM;
   str[1] = (ee->seed >> 24) & 255;
   ee->seed *= EMM;
   str[2] = (ee->seed >> 24) & 255;
   ee->seed *= EMM;
   str[3] = (ee->seed >> 24) & 255;
   ee->seed *= EMM;
   str[4] = (ee->seed >> 24) & 255;
   ee->seed *= EMM;
   str[5] = (ee->seed >> 24) & 255;
   ee->seed *= EMM;
   str[6] = (ee->seed >> 24) & 255;
   ee->seed *= EMM;
   str[7] = (ee->seed >> 24) & 255;
   ee->fibo1 = eeglcrc(ee,str,8);
   ee->seed *= EMM;
   str[0] = (ee->seed >> 24) & 255;
   ee->seed *= EMM;
   str[1] = (ee->seed >> 24) & 255;
   ee->seed *= EMM;
   str[2] = (ee->seed >> 24) & 255;
   ee->seed *= EMM;
   str[3] = (ee->seed >> 24) & 255;
   ee->seed *= EMM;
   str[4] = (ee->seed >> 24) & 255;
   ee->seed *= EMM;
   str[5] = (ee->seed >> 24) & 255;
   ee->seed *= EMM;
   str[6] = (ee->seed >> 24) & 255;
   ee->seed *= EMM;
   str[7] = (ee->seed >> 24) & 255;
   ee->fibo2 = eeglcrc(ee,str,8);
   ee->fibo3 = ee->fibo1 + ee->fibo2;
   ee->major = ee->lfsr0 = eeglsd(ee);
   ee->minor = ee->lfsr  = eeglsd(ee);

   /***************************************************/
   /* initialize the state array to random values     */
   /***************************************************/
   stp = (unsigned int *) ee->state;
   stq = (unsigned int *) ee->state + ee->states;
   while (stp < stq)
      {
      *stp++ = eeglsd(ee);      /* set to random UINT */
      } /* for each element in ee->state */

   /***************************************************/
   /* initialize pprev to random values               */
   /* this field is backed up in eegl()               */
   /***************************************************/
   ee->pprev = eeglsd(ee);      /* set to random UINT */

   /***************************************************/
   /* initialize prev to random values                */
   /* this field is backed up in eegl()               */
   /***************************************************/
   ee->prev = eeglsd(ee);       /* set to random UINT */

   /***************************************************/
   /* Warm up the generator                           */
   /***************************************************/
   i = 128;
   while (i--) eegl(ee);

   /***************************************************/
   /* To do regression testing, use eeglstrt(seed)    */
   /* instead of this routine.                        */ 
   /***************************************************/
   /* return the eegl structure                       */
   /***************************************************/
   return(ee);
   } /* eeglstrt subroutine */
