/* mchain.c - Markov Chain Example       Version 1.0.0               */
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

/* press 'q' to exit */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>
#include "eegl.h"

/* initialize new curses */
void initcrss()
   {
   initscr();
   cbreak();
   noecho();
   nonl();
   intrflush(stdscr,FALSE);
   nodelay(stdscr,TRUE);
   } /* initcrss */

int main()
   {
   int ch;                     /* keyboard character */
   int currnode;               /* current node in chain a=0 b=1 */
   char a[2];                  /* string for node a */
   char b[2];                  /* string for node b */
   eefmt *ee;                  /* eegl structure */
   ee = (eefmt *) eeglinit();  /* initialize the eegl structure */

   /********************************************************/
   /* start curses mode                                    */
   /********************************************************/

   initcrss();                 /* initialize curses mode */

   /********************************************************/
   /* initialize display format                            */
   /********************************************************/

   move(8,30);
   addstr("Markov Chain using eegl");
   move(23,30);
   addstr("Press 'q' to quit");

   /********************************************************/
   /* first cycle is fixed (not random)                    */
   /********************************************************/

   strcpy(a,"A");
   strcpy(b,"_");
   move(11,38);
   addstr(a);
   move(11,42);
   addstr(b);
   move(0,0);
   refresh();
   sleep(1);
   currnode = 0;           /* a=0 b=1 */

   /********************************************************/
   /* main generator loop                                  */
   /********************************************************/
   while (1)         /* infinite loop */
      {
      int i;
      i = eeglbit(ee);     /* each event is 50% probability */
      if (i == 0 && currnode == 1)
         {
	 strcpy(a,"A");
	 strcpy(b,"_");
	 currnode = 0;
	 } /* if change from node B to A */
      else if (i == 0 && currnode == 0)
         {
	 a[0]++;     /* next letter in alphabet */
	 if (a[0] > 'Z') a[0] = 'a';
	 } /* if stay at node A */
      else if (i == 1 && currnode == 0)
         {
	 strcpy(a,"_");
	 strcpy(b,"A");
	 currnode = 1;
	 } /* if change from node A to B */
      else if (i == 1 && currnode == 1)
         {
	 b[0]++;     /* next letter in alphabet */
	 if (b[0] > 'Z') b[0] = 'a';
	 } /* if stay at node B */
      move(11,38);
      addstr(a);
      move(11,42);
      addstr(b);
      move(0,0);
      refresh();
      ch = getch();
      if (ch == 'q') break;
      sleep(1);
      } /* for each cycle */
   endwin();           /* de-activate curses mode */
   free(ee->state);
   free(ee);
   return(0);
   } /* main */
