#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define KEY 40000

int main(int element, char** args_array) {
  //printf("test\n");
  umask(0);

  if (element = 0) {//no argument included
    printf("You forgot to include an argument. Exiting.\n");
    return 0;
  }

  else {//argument included

    if (strcmp(args_array[1], "-c") == 0) {
      //do -c things here
      printf("TEST: you typed in -c.\n");
      return 0;
    }

    if (strcmp(args_array[1], "-r") == 0) {
      //do -r things here
      printf("TEST: you typed in -r.\n");
      return 0;
    }

    if (strcmp(args_array[1], "-v") == 0) {
      //do -v things here
      //printf("TEST: you typed in -v.\n");
      int fd_story = -1;
      fd_story = open("story.txt", O_RDONLY, 0666);

      if (fd_story == -1) {
        printf("Error encountered: %i, %s\n", errno, strerror(errno));
      }

      else {
        printf("File opened successfully.\n");
      }

      printf("Printing file contents.\n\n");

      int fd_stdin_backup = dup(stdin);
      dup2(fd_story, 0);
      char file[500];

      FILE *fp = fgets(file, 500, stdin);
      while (fp != NULL) { 
        printf("%s", file);
        fp = fgets(file, 500, stdin);
      }
      return 0;
    }

    else {//argument not one of the three shown
      printf("Argument not recognized. Exiting.\n");
      return 0;
    }
  }
  printf("How did you even get here?\n");
  return 0;
}


