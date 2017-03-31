//Tom Grossman
//CS4760 - Operating Systems
//Project 1 - Logging Utility
//02/24/17
//Copyright © 2017 Tom Grossman. All Rights Reserved.

#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

typedef struct data_struct {
		time_t time;
		char *string;
} data_t;

int addmsg(data_t data);
void clearlog(void);
char *getlog(void);
int savelog(char *filename);

#endif
