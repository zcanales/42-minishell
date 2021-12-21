/*
 * La función opendir se usa para abrir un directorio. Su prototipo es:

		DIR *opendir(const char *nombre);

El único parámetro que recibe es el nombre del directorio que se quiere abrir. Devuelve un puntero al flujo de directorio (DIR) o NULL en caso de error. Este puntero se colocará en la primera entrada del directorio.

La función readdir sirve para leer las entradas del directorio abierto con opendir. Su prototipo es:

		struct dirent *readdir(DIR *dir);

Recibe como parámetro el puntero al flujo de directorio (DIR) que se obtuvo con opendir y devuelve un puntero a una estructura dirent o NULL en caso de error o fin del directorio. Esta estructura dirent representa la siguiente entrada de directorio al que apunte dir.

La función closedir cierra el flujo de directorio que se obtuvo con opendir. Su prototipo es:

		int closedir(DIR *dir);

		Recibe como parámetro el puntero al flujo de directorio (DIR) y devuelve 0 en caso de éxito y -1 en caso de error.
		https://pasky.wordpress.com/2009/08/05/funciones-opendir-readdir-y-closedir-en-c/
*/
#include <sys/types.h>
#include <dirent.h> 	//Open, close, read dir
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>		//errorres = EACCES, ENOENT, ENOTDIR

int main (int argc, char *argv[]){

 /* Variables */
 DIR *dirp;
 struct dirent *direntp;

 /* Comprobamos los argumentos */
	if (argc != 2)
	{
		fprintf(stderr,"Uso: %s directorio\n", argv[0]);
		exit(1);
	}

 /* Abrimos el directorio */
	errno = 0;
	dirp = opendir(argv[1]);
	if (dirp == NULL)
	{
		 printf("Error: No se puede abrir el directorio\n");
		 switch (errno) 
		 {
            case EACCES: printf("Permission denied\n"); break;
            case ENOENT: printf("Directory does not exist\n"); break;
            case ENOTDIR: printf("'%s' is not a directory\n", argv[1]); break;
    	 }
		exit(2);
	}

/* Leemos las entradas del directorio */
	errno = 0;
	printf("i-nodo\toffset\t\tlong\tnombre\n");
	while ((direntp = readdir(dirp)) != NULL) 
		printf("%llu\t%llu\t%d\t%s\n", direntp->d_ino, direntp->d_seekoff, direntp->d_reclen, direntp->d_name);
	if (errno != 0) 
	{
		if (errno == EBADF)
            printf("Invalid directory stream descriptor\n");
        else
            perror("readdir");
    } 
	else
        printf("End-of-directory reached\n");

 /* Cerramos el directorio */
	if (closedir(dirp))
		 perror("closedir");
	else
		printf("Success!\n");
	return (0);
}
/*
 * dirp = opendir(".");
           if (dirp == NULL)
                   return (ERROR);
           len = strlen(name);
           while ((dp = readdir(dirp)) != NULL) {
                   if (dp->d_namlen == len && strcmp(dp->d_name, name) == 0) {
                           (void)closedir(dirp);
                           return (FOUND);
                   }
           }
           (void)closedir(dirp);
           return (NOT_FOUND);
		   */
