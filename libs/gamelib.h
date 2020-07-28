#ifndef __GAMELIB_H__
#define __GAMELIB_H__

#include<strings.h>
#include<string.h>
#include<stdio.h>
#include<curl/curl.h>

int y;
int x;

char __str[200];
char home[]="/home/amin";
char gameDir[]="/home/amin/games";
char gameDev[]="/home/amin/cworkspace/gameStation";
char website[]="https://github.com/aminskey/cworkspace/";
char *file;

extern char *nreverse();
extern char *replace();

extern int gamecheck();
extern int wisMoveOk();

extern CURLcode downloadSource();

#define reverse(__str) nreverse(__str,0,strlen(__str)-1)
#define isMoveOk(y,x) wisMoveOk(stdscr,y,x)
#define download(file) downloadSource(website, file)

#endif
