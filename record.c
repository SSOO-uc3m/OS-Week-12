#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include "record.h"

int writeFile (char * nameFile, TypeRecord record ){ 

	int file ;
	int position;


	/* Open File */
	file = open (nameFile,O_APPEND|O_WRONLY) ;
	if (file != -1) {
	  printf ("The file already exists, append records to the end of file \n");
	}

	if (file < 0) {
	  printf ("The file do not exist\n");
	  printf ("The file is going to be created\n");
	  file=open (nameFile, O_CREAT| O_WRONLY, S_IWUSR|S_IRUSR) ;
	  if (file < 0) {
	      printf ("Error creating file %s :\n",nameFile);
	      return -1;
	  }
	}

	/* Write record */        
	   
	if (write (file, &record, sizeof (record)) < 0)  {
	      printf ("Error writing record to the file %s :\n",nameFile);
	      return -1;
	}
        

	/* print the position */
        position = lseek(file,0,SEEK_CUR) ;
        printf ("We are in the position %d of the File %s\n", position,nameFile );

	/* Cerrar File */
	close(file);
	
	return 0;
}

int readFile(char * nameFile){

	int file;
	int read_bytes;
	TypeRecord record;


	file = open (nameFile, O_RDONLY) ;
	if (file == -1) {
    	    fprintf (stderr, "No se ha podido abrir el File\n");
	    return -1 ;
        }
		
    printf  ("reading file %s\n",nameFile);
	read_bytes = read (file, &record, sizeof(record));
	while ( read_bytes !=0 ){
	        printf  ("record read -> code:%d: name:%s:\n",
			 record.code, 
			 record.name);
	        read_bytes = read (file, &record, sizeof(record));
       	}		

	close(file);
	return 0;

}