/*// Standard include files. stdio.h is required.
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>

//Used for select(2) 
#include <sys/types.h>
#include <sys/select.h>
#include <signal.h>
#include <stdio.h>

//Standard readline include files. 
#include <readline/readline.h>
#include <readline/history.h>*/

#include <errno.h>
//#include <error.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <setjmp.h>
#include <sys/types.h>
#include <sys/select.h>



void handle_signals(int signo) {
  if (signo == SIGINT) {
    printf("You pressed Ctrl+C\n");
  }
}

int main (int argc, char **argv)
{
   //printf("path is: %s\n", path_string);
  char * input;
  char * shell_prompt = "i-shell> ";

  if (signal(SIGINT, handle_signals) == SIG_ERR) 
    printf("failed to register interrupts with kernel\n");

  //set up custom completer and associated data strucutres
  setup_readline();

  while (1) 
  {
    input = readline(shell_prompt);
    if (!input)
      break;
    add_history(input);

    //do something with the code
    execute_command(input);

  }  
  return 0;
}
