#include<strings.h>
#include<string.h>
#include<stdio.h>
#include<curl/curl.h>
#include<fcntl.h>

#include<sys/stat.h>
#include<sys/types.h>

#include "../libs/graphics.h"

char *nreverse(char *str, int num1, int num2){
        int c;
        for(int i=num1, j=num2;i<j;i++, j--){
                c=str[i];
                str[i]=str[j];
                str[j]=c;
        }
        return str;
}
char *replace(char *string, char c1, char c2){

        char str[200];

        strcat(str, string);

        for(int i=0;i<strlen(str)-1;i++){
                if(str[i]==c1)
                        str[i]=c2;
        }
        sprintf(string,"%s",str);

        return string;
}
int gamecheck(char *filename){
	struct stat stbuf;
	init_pair(10,COLOR_WHITE,COLOR_RED);

	if(stat(filename,&stbuf)!=-1)
		return 0;

	clear();
	paint(32,10);

	mvprintw(MAXY/2,(MAXX-strlen("Cannot Find Executable: ")-strlen(filename))/2,"Cannot Find Executable: %s",filename);
	getch();

	clear();
	refresh();
	return -1;

}
int wisMoveOk(WINDOW *win,int y, int x){
	int t=mvwinch(win,y,x);
	return t=='-' || t=='|' || t=='+' || t=='_' || t=='#' || t=='/' || t=='\\'||t==97|A_ALTCHARSET||t==104|A_ALTCHARSET;
}
CURLcode downloadSource(char *source, char *file){
        CURL *curl=curl_easy_init();
        CURLcode res;

        FILE *fp;
        FILE *chck=fopen(file,"w+");

        if(chck==NULL){
                fclose(chck);
                int fd=creat(file,00666);
                if(fd == -1){
                        return 404;
                }
        }
        fclose(chck);
        fp=fopen(file,"w+");

        if(curl){
                curl_easy_setopt(curl,CURLOPT_URL,source);
                curl_easy_setopt(curl,CURLOPT_WRITEDATA,(void*)fp);

                res=curl_easy_perform(curl);
                return res;
        }
        fclose(fp);
}

