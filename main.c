//Tom Grossman
//CS4760 - Operating Systems
//Project 1 - Logging Utility
//02/24/17
//Copyright © 2017 Tom Grossman. All Rights Reserved.

#include "log.h"
#include "main.h"

int main (int argc, char **argv) {
	int index;
	int saveReturn;
	int flag;
	int nValue = 37;
	
	char *fileName;
	fileName = malloc(100);
	fileName = "logfile.txt";
	
	char *errStrm;
	errStrm = malloc(200);


	// Taken from https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html#Example-of-Getopt
	// Modified to fit what I needed
	while ((flag = getopt (argc, argv, "hn:l:")) != -1) {
		switch (flag) {
			case 'h':
				printf(" '-h' prints command flag help\n -n [integerValue] sets an integer to a variable\n -l [filename] sets the filename of the logfile");
				break;
				
			case 'n':
				if(isdigit(*optarg)) {
					nValue = atoi(optarg);
				} else {
					sprintf(errStrm, "'-n' expects an integer value, what didn't you understand? '%s' isn't an integer, buddy!", optarg);
					saveError(errStrm, argv[0], nValue);
				}
				break;
				
			case 'l':
				fileName = optarg;
				break;
				
			case '?':
				if (optopt == 'n') {
					sprintf(errStrm, "Seriously. '-%c' needs an integer... not that complicated!", optopt);
					saveError(errStrm, argv[0], nValue);
				} else if (optopt == 'l') {
					sprintf(errStrm, "C'mon dude. '-%c' needs an argument. A filename. Try again, you've got this (that's a lie, you probably don't)", optopt);
					saveError(errStrm, argv[0], nValue);
				} else if (isprint (optopt)) {
					sprintf(errStrm, "...No. `-%c' isn't an option", optopt);
					saveError(errStrm, argv[0], nValue);
				} else { 
					sprintf (errStrm, "I don't even know what `\\x%x' is", optopt);
					saveError(errStrm, argv[0], nValue);
				}
				break;
				
			default:
				// Assuming there are arguments, save to the logfile
				savelog(fileName);
				char *log = getlog();
				printf("%s\n", log);
				
				free(log);
				clearlog();
		}
	}

	// This gets all of the arguments that aren't supposed to be there
	for (index = optind; index < argc; index++) {
		sprintf (errStrm, "This '%s' isn't even an option. What are you doing?", argv[index]);
		saveError(errStrm, argv[0], nValue);
	}

	// Here are my three random messages to log
	sprintf(errStrm, "Batman > Superman");
	saveError(errStrm, argv[0], nValue);

	sprintf(errStrm, "I like Dr. Pepper");
	saveError(errStrm, argv[0], nValue);

	sprintf(errStrm, "Memory leak errors are a massive pain");
	saveError(errStrm, argv[0], nValue);

	// Save to log, print log
	savelog(fileName);

	char *log = getlog();
	log = getlog();
	printf("%s\n", log);

	free(log);
	free(errStrm);
	clearlog();

	return 0;
}

// Function to save each individual log
void saveError(char *err, char *arg, int nValue) {
	char *msg;
	msg = malloc(200);
	data_t *errorMsg = (data_t*)malloc(sizeof(data_t));

	time_t theTime;
	theTime = time(NULL);
	errorMsg->time = theTime;
	
	struct tm * p = localtime(&errorMsg->time);
	char *time = malloc(100);
	strftime(time, 1000, "%D @ %T", p);

	sprintf(msg, "%s: %s: Error: nValue = %i - %s\n", arg, time, nValue, err);
	errorMsg->string = msg;

	int toLog = addmsg(*errorMsg);
	if(toLog == -1) {
		perror("Error: ");
	}

	free(errorMsg);
	free(msg);
	free(time);

}

