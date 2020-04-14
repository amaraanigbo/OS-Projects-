/**********************************************
 * 
 * @file myshell.c
 * 
 * @author Max Barrett and Amara Anigbo
 * 
 * Project 1 
 * 
 * ********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <dirent.h> 
#include <limits.h>

/*
  Function Declarations for builtin shell commands:
 */
int my_clr(char **cmds);
int my_quit(char **cmds);
int my_pause(char **cmds);
int my_echo(char **cmds);
int my_dir(char **cmds);

/*
  Array of blocked unix string commands
 */
char *blocked_cmds[] = {
  "clear",
  "exit",
  "pause",
  "echo",
  "ls"
};

/*
  Array of built in string commands for each function
 */
char *my_cmds[] = {
  "myclr",
  "myquit",
  "mypause",
  "myecho",
  "mydir"
};

/*
  Array of built in functions for each command
 */
int (*my_funcs[]) (char **) = {
  &my_clr,
  &my_quit,
  &my_pause,
  &my_echo,
  &my_dir
};

/*
  Clear screen
 */
int my_clr(char **cmds) {
  printf("\e[1;1H\e[2J");
  return 1;
}

/*
  Exit shell
 */
int my_quit(char **cmds) {
  return 0;
}

/*
  Pause shell until [Enter] is pressed
 */
int my_pause(char **cmds) {
  getchar();
  return 1;
}

/*
  Display comment on new line
 */
int my_echo(char **cmds) {
  int i = 1;
  while (cmds[i] != NULL) {
    printf("%s ", cmds[i]);
    i++;
  }
  printf("\n");
  return 1;
}

/*
  List contents of specified directory (works relative to current working directory)
 */
int my_dir(char **cmds) {
  struct dirent *dir_pointer;
  DIR *dir = opendir(cmds[1]); // assign dir to directory specified in input

  if (dir == NULL) { // can't open directory
    printf("Could not open current directory\n" ); 
    return 1; 
  } 
  while ((dir_pointer = readdir(dir)) != NULL) { // loop through directory
    printf("%s\n", dir_pointer->d_name); 
  }
  closedir(dir);
  return 1;
}

/*
  Gets the current working directory and prints
 */
int get_dir(void) {
  char cur_dir[PATH_MAX];
  if (getcwd(cur_dir, sizeof(cur_dir)) != NULL) {
    printf("%s ", cur_dir);
  } else {
    perror("Directory error");
    return 0;
   }
   return 1;
}

/*
  Read input from terminal and return a string
 */
char *read_line(void) {
  char *line = NULL;
  size_t bufsize = 0;
  getline(&line, &bufsize, stdin);
  return line;
}

#define ARGDELIM " \t\r\n\a"
/*
  Split the string returned from the readline() method into an array of tokens, using " \t\r\n\a" as the delimitors.
 */
char **split_line(char *line) {
    int pos = 0;
    char **tokens = malloc(sizeof(char*)*64);
    char *token;
    token = strtok(line, ARGDELIM);
    
    while(token != NULL) { // iterate through string (line)
        tokens[pos] = token;
        pos++;
        token = strtok(NULL, ARGDELIM); 
    }

    tokens[pos] = NULL;
    return tokens;
}

/*
  Run external program using fork and execvp
*/
int run_program(char **cmds) {
  pid_t pid;

  switch (pid = fork()) {
  case 0: // child process
    execvp(cmds[0], cmds);
    perror("execvp");
    exit(EXIT_FAILURE);
  
  default: // parent waits for child
    wait(NULL);
    break;
  
  case -1: // error forking
    perror("fork");
    exit(EXIT_FAILURE);
  }
  return 1;
}

/*
  Execute either a built in function or run an external program
*/
int execute_cmd(char **cmds) {
  if (cmds[0] == NULL) { // no command was entered
    return 1;
  }

  for (int i = 0; i < 5; i++) {
    if (strcmp(cmds[0], blocked_cmds[i]) == 0) { // check if command matched any of the blocked unix commands
      printf("Blocked command entered\n");
      return 1;
    }
  }

  for (int i = 0; i < 5; i++) {
    if (strcmp(cmds[0], my_cmds[i]) == 0) { // check if command matches any of the built in commands
      return (*my_funcs[i])(cmds);
    }
  }

  return run_program(cmds); // run external program, command is not built in
}

/*
  Main function with loop running shell
*/
int main(int argc, char **argv) {

  char *input;
  char **split_input;
  int status;

  do {
    get_dir();
    input = read_line(); // read input
    split_input = split_line(input); // split input into token array
    status = execute_cmd(split_input); // execute command based on input

    free(input);
    free(split_input);
  } while (status); //checks status after otherwise loop never runs. Returning 1 continues execution

  return EXIT_SUCCESS;

}