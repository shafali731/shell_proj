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

/*======== int size_arr() ==========
Inputs:  char ** arr
Returns: int of the size of the array.

Gives the size of the array
====================*/
int size_arr(char ** arr){
  int i=0;
  while(arr[i]){
    i++;
  }
  return i;
}

/*======== int len_arr() ==========
Inputs:  char *** arr
Returns: int of the length of the array.

Gives the length of the array
====================*/
int len_arr(char*** arr){
	int i=0;
	while(arr[i]){
		i++;
	}
	return i;
}

/*======== char ** parse_args() ==========
Inputs:  char * line
Returns: array with arguments

Parses through the arguments
Each index is a different argument.
====================*/
char ** parse_args( char * line ) {
    char ** args_arr = calloc(sizeof(char*), 25);
    for(int i = 0; (args_arr[i] = strsep(&line, " ")); i++){
       if(*args_arr[i] == 0){
           i--;
       }
   }
   return args_arr;
}

/*======== char *** parse_lines() ==========
Inputs:  char * line
Returns: array with commands

Parses through multiple commands that are separated by a ;
Each index is a different command.
====================*/
char *** parse_lines (char* line){
	char *** ret_arr = calloc(256, sizeof(char**));
	char *s = strsep(&line, ";");
	int i = 0;
	while (s) {
	  ret_arr[i]=parse_args(s);
		s = strsep(&line, ";");
		i++;
	}
	return ret_arr;
}

/*======== int execute_command() ==========
Inputs:  char ** command
Returns: 0

Executes individual commands
It takes into account for <, >, >>, and cd
====================*/

int execute_command(char ** command) {
  if(!strcmp(command[0],"cd")){
			int director = chdir(command[1]); //returns 0 if sucessfully change directory
      if(director){ //if there was no change
        printf("%s\n", strerror(errno));
      }
	}
  else{
        int backup_stdout=dup(STDOUT_FILENO);
        int backup_stdin=dup(STDIN_FILENO);
        int parent = fork();
        if(parent){
          int status = 0;
          wait(&status);
          dup2(backup_stdout,STDOUT_FILENO);
          dup2(backup_stdin,STDIN_FILENO);
          return WEXITSTATUS(status);
        }
    else{
            for(int i=0;i<size_arr(command);i++){
                // Redirecting stdin, <
                 if(!strcmp(command[i],"<")){ //if command[i] is <
                  int fd=open(command[i+1],O_RDONLY);
                  dup2(fd,STDIN_FILENO);
                  char ** temp_arr = calloc(256, sizeof(char *)); ;
                  for (int ind = 0; ind < i; ind++){ //adjust
                    temp_arr[ind] = command[ind];
                  }
                   execvp(temp_arr[0],temp_arr);
                   close(fd);
                }
                // Redirecting stdout , >
                else if(!strcmp(command[i],">")){
                  int fd=open(command[i+1], O_WRONLY|O_CREAT, 0666);
                  dup2(fd,STDOUT_FILENO);
                  char ** temp_arr = calloc(256, sizeof(char *)); ;
                  for (int ind = 0; ind < i; ind++){
                    temp_arr[ind] = command[ind];
                  }
                   execvp(temp_arr[0],temp_arr);
                   close(fd);

                }
                // >>
                else if(!strcmp(command[i],">>")){
                  int fd=open(command[i+1], O_WRONLY|O_CREAT| O_APPEND, 0666);
                  dup2(fd,STDOUT_FILENO);
                  char ** temp_arr = calloc(256, sizeof(char *)); ;
                  for (int ind = 0; ind < i; ind++){
                    temp_arr[ind] = command[ind];
                  }
                   execvp(temp_arr[0],temp_arr);
                   close(fd);

                }


            	}
          		 execvp(command[0], command);
               return 0;
            }
      }
}


/*======== int execute_multiple_commands() ==========
Inputs:  char * command
Returns: 0

Takes in a string of commands
Parses through the string, executing each command.
====================*/
int execute_multiple_commands(char * command){
     char *** lines = parse_lines(command);
     for(int i=0;i<len_arr(lines);i++){
        execute_command(lines[i]);
     }
     return 0;
}
