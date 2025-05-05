#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define TERMINAL_IN 0
#define TERMINAL_OUT 1
#define ERROR_OUT 2

void fileCopy(int, int);

int main(int argc, char *argv[]) {
  int fd;

  if (1 == argc) {
    fileCopy(TERMINAL_IN, TERMINAL_OUT);
  } else {
    while (--argc > 0) {
      if ((fd = open(*(++argv), O_RDONLY)) == -1) {
        write(ERROR_OUT, errno, sizeof(errno));

        exit(EXIT_FAILURE);
      } else {
        fileCopy(fd, TERMINAL_OUT);

        if (-1 == close(fd)) {
          write(ERROR_OUT, errno, sizeof(errno));

          exit(EXIT_FAILURE);
        }
      }
    }
  }
}

void fileCopy(int ifd, int ofd) {
  int readErrorChecker;
  char character = ' ';

  while(EOF != character && 0 < (readErrorChecker = read(ifd, &character, sizeof(character)))) {
    write(ofd, &character, sizeof(character));
  }

  if(-1 == readErrorChecker) {
    write(ERROR_OUT, errno, sizeof(errno));

    exit(EXIT_FAILURE);
  }
}
