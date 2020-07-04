#ifndef __STDIOF_H__
#define __STDIOF_H__

#include<strings.h>
#include<string.h>

char __str[200];

extern char *nreverse();
extern char *replace();

#define reverse(__str) nreverse(__str,0,strlen(__str)-1)

#endif
