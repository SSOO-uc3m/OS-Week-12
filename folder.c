#include <stdio.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>


int readDirectory(char dirname[100]){
  int er;
	char nomfich[100], resp[30];
	struct stat atr;
	DIR *d;
	struct dirent *rd1;
	time_t date;	

	date=time(&date);
  
	if ((d=opendir(dirname))==NULL) {
		perror ("Directory doesn't exist");
		return -1;
	}
	else {
		while (( rd1 =readdir(d)) != NULL) {
			if ( (strcmp(rd1->d_name, ".")!=0 )&& (strcmp(rd1->d_name, "..")!=0 )){
				strcpy (nomfich, dirname);
				strcat (nomfich, "/");
				strcat (nomfich, rd1->d_name);
				printf ("File :%s:", nomfich);
				er=stat (nomfich, &atr);
				printf ("mode :%#o:", atr.st_mode);
				if ((atr.st_mode & 0400) != 0)
					printf (" Reading permission for the owner\n");
				else
					printf (" Not reading permission for the owner\n");
				if (S_ISDIR(atr.st_mode)) printf (" Is a directory \n");
				if (S_ISREG(atr.st_mode))
				/* Files modificados en los ultimos 10 dias */
				if ( (date - 10*24*60*60) <  atr.st_mtime) {
					printf ("FILE:%s: date access %s, in seconds %d\n", rd1->d_name,
                          ctime (&atr.st_mtime),(int) atr.st_mtime );
				}
			}
		} /* while*/
		closedir (d);
	}	

  return 0;
  
}
