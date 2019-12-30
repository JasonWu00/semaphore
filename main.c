#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/shm.h>

int main(int element, char** args_array) {
  int i = 0;
  if (element < 1) {//no argument included
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
      printf("TEST: you typed in -v.\n");
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
