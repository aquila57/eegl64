/* tmplt.c - Template Test Program  Version 0.1.0 */
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

/* This program uses the GNU Scientific Library to calculate         */
/* P-value and chi square range.                                     */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gsl/gsl_cdf.h>
#include "eegl.h"

#define SMPLS (10000000)

/* template size is large enough, so that it should never */
/* be completely matched.                                 */
/* To completely match the template, conduct a separate   */
/* test where the data is repeated after 10000 samples.   */
/* This will force a wrap-around error.                   */
/* To force a chi square failure, use a poor generator,   */
/* like a fibonacci generator.                            */

#define TMPLTSZ 1024

/* BITS is the number of bits in each token in the template */
/* A 3 bit numbers is 0-7 */

#define BITS 3

/* queue structure */
/* The template is stored as a FIFO queue. */
/* The samples are stored in a separate FIFO queue */
/* to match against the template queue. */

typedef struct qstruct {
   struct qstruct *next;
   struct qstruct *prev;
   unsigned int num;
   } qfmt;

/* This is a re-entrant program.  All data is stored */
/* in a dynamic structure on the heap. */

typedef struct xxstruct {
   qfmt *tmplthead;         /* head of the template queue */
   qfmt *tmplttail;         /* tail of the template queue */
   qfmt *lsthead;           /* head of the sample   queue */
   qfmt *lsttail;           /* tail of the sample   queue */
   eefmt *ee;        /* random number generator structure */
   /* array of actual sample tallies */
   /* The index to the array is the number of times that  */
   /* sample tokens are matched against the template.     */
   double actual[TMPLTSZ];
   double chisq;            /* chi square result */
   double pvalue;           /* P-value of chi square test */
   } xxfmt;

/* Initialize a new element in a FIFO queue */

qfmt *qinit(void)
   {
   qfmt *newnode;
   newnode = (qfmt *) malloc(sizeof(qfmt));
   if (newnode == NULL)
      {
      fprintf(stderr,"qinit: out of memory "
         "allocating newnode\n");
      exit(1);
      } /* out of memory */
   newnode->next = NULL;
   newnode->prev = NULL;
   newnode->num  = 0;
   return(newnode);
   } /* qinit */

/* FIFO queue push */
void pushq(qfmt *head, unsigned int num)
   {
   qfmt *newnode;
   newnode = qinit();
   newnode->next = head;
   newnode->prev = head->prev;
   newnode->num = num;
   head->prev = newnode;
   newnode->prev->next = newnode;
   } /* pushq */

/* FIFO queue pop */
void popq(qfmt *tail)
   {
   qfmt *tmp;
   tmp = tail->next;
   tail->next = tmp->next;
   tmp->next->prev = tail;
   free(tmp);
   } /* popq */

/* debugging routine to display the template queue */
void shwqueue(xxfmt *xx)
   {
   int i;
   qfmt *currnode;
   printf("t ");
   i = 0;
   currnode = xx->tmplttail->next;
   while (currnode != xx->tmplthead)
      {
      printf("%08x ", currnode->num);
      currnode = currnode->next;
      i++;
      if (i > 5) break;
      } /* for each element in template FIFO queue */
   printf("\n");
   } /* shwqueue */

/* debugging routine to display the actual sample queue */
void shwlist(xxfmt *xx)
   {
   int i;
   qfmt *currnode;
   printf("a ");
   i = 0;
   currnode = xx->lsttail->next;
   while (currnode != xx->lsthead)
      {
      printf("%08x ", currnode->num);
      currnode = currnode->next;
      i++;
      if (i > 5) break;
      } /* for each element in actual list (FIFO queue) */
   printf("\n");
   } /* shwlist */

/* debugging routine to display the actual tally array */
void shwactual(xxfmt *xx)
   {
   int i;
   int indx;
   indx = 0;
   i = TMPLTSZ;
   while (i--)
      {
      if (xx->actual[indx] > 0.0)
         printf("indx %5d tally %.0f\n",
	    indx, xx->actual[indx]);
      indx++;
      } /* for each tally in actual > 10 */
   } /* shwactual */

/* build a random template queue */
/* if BITS is equal to 3, each token is a binary */
/* number from zero to 7 */
void bldtmplt(xxfmt *xx)
   {
   int i;
   i = TMPLTSZ;
   while (i--)
      {
      unsigned int x;
      x = eeglpwr(xx->ee,BITS);
      pushq(xx->tmplthead, x);
      } /* for each element in template FIFO queue */
   } /* bldtmplt */

/* Create the initial sample queue the same size as */
/* the template */
/* the tokens in this sample queue should not match */
/* the template queue.  */
void bldlst(xxfmt *xx)
   {
   int i;
   i = TMPLTSZ;
   while (i--)
      {
      unsigned int x;
      x = eeglpwr(xx->ee,BITS);
      pushq(xx->lsthead, x);
      } /* for each element in active list FIFO queue */
   } /* bldlst */

/* Starting with the tail of each queue, */
/* compare the sample queue against the template queue */
/* The number of token matches is the index into the */
/* actual tally array. */
/* If the number of token matches is equal to TMPLTSZ */
/* a wrap-around error occurs, and the template test */
/* fails. */

