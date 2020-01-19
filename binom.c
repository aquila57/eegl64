/* binom.c - Binomial Distribution Test Version 1.0.0                */
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

/* This program performs a chi square test on a sample */
/* population in a binomial distribution */
/* The program flips a "coin" 17 times and counts the */
/* number of heads in the tuple */
/* The program samples the population 131072 times. */
/* The expected results are based on Pascal's triangle */
/* for 2^17 */
/* To determine heads or tails, the eegl generator is used */

#include <stdio.h>
#include "eegl.h"

#define TRIALS (131072)

int main()
   {
   int i;                  /* loop counter for #samples */
   double chisq;           /* chi square total */
   double *p,*q,*r;        /* pointers to actual and expected */
   double actual[64];      /* actual sample totals */
   double expected[64];    /* expected totals */
   eefmt *ee;              /* eegl structure */
   /*********************************************************/
   /* initialize total arrays                               */
   /*********************************************************/
   p = (double *) actual;
   q = (double *) actual + 64;
   while (p < q) *p++ = 0.0;
   p = (double *) expected;
   q = (double *) expected + 64;
   while (p < q) *p++ = 0.0;
   /*********************************************************/
   /* set the expected totals based on Pascal's triangle    */
   /*********************************************************/
   p = (double *) expected;
   *p++ = 1.0;
   *p++ = 17.0;
   *p++ = 136.0;
   *p++ = 680.0;
   *p++ = 2380.0;
   *p++ = 6188.0;
   *p++ = 12376.0;
   *p++ = 19448.0;
   *p++ = 24310.0;
   *p++ = 24310.0;
   *p++ = 19448.0;
   *p++ = 12376.0;
   *p++ = 6188.0;
   *p++ = 2380.0;
   *p++ = 680.0;
   *p++ = 136.0;
   *p++ = 17.0;
   *p++ = 1.0;
   /*********************************************************/
   /* initialize the eegl generator                         */
   /*********************************************************/
   ee = (eefmt *) eeglinit();
   /*********************************************************/
   /* Count actual number of heads                          */
   /*********************************************************/
   i = TRIALS;         /* loop counter for #trials */
   while (i--)
      {
      int j;           /* loop counter for counting heads    */
      int tothd;       /* total number of heads in one tuple */
      tothd = 0;       /* initialize total number of heads   */
      j = 17;          /* set loop counter                   */
      while (j--)
         {
	 if (eeglbit(ee)) tothd++;     /* tally #heads in tuple  */
	 } /* for each flip */
      p = (double *) actual + tothd;   /* point to correct total */
      *p += 1.0;                   /* tally n # of heads */
      } /* for each m-bit sample */
   /*********************************************************/
   /* Calculate chi square                                  */
   /*********************************************************/
   chisq = 0.0;                /* initialize chi square total */
   p = (double *) actual;      /* point to actual array */
   q = (double *) actual + 18;    /* end of actual array */
   r = (double *) expected;    /* point to expected array */
   while (p < q)               /* for each actual total */
      {
      double diff;             /* difference = actual - expected */
      double diffsq;           /* difference squared */
      diff = *p - *r;          /* difference = actual - expected */
      diffsq = diff * diff;    /* square the difference */
      chisq += (diffsq / *r);     /* add to the chi square total */
      p++;                     /* next actual total */
      r++;                     /* next expected total */
      } /* for each actual total */
   printf("Binomial Distribution Test\n");
   printf("eegl64 generator\n");
   printf("Total trials %d\n", TRIALS);
   printf("Chi square %f\n", chisq);
   printf("Degrees of freedom 17\n");
   printf("95%c of the time, the chi square is "
      "between 7.564186 and 30.191009\n", '%');
   return(0);
   } /* main */
