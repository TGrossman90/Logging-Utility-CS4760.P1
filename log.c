//Tom Grossman
//CS4760 - Operating Systems
//Project 1 - Logging Utility
//02/24/17
//Copyright © 2017 Tom Grossman. All Rights Reserved.

#include "log.h"

typedef struct list_struct {
	data_t item;
	struct list_struct *next;
} log_t;

static log_t *headptr = NULL;
static log_t *tailptr = NULL;

int addmsg(data_t data){
	//Successful return 0
	//Unsuccessful return -1
	//Sets errno on failure
    if (data.string == NULL) {
		errno = ENODATA;
        return -1;
    }
	
    log_t *newLog = malloc(sizeof(log_t));
    newLog->item = *(data_t*)malloc(sizeof(data_t));
    newLog->item.string = malloc(sizeof(char) * strlen(data.string));
    strncpy(newLog->item.string, data.string, strlen(data.string));
    newLog->next = NULL;
    
    if (!headptr) {
        headptr = newLog;
        tailptr = newLog;
    } else {
		tailptr->next = newLog;
        tailptr = tailptr->next;
	}
	
    return 0;
}

void clearlog(void) {
	//Releases all the storage that has been allocated
	//for the logged messages and epties the list of
	//logged mesages

	log_t *toClear = headptr;
	log_t *nextLog = NULL;
	while(toClear) {
		nextLog = toClear->next;
		free(toClear);
		toClear = nextLog;
	}
	
	headptr = NULL;
	tailptr = NULL;
	free(toClear);
	free(nextLog);
}

char *getlog(void) {
	//Allocates enough space for a string containing
	//the entire log, copies the log into this string,
	//and returns a pointer to the string
	//Unsucessful returns NULL
	//Sets errno on failure

	char *theLog = malloc(sizeof(char));
	
	// This is the only way I could find to have my getlog to stop returning random characters
	// but it still returns a random exclamation point sometimes and I can't figure out how to get rid of it
	memset(theLog, '\0', sizeof(char));
	
	log_t *tmp = headptr;
	if(tmp) {
		while(tmp) {
			theLog = realloc(theLog, (strlen(theLog) + strlen(tmp->item.string)));
			strcat(theLog, tmp->item.string);
			tmp = tmp->next;
		}
		free(tmp);
		
	} else {
		errno = ENOENT;
		return NULL;
	}
	
	return theLog;
}

int savelog(char *filename) {
	//Save log to a file
	//Successful return 0
	//Unsuccessful return -1
	//Sets errno on failure

	FILE *fp;
	fp = fopen(filename, "a");
	if(fp == NULL) {
		errno = ENOENT;
		return -1;
	}
	
	log_t *tmp = headptr;
	while(tmp) {
		fprintf(fp, "%s", tmp->item.string);
		tmp = tmp->next;
	}
	
	fclose(fp);
	free(tmp);
	return 0;
}
