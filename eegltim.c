/* eegltim.c - time the eegl RNG  Version 1.0.0                      */
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

#include <stdio.h>
#include <gsl/gsl_rng.h>
#include "eegl.h"

#define COUNT (10000000.0)

int main(void)
   {
   int elap;
   unsigned int dttk;
   double count;
   time_t now;
   clock_t clk;
   clock_t start;
   clock_t fin;
   struct tms t;
   eefmt *ee;
   gsl_rng *r;
   ee = (eefmt *) eeglinit();
   /**************************************************/
   count = 0.0;
   start = times(&t);       /* get ticks */
   while (1)
      {
      eegl(ee);
      count += 1.0;
      if (count >= COUNT)
         {
         fin = times(&t);
	 elap = (fin - start); 
	 break;
	 } /* if 100 million cycles */
      } /* for each cycle */
   printf("eegl        count %.0f ticks %d\n",
      count, elap);
   /**************************************************/
   /* time the GSL taus2 RNG                         */
   /**************************************************/
   /* initialize the GSL taus2 RNG                   */
   /* to date, time, #ticks                          */
   /**************************************************/
   r = (gsl_rng *) gsl_rng_alloc(gsl_rng_taus2);
   /* get clock ticks since boot                       */
   clk = times(&t);
   /* get date & time                                  */
   time(&now);
   /* combine date, time, and ticks into a single UINT */
   dttk = (unsigned int) (now ^ clk);
   /* initialize the GSL taus2 random number generator */
   /* to date,time,#ticks                              */
   gsl_rng_set(r, dttk);
   /**************************************************/
   count = 0.0;
   /* get ticks */
   start = times(&t);
   while (1)
      {
      gsl_rng_get(r);
      count += 1.0;
      if (count >= COUNT)
         {
         fin = times(&t);
	 elap = (fin - start); 
	 break;
	 } /* if 100 million cycles */
      } /* for each cycle */
   printf("GSL taus2   count %.0f ticks %d\n",
      count, elap);
   /**************************************************/
   /* time the GSL ranlxd2 RNG                       */
   /**************************************************/
   /* initialize the GSL ranlxd2 RNG                 */
   /* to date, time, #ticks                          */
   /**************************************************/
   gsl_rng_free(r);
   r = (gsl_rng *) gsl_rng_alloc(gsl_rng_ranlxd2);
   /* get clock ticks since boot                         */
   clk = times(&t);
   /* get date & time                                    */
   time(&now);
   /* combine date, time, and ticks into a single UINT   */
   dttk = (unsigned int) (now ^ clk);
   /* initialize the GSL ranlxd2 random number generator */
   /* to date,time,#ticks                                */
   gsl_rng_set(r, dttk);
   /**************************************************/
   count = 0.0;
   /* get ticks */
   start = times(&t);
   while (1)
      {
      gsl_rng_uniform(r);
      count += 1.0;
      if (count >= COUNT)
         {
         fin = times(&t);
	 elap = (fin - start); 
	 break;
	 } /* if 100 million cycles */
      } /* for each cycle */
   printf("GSL ranlxd2 count %.0f ticks %d\n",
      count, elap);
   /**************************************************/
   free(ee->state);
   free(ee);
   return(0);
   } /* main */
