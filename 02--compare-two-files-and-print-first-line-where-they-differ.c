#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 100

void compareLines(char *, char *);

int main(int argc, char **argv) {
  FILE *firstFilePtr, *secondFilePtr;
  char firstFileLine[MAX_LINE_LENGTH], secondFileLine[MAX_LINE_LENGTH], *tempFirstFileLinePtr, *tempSecondFileLinePtr;
  char firstLineErrChk, secondLineErrChk;
  int foundDiff = 1;

  if (3 == argc) {

    if (NULL == (firstFilePtr = fopen(argv[1], "r")) || NULL == (secondFilePtr = fopen(argv[2], "r"))) {
      perror("File failed to open\n");

      exit(EXIT_FAILURE);
    }

    while (foundDiff
      && NULL != (firstLineErrChk = fgets(firstFileLine, sizeof(firstFileLine), firstFilePtr))
      && NULL != (secondLineErrChk = fgets(secondFileLine, sizeof(secondFileLine), secondFilePtr))) {

      tempFirstFileLinePtr = firstFileLine;
      tempSecondFileLinePtr = secondFileLine;

      while ('\0' != *tempFirstFileLinePtr || '\0' != *tempSecondFileLinePtr) {

        if (*tempFirstFileLinePtr != *tempSecondFileLinePtr) {
          fputs(firstFileLine, stdout);
          fputs(secondFileLine,  stdout);
          foundDiff = 0;

          break;
        }
        tempFirstFileLinePtr++;
        tempSecondFileLinePtr++;
      }
    }
  } else {
    printf("You need exactly 2 files to compare\n");

    exit(EXIT_FAILURE);
  }

  if (firstLineErrChk == NULL || secondLineErrChk == NULL) {
    perror("Failed to get next line\n");

    exit(EXIT_FAILURE);
  }

  fclose(firstFilePtr);
  fclose(secondFilePtr);
}
