/* eeglint.c - generate a random number integer Version 2.0.0        */
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
/* This is a 64-bit version of eeglint.c.                            */
/* It is based on Version 1.0.0 of eeglint.c                         */
/* at http://www.github.com/aquila62/eegl                            */
/*********************************************************************/

/********************************************************/
/* The LFSR in this generator comes from the following  */
/* http://courses.cse.tamu.edu/walker/csce680/          */
/* lfsr_table.pdf                                       */
/********************************************************/

/* this subroutine generates a random integer from zero */
/* up to, but not including, a limit                    */
/* the limit may be positive or negative                */
/* For performance reasons, the input parameter is not  */
/* validated                                            */
/* See eeglpwr.c for generating an unsigned integer     */

#include "eegl.h"

int eeglint(eefmt *ee, int limit)
   {
   unsigned int intgr;               /* output integer */
   /* calculate the remainder of a random UINT         */
   /* divided by the limit.                            */
   intgr = (unsigned int) eegl(ee) % limit;
   return(intgr);           /* return the integer */
   } /* eeglint */
