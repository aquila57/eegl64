/* eegl.c - random number generator Version 2.0.0                    */
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
/* This is a 64-bit version of eegl.c.                               */
/* It is based on Version 1.1.0 of eegl.c                            */
/* at http://www.github.com/aquila62/eegl                            */
/*********************************************************************/

/********************************************************/
/* The LFSR in this generator comes from the following  */
/* http://courses.cse.tamu.edu/walker/csce680/          */
/* lfsr_table.pdf                                       */
/********************************************************/

/********************************************************/
/* The result of the Bays-Durham shuffle is that the    */
/* period length of eegl is somewhat less than          */
/* 61036 digits, or the factorial of 16384.             */
/* This is a theoretical period length that is too      */
/* long to be tested in practice.                       */
/********************************************************/

#include "eegl.h"

#define MAXINT (4294967296.0)

unsigned int eegl(eefmt *ee)
   {
   unsigned int tmp;       /* used by Bays-Durham shuffle  */
   unsigned int *stp;      /* state array pointer          */
   /********************************************************/
   /* this LFSR is 64 bits                                 */
   /* this is 64 63 61 60 counting from the left at one    */
   /* or 4 3 1 0 counting from the left at zero            */
   /* in the reverse direction,                            */
   /* the bits are counted from the right at zero          */
   /* 4 3 1 0                                              */
   /* the period length is 10^18, or 2^64-1, cycles        */
   /* for this 64-bit double LFSR register                 */
   /* It uses a random 32 bit number (non-zero) for a seed */
   /* When combined with 16384 states, the period length   */
   /* is approximately 1.2e61036 cycles.                   */
   /********************************************************/
   /* select one out of 16384 states                       */
   /* calculate offset using the top 14 bits               */
   /********************************************************/
   ee->ofst = (ee->pprev >> 18);
   /********************************************************/
   /* back up the previous two results                     */
   /********************************************************/
   ee->pprev = ee->prev;   /* prev prev <== prev           */
   ee->prev  = ee->lfsr;   /* prev <== lfsr                */
   /********************************************************/
   /* calculate one lfsr cycle                             */
   /********************************************************/
   LFSR;
   /********************************************************/
   /* point to the state selected                          */
   /********************************************************/
   stp = (unsigned int *) ee->state + ee->ofst;
   /********************************************************/
   /* Bays-Durham shuffle                                  */
   /* Swap current LFSR with random entry into the         */
   /* state array.                                         */
   /********************************************************/
   tmp  = (unsigned int) *stp;
   *stp = (unsigned int) ee->lfsr;
   ee->lfsr = tmp;
   /********************************************************/
   /* return the output of the Bays-Durham shuffle         */
   /********************************************************/
   return(ee->lfsr ^ ee->prev ^ ee->pprev);
   } /* eegl subroutine */
