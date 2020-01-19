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

#define TAUSONE (ee->s1 = (((ee->s1&0xfffffffe)<<12) \
      ^(((ee->s1<<13)^ee->s1)>>19)))

#define TAUSTWO (ee->s2 = (((ee->s2&0xfffffff8)<< 4) \
      ^(((ee->s2<< 2)^ee->s2)>>25)))

#define TAUSTRE (ee->s3 = (((ee->s3&0xfffffff0)<<17) \
      ^(((ee->s3<< 3)^ee->s3)>>11)))

#define TAUS (TAUSONE ^ TAUSTWO ^ TAUSTRE)

/* multiplier for RANDU */

#define EMM (65539)

#define LEN (128)

unsigned int eeglsd(eefmt *ee)
   {
   unsigned int ch;
   unsigned int rslt;
   unsigned char *p,*q;
   unsigned char str[256];
   p = (unsigned char *) str;
   q = (unsigned char *) str + LEN;
   while (p < q)
      {
      ch = TAUS;
      *p++ = (ch >> 24);
      } /* for each unsigned char in str */
   rslt = eeglcrc(ee, str, LEN);
   return(rslt);
   } /* eeglsd */
