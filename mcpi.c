/* mcpi.c - Monte Carlo Calculation of Pi/4  Version 1.0.0           */
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

/********************************************************/
/* mcpi estimates the value of Pi/4 through a Monte     */
/* Carlo simulation.                                    */
/* Two uniform random numbers are generated 0-1         */
/* one million times                                    */
/* If x^2 + y^2 < 1 then tally a counter                */
/* The ratio of the counter total / one million         */
/* is approximately Pi/4 to 3 decimal places            */
/* or approximately 0.785...                            */
/********************************************************/

#include <stdio.h>
#include <time.h>
#include <sys/times.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include "eegl.h"

int main(void)
   {
   int i;                     /* loop counter                 */
   int eeglelap;              /* elapsed time for eegl        */
   int ranlxelap;             /* elapsed time for ranlxd2     */
   unsigned int dttk;         /* combined date, time #ticks   */
   double tot;                /* total points within a circle */
   double bot;                /* one million                  */
   double ratio;              /* estimated pi/4               */
   time_t now;                /* current date and time        */
   clock_t clk;               /* current number of ticks      */
   clock_t eeglstart;         /* start time for eegl          */
   clock_t eeglfin;           /* end   time for eegl          */
   clock_t ranlxstart;        /* start time for ranlxd2       */
   clock_t ranlxfin;          /* end   time for ranlxd2       */
   struct tms t;              /* structure used by times()    */
   gsl_rng *r;                /* GSL RNG structure            */
   eefmt *ee;                 /* eegl structure               */
   ee = (eefmt *) eeglinit();      /* initialize the eegl structure */
   bot = 1000000.0;           /* set to one million           */
   /************************************************************/
   tot = 0.0;                 /* initialize total points in a circle */
   i = (int) bot;             /* set loop counter */
   /* get clock ticks since boot                           */
   eeglstart = times(&t);     /* start time for eegl       */
   while (i--)                /* loop one million times    */
      {
      double x;               /* horizontal value             */
      double y;               /* vertical   value             */
      double sum;             /* sum = x*x + y*y              */
      x = eeglunif(ee);       /* uniform number 0-1           */
      y = eeglunif(ee);       /* uniform number 0-1           */
      sum = (x*x) + (y*y);    /* calculate the vector length  */
      if (sum < 1.0) tot += 1.0;   /* if within a unit circle, tally */
      } /* for each point inside or outside a circle */
   ratio = tot / bot;         /* calculate est. pi/4   */
   eeglfin = times(&t);       /* finish time for eegl  */
   printf("Monte Carlo Calculation of Pi/4\n");
   printf("       eegl Pi/4 %18.15f\n", ratio);
   /************************************************************/
   /* allocate the ranlxd2 random number generator */
   r = (gsl_rng *) gsl_rng_alloc(gsl_rng_ranlxd2);
   /* get clock ticks since boot                           */
   clk = times(&t);
   /* get date & time                                      */
   time(&now);
   /* combine date, time, and ticks into a single UINT     */
   dttk = (unsigned int) (now ^ clk);
   /* initialize the GSL ranlxd2 random number generator      */
   /* to date,time,#ticks                                     */
   gsl_rng_set(r, dttk);      /* initialize ranlxd2 seed      */
   tot = 0.0;                 /* initialize total points in a circle */
   i = (int) bot;             /* set loop counter */
   /* get clock ticks since boot                              */
   ranlxstart = times(&t);    /* start time for GSL ranlxd2   */
   while (i--)                /* loop one million times       */
      {
      double x;               /* horizontal value             */
      double y;               /* vertical   value             */
      double sum;             /* sum = x*x + y*y              */
      /* use the ranlxd2 random number generator this time    */
      x = gsl_rng_uniform(r);      /* uniform number 0-1      */
      y = gsl_rng_uniform(r);      /* uniform number 0-1      */
      sum = (x*x) + (y*y);    /* calculate the vector length  */
      if (sum < 1.0) tot += 1.0;   /* if within a unit circle, tally */
      } /* for each point inside or outside a circle */
   ratio = tot / bot;         /* calculate est. pi/4           */
   ranlxfin = times(&t);      /* finish time for GSL ranlxd2   */
   printf("GSL ranlxd2 Pi/4 %18.15f\n", ratio);
   printf("     Actual Pi/4 %18.15f\n", M_PI * 0.25);
   eeglelap  = eeglfin  - eeglstart;
   ranlxelap = ranlxfin - ranlxstart;
   printf("       eegl ticks %6d\n", eeglelap);
   printf("GSL ranlxd2 ticks %6d\n", ranlxelap);
   return(0);
   } /* main */
