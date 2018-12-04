#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <ctype.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include "commands.h"

/*======== int main() ==========
Inputs: nothing
Returns: 0

Prompts for inputs
Exits shell
====================*/
int main() {
  while(1){
     char cwd_buffer[256];
     getcwd(cwd_buffer, sizeof(cwd_buffer));
     char str[256];
     printf("%s~sgupta ", cwd_buffer);
     fgets(str, 256, stdin);
     if (!strncmp("exit", str, 4 )) {
        exit(0);
     }
     char * temp = str;
     char * init = strsep(&temp, "\n");
    execute_multiple_commands(str);
  }
  return 0;
}
