#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/sem.h>

#define KEY 40000
#define SEGSIZE 100

int main(int element, char** args_array) {
  //printf("test\n");
  umask(0);

  if (element = 0) {//no argument included
    printf("You forgot to include an argument. Exiting.\n");
    return 0;
  }

  else {//argument included
    int shared_mem_identifier = -1;

    if (strcmp(args_array[1], "-c") == 0) {//create file
      //do -c things here
      //printf("TEST: you typed in -c.\n");

      int sem_identifier = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);//makes the semaphore
      if (sem_identifier == -1) {//semget failed
        printf("Error encountered: %i, %s\n", errno, strerror(errno));
        printf("A debug is probably needed.\n");
      }
      else {
        printf("Semaphore made\n");
      }

      int fd_story = -1;
      fd_story = open("story.txt", O_RDONLY | O_TRUNC | O_CREAT, 0644);//makes the file
      printf("File made\n");

      shared_mem_identifier = shmget(KEY, SEGSIZE, IPC_CREAT | 0644);//makes the shared mem
      printf("Shared memory made\n");

      return 0;
    }

    if (strcmp(args_array[1], "-r") == 0) {//remove file
      //do -r things here
      //printf("TEST: you typed in -r.\n");
      printf("The story, before it is deleted:\n\n");
      print_file_contents();
      printf("Removing everything.\n");
      int sem_identifier = semget(KEY, 1, 0);
      semctl(sem_identifier, IPC_RMID, 0);
      shmctl(shared_mem_identifier, IPC_RMID, 0);
      printf("Semaphore, shared segment, and file removed.");
      execl("/bin/rm", "rm", "-rf", "story.txt", NULL);
      return 0;
    }

    if (strcmp(args_array[1], "-v") == 0) {//view the file
      //do -v things here
      //printf("TEST: you typed in -v.\n");
      print_file_contents();
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

void print_file_contents() {
  int fd_story = -1;
  fd_story = open("story.txt", O_RDONLY, 0644);

  if (fd_story == -1) {
    printf("Error encountered: %i, %s\n", errno, strerror(errno));
  }

  else {
    printf("Printing story contents.\n\n");

    int fd_stdin_backup = dup(stdin);
    dup2(fd_story, 0);
    char file[500];

    FILE *fp = fgets(file, 500, stdin);
    while (fp != NULL) {
      printf("%s", file);
      fp = fgets(file, 500, stdin);
    }
  }
}
