/*Pongamos en práctica todo lo aprendido en esta sesión. Haced un programa que limpie la pantalla, imprima un mensaje que ponga:
¿Desea que el programa acabe? (s/n) 
con la s en modo inverso para resaltar que es la opción por defecto. El mensaje debe aparecer en la línea 3, columna 7 de la pantalla. No uséis tput para ello. Usad directamente los códigos del terminal vt100 que vienen en el resumen. El programa se debe quedar esperando 10 segundos como máximo a que el usuario pulse una tecla. A la sola pulsación de una 's' el programa acaba con un código de retorno 0. Si se pulsa una 'n' el programa acaba con un código de retorno 1. Si se pulsa otra letra, el programa acaba con un código de retorno 2. Si no se pulsa nada y pasan los diez segundos, el programa acaba con código de retorno 3. No usar alarm. Dejad el terminal como estaba al principio, incluso si se pulsa CTRL+C para interrumpir su funcionamiento.
*/


/* Codigos de error         */
/* (no indicados enunciado) */
/* 10: Error de ejecucion   */
/* 11: Salida por CTRL+C    */

#define _HPUX_SOURCE

#define ESC 27
#define STD_IN 0
#define STD_OUT 1

#include <signal.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>

struct termios vieja;
struct sigaction int_old;
int dev=11;

void aborto (int);

int main (void) {
  char term_clear[7],
       term_posic[7],
       term_invsi[5],
       term_invno[5],
       letra='\0';
  struct termios actual;
  struct sigaction int_new;

  /* Almacenamos cosas */
  if (tcgetattr(STD_IN, &vieja)==-1) {
    perror ("ioctl/TCGETA vieja:");
    return 10;
  }
  if (tcgetattr(STD_IN, &actual)==-1) {
    perror ("ioctl/TCGETA actual:");
    return 10;
  }

  int_new.sa_handler=aborto;
  sigemptyset (&(int_new.sa_mask));
  int_new.sa_flags=0;
  if (sigaction (SIGINT, &int_new, &int_old)==-1) {
    perror ("sigaction:");
    return 10;
  }

  /* Mensaje */
  sprintf (term_clear, "%c[H%c[J", ESC, ESC);
  sprintf (term_posic, "%c[3;7H",  ESC);
  sprintf (term_invsi, "%c[7m",    ESC);
  sprintf (term_invno, "%c[m",     ESC);
  printf ("%s%s¿Desea que el programa acabe? (%ss%s/n)",
          term_clear, term_posic, term_invsi, term_invno);
  fflush (stdout);
/* Es importante poner el fflush(stdout);
   pues si no, la frase se quedaría en el buffer
   intermedio y no aparecería de inmediato en la
   pantalla. */

  /* Entrada */
  //& ~ICANON Desactivar el bit: lo logramos haciendo un AND con el complementario de la macro
  //Ponemos modo no canonico -> inmediato 
  //& ICANON -> Desactival  | ~ICANON
  //& ECHO no aparece
  //| ECHO aparece -> Aparece por defecto
  actual.c_lflag=actual.c_lflag & ~ ICANON | ECHO; // ~ICANON | ECHO;i
  actual.c_cc[VTIME]=100;
  actual.c_cc[VMIN] =0;
  if (tcsetattr(STD_IN,TCSANOW, &actual)==-1) {
    perror ("ioctl/TCSETA actual:");
    return 10;
  }

  switch (read(STD_IN, &letra, 1)) {
    case 0:
      dev=3;
      break;
    case 1:
      switch (letra) {
        case 's':
          dev=0;
          break;
        case 'n':
		  printf("hola\n");
          dev=1;
          break;
        default:
          dev=2;
          break;
      }
      break;
    default:
      perror ("read: ");
      return 10; 
  }
  
  printf ("%s", term_clear);
  fflush (stdout);
  aborto (dev);
}

void aborto (int nada) {
  if (tcsetattr(STD_IN,TCSANOW,  &vieja)==-1) {
    perror ("ioctl/TCSETA vieja (aborto):");
    exit (10);
  }
  if (sigaction (SIGINT, &int_old, NULL)==-1) {
    perror ("sigaction (aborto):");
    exit (10);
  }
  
  exit (dev);
}
