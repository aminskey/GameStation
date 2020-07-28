#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include<ncurses.h>
#include<strings.h>
#include<string.h>

int __ch;
int __y;
int __x;

short __col;

const chtype __ch1;
const chtype __ch2;

WINDOW *__win;
MEVENT __evnt;

extern char home[];

extern void wpaint();
extern void wredrawbg();
extern void woutline();

extern int touch();
extern int chprint();

#define paint(__ch, __col) wpaint(stdscr,__ch,__col)
#define mtouchwin(__win, __evnt) touch(getbegy(__win),getbegx(__win),getmaxy(__win),getmaxx(__win),__evnt)
#define redraw(__col); wredrawbg(stdscr,__col);
#define istouching(__y,__x) wistouching(stdscr,__y,__x)
#define outline(__col,__ch1,__ch2) woutline(stdscr,__col,__ch1,__ch2)

#define MAXY getmaxy(stdscr)
#define MAXX getmaxx(stdscr)

#endif
