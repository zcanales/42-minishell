#include <unistd.h>
#include <stdio.h>

int main(void)
{
	//int access(const char *pathname, int mode)
  char path[]="borrar";

  if (access(path, F_OK) != 0)
    printf("'%s' does not exist!\n", path);
  else {
    if (access(path, R_OK) == 0)
      printf("You have read access to '%s'\n", path);
    if (access(path, W_OK) == 0)
      printf("You have write access to '%s'\n", path);
    if (access(path, X_OK) == 0)
      printf("You have execute access to '%s'\n", path);
  }
}

