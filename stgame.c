#include<ncurses.h>
#include<stdio.h>
#include<strings.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<curl/curl.h>

#include "libs/graphics.h"
#include "libs/gamelib.h"

int main(void){

	char game[100];
	char exe[100];
	char exec[100];
	char bg[100];
	char comp[500];

	char arg1[200];
	char arg2[200];


	sprintf(bg,"%s/bgtext.txt",gameDir);

	initscr();
	cbreak();
	noecho();

	curs_set(0);

	start_color();
	init_pair(1,COLOR_WHITE,COLOR_BLUE);
	init_pair(2,COLOR_BLACK,COLOR_WHITE);
	init_pair(3,COLOR_WHITE,COLOR_BLACK);


	WINDOW *chfile=newwin(MAXY/2,MAXX/2,MAXY/2-MAXY/5,MAXX/2-MAXX/5);
	WINDOW *shdw=newwin(getmaxy(chfile),getmaxx(chfile),getbegy(chfile)+1,getbegx(chfile)+2);

	paint(32,1);
	refresh();

	sleep(1);
	paint(97|A_ALTCHARSET,1);
	refresh();

	sleep(1);
	paint(110|A_ALTCHARSET,1);

	refresh();

	sleep(2);

	clear();
	paint(32,1);

	attron(COLOR_PAIR(1));
	chprint(stdscr,bg);
	attroff(COLOR_PAIR(1));
	refresh();

	redraw(1);
	refresh();

	wredrawbg(shdw,3);

	int ret;

re_enter:
	while(1){

		clear();

		paint(32,1);
		chprint(stdscr,bg);
		redraw(1);
		refresh();


		wredrawbg(shdw,3);
		wrefresh(shdw);

		wpaint(chfile,32,2);
		wrefresh(chfile);

		wattron(chfile,COLOR_PAIR(2));

		echo();
		curs_set(1);
		sprintf(exe," ");
		sprintf(arg1," ");
		sprintf(arg2," ");


		mvwprintw(chfile,5,10,"Enter Game Executable: %s",exe);
		for(int i=0;i<50;i++){
			mvwaddch(chfile,6,10+i+strlen("Enter Game Executable: "),111|A_ALTCHARSET);
		}
		mvwscanw(chfile,5,10+strlen("Enter Game Executable: "),"%s%s%s",exe,arg1,arg2);

		sprintf(game,"%s/%s",gameDir,exe);
		sprintf(exec,"%s.c",game);
		sprintf(comp,"gcc %s %s/libfuncs/*.c -lncurses -lpthread -lcurl -I%s/libs -o %s",exec,gameDev,gameDev,game);

		wattroff(chfile,COLOR_PAIR(2));
		curs_set(0);
		noecho();

		if(!strcmp(exe,"Finish_search"))
			break;
		if(!strcmp(exe,"Download_source")){
			sprintf(game,"%s/%s",gameDir,arg2);
			CURLcode res=downloadSource(arg1,game);
			if(res==CURLE_OK){
				mvwprintw(chfile,20,20,"Download succesful");
				sprintf(exec,"%s",game);
			}else{
				mvwprintw(chfile,20,20,"Download unsuccesful :(");
				sprintf(game," ");
				sprintf(exec," ");

				wrefresh(chfile);
				getch();

				goto re_enter;
			}
			wrefresh(chfile);
			getch();
		}

		ret=gamecheck(exec);
		if(ret!=-1){
			mvwprintw(chfile,20,20,"compiling.....");
			wrefresh(chfile);
			system(comp);
			mvwprintw(chfile,20,20,"done compiling");
			wrefresh(chfile);
			getch();
			system(game);
			remove(game);
		}
	}

	endwin();
	return 0;

}
