/* eegl.h - random number generator header file Version 2.0.0 */
/* Copyright (C) 2019 aquila57 at github.com */

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
/* This is a 64-bit version of eegl.h.                               */
/* It is based on Version 1.1.0 of eegl.h                            */
/* at http://www.github.com/aquila62/eegl                            */
/*********************************************************************/

/********************************************************/
/* The LFSR in this generator comes from the following  */
/* http://courses.cse.tamu.edu/walker/csce680/          */
/* lfsr_table.pdf                                       */
/* 64 bit LFSR is 64,63,61,60 with low order bit equal  */
/* to 64                                                */
/********************************************************/

/* the following includes are used especially by the    */
/* initialization routine                               */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>

typedef struct eeglstruct {
   int states;               /* number of states */
   int ofst;                 /* offset into state array */
   int out;                  /* current output from the LFSR */
   unsigned int lowbit;      /* high order LFSR low bit */
   unsigned int major;       /* high order LFSR */
   unsigned int minor;       /* low  order LFSR */
   unsigned int lfsr0;       /* high order LFSR */
   unsigned int lfsr;        /* low  order LFSR */
   unsigned int prev;        /* prev LFSR */
   unsigned int pprev;       /* prev prev LFSR */
   unsigned int s1;          /* taus s1        */
   unsigned int s2;          /* taus s2        */
   unsigned int s3;          /* taus s3        */
   unsigned int crctbl[256];      /* crc32 table */
   unsigned int crc;         /* crc32 */
   unsigned int fibo1;       /* fibonacci number 1 */
   unsigned int fibo2;       /* fibonacci number 2 */
   unsigned int fibo3;       /* fibonacci number 3 */
   unsigned int seed;        /* initial seed */
   unsigned int *state;      /* state array */
   } eefmt;

#define LFSROUT (ee->out = (((ee->lfsr >> 4) \
   ^ (ee->lfsr >> 3) \
   ^ (ee->lfsr >> 1) \
   ^ (ee->lfsr >> 0)) & 1))

#define LFSRLOWBIT (ee->lowbit = ee->major & 1)

#define LFSRROLL (ee->major = ee->lfsr0 = \
(ee->major >> 1) | (ee->out << 31))

#define LFSRCARRY (ee->minor = ee->lfsr = \
(ee->minor >> 1) | (ee->lowbit << 31))

#define LFSR (LFSROUT,LFSRLOWBIT,LFSRROLL,LFSRCARRY)

void eeglcrct(eefmt *ee);              /* initialize crc table   */
unsigned int eeglcrc(eefmt *ee, unsigned char *str, int len);
unsigned int eeglsd(eefmt *ee);        /* generate random seed   */
eefmt *eeglinit(void);                 /* initialization routine */
eefmt *eeglstrt(unsigned int seed1, unsigned int seed2,
   unsigned int seed3);    /* regression initialization */
unsigned int eegl(eefmt *ee);          /* random bit generator */
double eeglunif(eefmt *ee);            /* random number 0-1 */
double eeglfrac(eefmt *ee);            /* random fraction 0-1 */
int eeglint(eefmt *ee, int limit);     /* random integer 0-limit */
unsigned int eeglpwr(eefmt *ee, int bits); /* random # 0-32 bits */
int eeglbit(eefmt *ee);                /* random bit */
void eegldspl(eefmt *ee, int option);  /* display eegl state */
void eeglabt(void);                    /* about eegl RNG */
