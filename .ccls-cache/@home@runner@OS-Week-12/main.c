#include <stdio.h>
#include <string.h>
#include "folder.h"
#include "record.h"

const int NUMBER_RECORDS = 5;
char FILE_NAME[40]="records.dat";

int main(void) {
  
  
  /* Exercise 03

  
  char dirname[100];
  
  printf ("Enter a directory name\n");
  fgets (dirname, sizeof (dirname), stdin);	
  // we have to remove the breakline \n od the directory name

  dirname[strlen(dirname)-1]='\0';

  readDirectory(dirname);

  */
  
  /* Exercise 06
	TypeRecord record;

	for(int i = 1; i < NUMBER_RECORDS+1; i++) {
        record.code = i;
        snprintf(record.name, 30, "%s_%04d", "Client", i + 1);
		writeFile(FILE_NAME,record);
    }
	
	readFile(FILE_NAME);

  */
  
  return 0;
}


