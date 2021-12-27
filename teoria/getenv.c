#include        <stdio.h>
#include        <curses.h>
#include        <term.h>
#include        <stdlib.h>

int     main()
{
  const char *name;
  char  *bp;
  char  *term;
  int   height;
  int   width;

  bp = malloc(sizeof(*bp));
  name = "TERM";
  if ((term = getenv(name)) == NULL)
    return (1);
  printf("My PRETTY PRETTY terminal is %s.\n", term);
  tgetent(bp, term);
  height = tgetnum("li");
  width = tgetnum("co");
  printf("H : %d\nL : %d\n", height, width);
  free(bp);
  return (0);
}

prueba DE EDURNE
//getenv()
//tgetent()
//
