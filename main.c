 /* 
 ● FUNCTION    : Command line interpreter 
 
 ● USAGE       : * To run commands, user command executed regardless of
                  argument into the prompt and then press 'Enter' key.

                 * To exit input 'q' and then press 'Enter' key
                
  ● OTHER      : * Uses execvp() function to execute a command (no paths needed)
  
                 * Baseline directory commands only
                 
  ● ADDITIONAL : Displays errors, validates user input (!NULL or not empty)
  */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>   // Library for fork() and execve() functions 
#include <errno.h>    // Used for "error handling"
#include <sys/wait.h> // Used for wait() function 

void startDisplay();
void menuPrompt();
void makeTokens(char *input, char* token, char* array[]);
void execute(char* array[]);


int main() {

  char *input = NULL; // pointer for user input
  char *token;
  char *array[512];
  size_t capline = 0; // Capacity
  int i;   
  
  startDisplay();
  
  while(1) {
    menuPrompt(); 
    getline(&input, &capline, stdin); //Gets  user input
    
    if(strcmp(input,"\n") == 0) {      // Check if input is empty
      perror("Please type in a command ");
      perror("or press 'q' to exit");
      continue;
    }
    makeTokens(input,token,array);          // Split input to make tokens   
    
    if (strcmp(array[0], "q") == 0) {    // If input is "q", exits shell
      return 0;
    }
    execute(array);    // Call execvp() function to execute valid user command
  }

}


void startDisplay() {
  printf("SIMPULL COMMAND LINE INTERPETER\n");
  printf("*To run, type <COMMAND> and PRESS 'Enter'\n");
  printf("*EXAMPLE: ls\n");
  printf("*To exit, type 'q' and pres 'Enter'\n\n");
}


void menuPrompt() {  // Prompt cursor
  printf("\n~/scli$ ");
}


void makeTokens(char *input, char *token, char *array[]) {
  int i = 0;
  token = strtok(input, "\n ");
                        
  while (token != NULL) { 
    array[i++] = token; // Add tokens into the array
    token = strtok(NULL, "\n ");
  }
  
  array[i] = NULL;
}


void execute(char *array[]){
  int pid = fork(); // Create a new process
  
  if (pid != 0) { // If not successfully completed
    int s;
    waitpid(-1, &s, 0); // Wait for process termination
  } else {
      if(execvp(array[0], array) == -1) { // If returned -1 => something went wrong! If not then command successfully completed */
        perror("invalid syntax.."); // Display error message
        exit(errno);
      }
    
    }
}