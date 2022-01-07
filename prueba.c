#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#define N 5
#include <sys/wait.h>
#include <stdlib.h>

typedef struct s_ch
{
	int i;
	int pid[N];
}t_ch;



int main(void)
{
	t_ch	ch;
	
	ch.i = N;
	while(ch.i--)
	{
		ch.pid[ch.i] = fork();
		if (ch.pid[ch.i] < 0)
			return (1);
		if (ch.pid[ch.i] != 0)
		{
			kill(ch.pid[ch.i], SIGSTOP);
		}
		else
		{
	//		sleep(1);
			printf("I'm child %d\n", ch.i);
	//		sleep(2);
			if (ch.i == N - 1)
				exit (0);
			if (ch.i == 2)
				exit (1);
			kill(ch.pid[ch.i + 1], SIGCONT);
			printf("Yo %d he desbloqueado a %d\n", ch.i, ch.i + 1);
			exit(0);
		}
	}
	printf("Todos los hijos bloqueados\n");
//	sleep(1);
	kill(ch.pid[0], SIGCONT);

	int i = -1;
	int status;
	while (++i < N)
	{
		waitpid(-1, &status, 0);
		if (status != 0 && i != (N -1))
		{
			printf("Hijos %d con problemas\n", i);
			kill(ch.pid[i + 1], SIGCONT);
		}
	}	
	return (0);
}