void tally(xxfmt *xx)
   {
   int indx;
   qfmt *tmplt;
   qfmt *lst;
   indx = 0;
   tmplt = xx->tmplttail->next;
   lst   = xx->lsttail->next;
   while (tmplt != xx->tmplthead)
      {
      if (tmplt->num == lst->num)
         {
	 indx++;
         tmplt = tmplt->next;
	 lst   = lst->next;
	 } /* if match node */
      else break;
      } /* for each node in the template */
   xx->actual[indx] += 1.0;
   if (tmplt == xx->tmplthead)
      {
      fprintf(stderr,"tally: wrap around\n");
      exit(1);
      } /* wrap around */
   } /* tally */

/* update the sample FIFO queue with a new sample */
/* compare the sample queue to the template queue */
/* to see if a wrap-around error has occurred */
/* update the tally array based on the number of */
/* sample tokens that match the template */

void sample(xxfmt *xx)
   {
   unsigned int newnum;
   popq(xx->lsttail);
   newnum = eeglpwr(xx->ee,BITS);
   pushq(xx->lsthead, newnum);
   tally(xx);
   } /* sample */

/* run a chi square test on the tally array */
void calcchi(xxfmt *xx)
   {
   int indx;
   double prob;        /* probability of each tally */
   double expected;    /* expected number of tallies */
   double diff;        /* actual minus expected */
   double diffsq;      /* tally difference squared */
   double max;         /* 2^BITS                   */
   double totsmpls;    /* total number of samples */
   double df;          /* degrees of freedom */
   double minchi;      /* minimum chi square at 95% */
   double maxchi;      /* maximum chi square at 95% */
   max = (double) (1 << BITS);
   totsmpls = (double) SMPLS;
   xx->chisq = 0.0;    /* initialize chi square */
   /* probability of no match */
   prob = 1.0 - (1.0 / max);
   indx = 0;
   /* for each tally in the tally array greater than 10 */
   while (xx->actual[indx] > 10)
      {
      /* expected number of tallies */
      expected = prob * totsmpls;
      /* difference between actual and expected tallies */
      diff = xx->actual[indx] - expected;
      diffsq = diff * diff;     /* difference squared */
      /* add to the chi square */
      xx->chisq += (diffsq / expected);
      /* running display of the actual and expected */
      printf("%5d act %15.5f exp %15.5f diff %12.5f\n",
         indx, xx->actual[indx], expected, diff);
      /* calculate the probability and expected values */
      /* for the next tally in the tally array */
      prob /= max;
      expected = prob * totsmpls;
      indx++;
      } /* for each level of actual tally */
   /* calculate degrees of freedom */
   df = (double) (indx - 1);
   /* at 95% probability calculate minimum chi square */
   minchi = gsl_cdf_chisq_Pinv(0.025,df);
   /* at 95% probability calculate maximum chi square */
   maxchi = gsl_cdf_chisq_Pinv(0.975,df);
   /* find the P-value for the calculated */
   /* chi square and degrees of freedom */
   xx->pvalue = gsl_cdf_chisq_P(xx->chisq,df);
   printf("Chi square %f  P-value %18.15f\n", xx->chisq, xx->pvalue);
   printf("At 95%c probability and %.0f degrees of freedom,\n"
      "Chi square ranges from %f to %f\n",
      '%', df, minchi, maxchi);
   } /* calcchi */

int main(void)
   {
   int i;
   /* this is a re-entrant program */
   /* allocate the global storage structure */
   /* from the heap */
   xxfmt *xx;
   xx = (xxfmt *) malloc(sizeof(xxfmt));
   if (xx == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating xx\n");
      exit(1);
      } /* out of memory */
   /* initialize the random number generator */
   /* from the date, time, and number of ticks */
   xx->ee = (eefmt *) eeglinit();
   /**************************************************/
   /* initialize the template and sample FIFO queues */
   /**************************************************/
   xx->tmplthead = (qfmt *) qinit();
   xx->tmplttail = (qfmt *) qinit();
   xx->lsthead   = (qfmt *) qinit();
   xx->lsttail   = (qfmt *) qinit();
   xx->tmplttail->next = xx->tmplthead;
   xx->tmplthead->prev = xx->tmplttail;
   xx->lsttail->next   = xx->lsthead;
   xx->lsthead->prev   = xx->lsttail;
   /**************************************************/
   /* create the random template                     */
   /**************************************************/
   bldtmplt(xx);
   /**************************************************/
   /* create the sample queue the same size as       */
   /* the template queue.                            */
   /**************************************************/
   bldlst(xx);
   /**************************************************/
   /* run (SMPLS) random samples                     */
   /* tally #matched tokens to the template          */
   /**************************************************/
   i = SMPLS;
   while(i--)
      {
      sample(xx);   /* process a sample */
      } /* for each sample */
   /**************************************************/
   /* calculate the chi square test                  */
   /**************************************************/
   calcchi(xx);
   /**************************************************/
   /* end of job.  free all allocated memory         */
   /**************************************************/
   free(xx->ee->state);
   free(xx->ee);
   while (xx->tmplttail->next !=  xx->tmplthead)
      popq(xx->tmplttail);
   while (xx->lsttail->next !=  xx->lsthead)
      popq(xx->lsttail);
   free(xx);
   return(0);
   } /* main */
