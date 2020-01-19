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

/***********************************************************/
/* This initialization routine is based on date/time/ticks */
/* RNG is an acronym for random number generator           */
/* To do regression testing, use                           */
/* eeglstrt(seed1,seed2,seed3)                             */
/* instead of this initialization routine.                 */ 
/***********************************************************/

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

#define TAUS (TAUSONE ^ TAUSTWO ^ TAUSTRE)

#define STATES (16384)

#define EMM (65539)

void eeglcrct(eefmt *ee);

eefmt *eeglinit(void)
   {
   int i;
   unsigned int dttk;          /* combined date and #ticks */
   unsigned int *stp,*stq;     /* pointers into state array */
   unsigned char str[16];      /* string to crc */
   time_t now;                 /* current date and time */
   clock_t clk;                /* current number of ticks */
   struct tms t;               /* structure used by times() */
   eefmt *ee;                  /* eegl structure */

   /***************************************************/
   /* allocate memory for eegl structure              */
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
   eeglcrct(ee);      /* initialize crc table */
   /* get clock ticks since boot                       */
   clk = times(&t);
   /* get date & time                                  */
   time(&now);
   /* combine date, time, and ticks into a single UINT */
   dttk = (unsigned int) (now ^ clk);
   /* initialize the first seed to date,time,#ticks    */
   ee->seed = dttk | 1;   /* initial seed = curr date & time */
   /***************************************************/
   /* Create an 8 byte random string to use for       */
   /* calculating a random crc32.                     */
   /* Assign the crc32 to s1                          */
   /***************************************************/
   ee->seed *= EMM;    /* warm up the seed */
   ee->seed *= EMM;    /* warm up the seed */
   ee->seed *= EMM;    /* warm up the seed */
   ee->seed *= EMM;    /* warm up the seed */
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
   ee->s1 = eeglcrc(ee,str,8);
   /***************************************************/
   /* Create an 8 byte random string to use for       */
   /* calculating a random crc32.                     */
   /* Assign the crc32 to s2                          */
   /***************************************************/
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
   ee->s2 = eeglcrc(ee,str,8);
   /***************************************************/
   /* Create an 8 byte random string to use for       */
   /* calculating a random crc32.                     */
   /* Assign the crc32 to s3                          */
   /***************************************************/
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
   ee->s3 = eeglcrc(ee,str,8);
   /*****************************************************/
   /* we are now ready to assign the entire eegl state  */
   /*****************************************************/
   ee->major = ee->lfsr0 = TAUS;     /* set to random UINT */
   ee->minor = ee->lfsr  = TAUS;     /* set to random UINT */

   /***************************************************/
   /* initialize the state array to random values     */
   /***************************************************/
   stp = (unsigned int *) ee->state;
   stq = (unsigned int *) ee->state + ee->states;
   while (stp < stq)
      {
      *stp++ = TAUS;         /* set to random UINT */
      } /* for each element in ee->state */

   /***************************************************/
   /* initialize pprev to random values               */
   /* this field is backed up in eegl()               */
   /***************************************************/
   ee->pprev = TAUS;         /* set to random UINT */

   /***************************************************/
   /* initialize prev to random values                */
   /* this field is backed up in eegl()               */
   /***************************************************/
   ee->prev = TAUS;         /* set to random UINT */

   /***************************************************/
   /* Warm up the generator                           */
   /***************************************************/
   i = 128;
   while (i--) eegl(ee);

   /***************************************************/
   /* To do regression testing, use eeglstrt(seed)    */
   /* instead of this initialization routine.         */ 
   /***************************************************/
   /* return the eegl structure                       */
   /***************************************************/
   return(ee);
   } /* eeglinit subroutine */

