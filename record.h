#ifndef __RECORD_H__
#define __RECORD_H__

typedef struct {
	int code;
	char name[30];
} TypeRecord;


int writeFile (char * nameFile, TypeRecord record );

int readFile(char * nameFile);


#endif // __RECORD_H__