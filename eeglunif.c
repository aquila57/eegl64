/* eeglunif.c - uniform random number generator 0-1 Version 2.0.0    */
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
/* This is a 64-bit version of eeglunif.c.                           */
/* It is based on Version 1.0.0 of eeglunif.c                        */
/* at http://www.github.com/aquila62/eegl                            */
/*********************************************************************/

/********************************************************/
/* The LFSR in this generator comes from the following  */
/* http://courses.cse.tamu.edu/walker/csce680/          */
/* lfsr_table.pdf                                       */
/********************************************************/

/* This subroutine produces a uniform random number     */
/* from zero to one.                                    */
/* This routine should produce all positive results.    */
/* A test for negative results has been removed, for    */
/* efficiency reasons.  If negative results occur in    */
/* the future, the test for negative results has to     */
/* be added back in to the routine, as follows.         */
/*    if (num < 0.0) num = -num;                        */

#define MAXINT (4294967296.0)

#include "eegl.h"

double eeglunif(eefmt *ee)
   {
   double num;             /* random number from 0 up to 2^32 */
   double frac;            /* random number from 0-1          */
   num  = (double) eegl(ee);
   /* This uniform random number is the ratio between       */
   /* a random UINT and 2^32, such that                     */
   /* 0.0 <= frac < 1.0                                     */
   frac = num / MAXINT;
   return(frac);           /* return uniform random number */
   } /* eeglunif */
