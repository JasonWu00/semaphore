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
  int* data = shmat(shared_mem_identifier, 0, 0);

  int fd_story = -1;
  fd_story = open("story.txt", O_RDWR, 0644);

  struct stat filedata;
  stat(fd_story, &filedata);

  if (*data == NULL) {
    printf("Error encountered: %i, %s\n", errno, strerror(errno));
    return 0;
  }

  else {
    printf("Current story:\n\n");
    char lastline[100];
    return_last_line(lastline);
    printf("%s\n", lastline);

    char input[100];
    printf("Your addition to the story: ");
    fgets(input, 100, stdin);
    pwrite(fd_story, input, 100, filedata.st_size);
  }
  close(fd_story);
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

    dup2(fd_stdin_backup, 0);
  }
  close(fd_story);
}

void return_last_line(char output[100]) {
  int fd_story = -1;
  fd_story = open("story.txt", O_RDONLY, 0644);
  char file[100] = "\0";

  if (fd_story == -1) {
    printf("Error encountered: %i, %s\n", errno, strerror(errno));
  }

  else {
    //printf("Printing story contents.\n\n");

    int fd_stdin_backup = dup(stdin);
    dup2(fd_story, 0);

    FILE *fp = fgets(file, 500, stdin);
    while (fp != NULL) {
      //printf("%s", file);
      fp = fgets(file, 500, stdin);
    }
    dup2(fd_stdin_backup, 0);
  }
  close(fd_story);
  output = file;
}
