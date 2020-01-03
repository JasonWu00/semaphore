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
#include "control.h"

#define KEY 40000
#define SEGSIZE 100

int main() {
  int shared_mem_identifier = shmget(KEY, SEGSIZE, 0);
  char* data = shmat(shared_mem_identifier, 0, 0);

  if (*data == NULL) {
    printf("Error encountered: %i, %s\n", errno, strerror(errno));
    return 0;
  }

  else {
    printf("Current story:\n\n");
    //print_file_contents();
    printf("Your addition to the story: ");
  }
  return 0;
}
