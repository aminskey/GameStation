#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include<ncurses.h>
#include<strings.h>
#include<string.h>

int __ch;
short __col;

WINDOW *__win;
MEVENT __evnt;

extern char home[];

extern void wpaint();
extern int touch();
extern int chprint();

#define paint(__ch, __col) wpaint(__win,__ch,__col)
#define mtouchwin(__win, __evnt) touch(getbegy(__win),getbegx(__win),getmaxy(__win),getmaxx(__win),__evnt)

#define MAXY getmaxy(stdscr)
#define MAXX getmaxx(stdscr)

#endif
