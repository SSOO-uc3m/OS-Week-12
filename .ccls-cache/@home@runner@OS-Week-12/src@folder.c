#include <stdio.h>

#include <time.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>


int readDirectory(char nomdir[100]){
  int er;
	char nomfich[100], resp[30];
	struct stat atr;
	DIR *d;
	struct dirent *rd1;
	time_t fecha;

	

	fecha=time(&fecha);
	if ((d=opendir(nomdir))==NULL) {
		printf ("No existe ese Directory \n");
		return -1;
	}
	else {
		while (( rd1 =readdir(d)) != NULL) {
			if ( (strcmp(rd1->d_name, ".")!=0 )&& (strcmp(rd1->d_name, "..")!=0 )){
				strcpy (nomfich, nomdir);
				strcat (nomfich, "/");
				strcat (nomfich, rd1->d_name);
				printf ("File :%s:", nomfich);
				er=stat (nomfich, &atr);
				printf ("modo :%#o:", atr.st_mode);
				if ((atr.st_mode & 0400) != 0)
					printf (" permiso R para propietario\n");
				else
					printf (" No permiso R para propietario\n");
				if (S_ISDIR(atr.st_mode)) printf (" Es un Directory \n");
				if (S_ISREG(atr.st_mode))
				/* Files modificados en los ultimos 10 dias */
				if ( (fecha - 10*24*60*60) <  atr.st_mtime) {
					printf ("FILE:%s: fecha acceso %s, en sgdos %d\n", rd1->d_name,
                          ctime (&atr.st_mtime),(int) atr.st_mtime );
				}
			}
		} /* while*/
		closedir (d);
	}	
  
}
