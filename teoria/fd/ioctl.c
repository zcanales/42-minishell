/*
 *   #include <sys/ioctl.h>

     int
     ioctl(int fildes, unsigned long request, ...);

	 Una llamada ioctl toma como parámetros:

un descriptor de archivos abierto
un número de código de requerimiento
también un valor entero, posiblemente sin signo (va al driver), o un puntero a datos (también va al driver y vuelve de él)
El kernel generalmente envía un ioctl directamente al driver, el cual puede interpretar el número de requerimiento y datos en cualquier forma requerida. Los escritores del driver documentan cada número de requerimiento del driver para ese driver particular, y los proveen de constantes en el archivo de cabeceras (*.h)
	 */

#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
//#include <linux/kd.h>
#include <time.h>
#include <unistd.h>    /*Encabezado para la función sleep() and close() */ 

/*int get_state(int fd,int *estado)
{
    if (-1 == ioctl(fd, KDGKBLED, estado)){          
//Si la función ioctl devuelve -1, hubo un error, que será especificado en la función perror(), si es cero significa que finalizo exitosamente
        perror("ioctl");
        close(fd);
        return -1;
    }
   return 0;    
}

void print_caps_lock_state(int estado)
{
    printf("Estado Caps Lock: %s (%d)\n",
           (estado & K_CAPSLOCK) == K_CAPSLOCK ? "on" : "off", estado);
}

int apaga(int fd,int *estado)
{
    get_state(fd,estado);
    if (-1 == ioctl(fd, KDSKBLED, *estado ^ K_CAPSLOCK)){
        perror("ioctl set");
        close(fd);
        return -1;
    }
    return 0;
}

int prende(int fd,int *estado)
{
    if (-1 == ioctl(fd, KDSKBLED, K_CAPSLOCK)){
        perror("ioctl set");
        close(fd);
        return -1;
    }
    get_state(fd,estado);
    return 0;
}

int main()
{
    int fd = open("/dev/tty0", O_NOCTTY);

    if (fd == -1){
        perror("open");
        return -1;
    }

    int estado = 0;  
 //   prende(fd,&estado);    
    sleep(1);
   // apaga(fd,&estado);
    sleep(2);
   // prende(fd,&estado);
    sleep(1);
   // apaga(fd,&estado);
    close(fd);
    return 0;
}*/

/*  prueba_ioctl.c */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>


/* IOCTL_ABRIR: 6301
   IOCTL_CERRAR: 6302
   IOCTL_PLAY: 6303
   IOCTL_STOP: 6304
   IOCTL_PAUSE: 40046305 */

int main() {
        int file, result;
        int segundos=10;
        file=open("ioctl_prueba",O_RDWR);
        if (file==-1)
		{
			printf("Error: Open\n");
		   	return(-1);
		}


        result=ioctl(file, 0x6301);
        if (result==0) printf("OK\n");
        result=ioctl(file, 0x6302);
        if (result==0) printf("OK\n");
        result=ioctl(file, 0x6303);
        if (result==0) printf("OK\n");
        result=ioctl(file, 0x6304);
        if (result==0) printf("OK\n");
        result=ioctl(file, 0x40046305,&segundos); /* atención al tipo del
                                                     argumento */
        if (result==0) printf("OK\n");

        /* ahora una que falle */
        result=ioctl(file, 0x6305);
        if (result) printf("ioctl(file,0x6305) falló, como debe ser\n");


        result=close(file);
        if (file==-1) return(-1);
        return(result);
}

