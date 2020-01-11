/* eeglsd.c - Generate random seed  Version 0.1.0                    */
/* Copyright (C) 2020 aquila57 at github.com                         */

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

/* Generate a random unsigned integer to be used in        */
/* initializing the eegl state.                            */

#include "eegl.h"

/* multiplier for RANDU */

#define EMM (65539)

#define LEN (128)

unsigned int eeglsd(eefmt *ee)
   {
   int ch;
   unsigned int rslt;
   unsigned char *p,*q;
   unsigned char str[256];
   p = (unsigned char *) str;
   q = (unsigned char *) str + LEN;
   while (p < q)
      {
      ee->seed *= EMM;
      ee->fibo1 = ee->fibo2;
      ee->fibo2 = ee->fibo3;
      ee->fibo3 = ee->fibo1 + ee->fibo2;
      ch = (ee->seed >> 24) ^ (ee->fibo3 >> 24);
      *p++ = ch;
      } /* for each unsigned char in str */
   rslt = eeglcrc(ee, str, LEN);
   return(rslt);
   } /* eeglsd */
