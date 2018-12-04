# Shell[ing] out commands
##Shafali Gupta

##Features:
  - Forks and executes commands
  - Parses through multiple commands
  - Redirection (<, >, >>)
  - Exiting
  - Change directories
  - Display current working directory

##Not implemented, but attempted
  - piping

##Bugs
  - sometimes exiting takes a couple of tries to work.

##Files & Function Headers:
commands.c
  Handles parsing through lines and executing them.

```c
  int size_arr()
  Inputs:  char ** arr
  Returns: int of the size of the array.

  Gives the size of the array

```

```c
  int len_arr()
  Inputs:  char *** arr
  Returns: int of the length of the array.

  Gives the length of the array
```

  ```c
  char ** parse_args() ==========
  Inputs:  char * line
  Returns: array with arguments

  Parses through the arguments
  Each index is a different argument.
```

  /*======== char *** parse_lines() ==========
  Inputs:  char * line
  Returns: array with commands

  Parses through multiple commands that are separated by a ;
  Each index is a different command.
  ====================*/

  /*======== int execute_command() ==========
  Inputs:  char ** command
  Returns: 0

  Executes individual commands  
  It takes into account for <, >, >>, and cd
  ====================*/

  /*======== int execute_multiple_commands() ==========
  Inputs:  char * command
  Returns: 0

  Takes in a string of commands
  Parses through the string, executing each command.
  ====================*/

 shell.c
  Executes the shell
 /*======== int main() ==========
 Inputs: nothing
 Returns: 0

 Prompts for inputs
 Exits shell
 ====================*/
