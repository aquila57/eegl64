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

#define TAUSONE (ee->s1 = (((ee->s1&0xfffffffe)<<12) \
      ^(((ee->s1<<13)^ee->s1)>>19)))

#define TAUSTWO (ee->s2 = (((ee->s2&0xfffffff8)<< 4) \
      ^(((ee->s2<< 2)^ee->s2)>>25)))

#define TAUSTRE (ee->s3 = (((ee->s3&0xfffffff0)<<17) \
      ^(((ee->s3<< 3)^ee->s3)>>11)))

#define TAUS (ee->seed = TAUSONE ^ TAUSTWO ^ TAUSTRE)

#define STATES (16384)

#define EMM (65539)

void eeglcrct(eefmt *ee);

eefmt *eeglstrt(unsigned int seed1, unsigned int seed2,
   unsigned int seed3)
   {
   int i;
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
   if (seed1 < 1 || seed1 > 4000000000)
      {
      fprintf(stderr,"eeglstrt: seed1 %u "
         "is invalid\n", seed1);
      exit(1);
      } /* invalid seed 1 */
   if (seed2 < 1 || seed2 > 4000000000)
      {
      fprintf(stderr,"eeglstrt: seed2 %u "
         "is invalid\n", seed2);
      exit(1);
      } /* invalid seed 2 */
   if (seed3 < 1 || seed3 > 4000000000)
      {
      fprintf(stderr,"eeglstrt: seed3 %u "
         "is invalid\n", seed3);
      exit(1);
      } /* invalid seed 3 */
   ee->s1 = seed1;    /* initial s1 = parm 1 */
   ee->s2 = seed2;    /* initial s2 = parm 2 */
   ee->s3 = seed3;    /* initial s3 = parm 3 */
   i = 128;    /* warm up taus seeds 128 times */
   while (i--) TAUS;    /* warm up ee->seed */
   ee->major = ee->lfsr0 = TAUS;      /* set to random UINT */
   ee->minor = ee->lfsr  = TAUS;      /* set to random UINT */

   /***************************************************/
   /* initialize the state array to random values     */
   /***************************************************/
   stp = (unsigned int *) ee->state;
   stq = (unsigned int *) ee->state + ee->states;
   while (stp < stq)
      {
      *stp++ = TAUS;      /* set to random UINT */
      } /* for each element in ee->state */

   /***************************************************/
   /* initialize pprev to random values               */
   /* this field is backed up in eegl()               */
   /***************************************************/
   ee->pprev = TAUS;      /* set to random UINT */

   /***************************************************/
   /* initialize prev to random values                */
   /* this field is backed up in eegl()               */
   /***************************************************/
   ee->prev = TAUS;      /* set to random UINT */

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
