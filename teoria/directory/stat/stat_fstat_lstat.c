/*
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

   int stat(const char *file_name, struct stat *buf);
   int fstat(int filedes, struct stat *buf);
   int lstat(const char *file_name, struct stat *buf);

   Estas  funciones  devuelven información del fichero especificado. No se necesitan derechos
       de acceso al fichero para conseguir la  información  pero  sí  se  necesitan  derechos  de
       búsqueda para todos los directorios del camino al fichero.

       stat examina el fichero al que apunta file_name y llena buf.

       lstat  es  idéntico  a stat, salvo en caso de que se trate de un enlace simbólico, en cuyo
       caso se examina el enlace mismo, no el fichero al que hace referencia.

       fstat es idéntico a stat, pero sólo el fichero abierto apuntado por filedes (tal y como lo
       devuelve open(2)) es examinado en lugar de file_name.

       Todos devuelven una estructura stat, que contien los siguientes campos:

              struct stat {
                  dev_t         st_dev;      / dispositivo /
                  ino_t         st_ino;      / inodo /
                  mode_t        st_mode;     / protección /
                  nlink_t       st_nlink;    / número de enlaces físicos /
                  uid_t         st_uid;      / ID del usuario propietario /
                  gid_t         st_gid;      / ID del grupo propietario /
                  dev_t         st_rdev;     / tipo dispositivo (si es
                                                dispositivo inodo) /
                  off_t         st_size;     / tamaño total, en bytes /
                  blksize_t     st_blksize;  / tamaño de bloque para el
                                                sistema de ficheros de E/S /
                  blkcnt_t      st_blocks;   / número de bloques asignados /
                  time_t        st_atime;    / hora último acceso /
                  time_t        st_mtime;    / hora última modificación /
                  time_t        st_ctime;    / hora último cambio /
              };
	symbolic file ln -s			  
			  
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h> 	//printf

int main(void)
{
	struct stat buf;

	printf("\n///STAT/////\n");
 	stat("file_1", &buf);
 	printf("File size = %lld \n", buf.st_size);
	printf("ID group = %d\n", buf.st_uid);
	printf("Time last access = %ld\n", buf.st_atime);
	printf("Dispositivo = %d\n", buf.st_dev);
	
	printf("\n///LSTAT/////\n");
 	lstat("file_2", &buf);
 	printf("File size = %lld \n", buf.st_size);
	printf("ID group = %d\n", buf.st_uid);
	printf("Time last access = %ld\n", buf.st_atime);
	printf("Dispositivo = %d\n", buf.st_dev);
	
	printf("\n///FSTAT/////\n");
 	fstat("file_1", &buf);
 	printf("File size = %lld \n", buf.st_size);
	printf("ID group = %d\n", buf.st_uid);
	printf("Time last access = %ld\n", buf.st_atime);
	printf("Dispositivo = %d\n", buf.st_dev);
	return (0);
}


