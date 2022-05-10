/*
 * The LD_PRELOAD trick
 * http://www.goldsborough.me/c/low-level/kernel/2016/08/29/16-48-53-the_-ld_preload-_trick/#:~:text=Outro-,Introduction,shared%20library%20before%20other%20libraries.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 100

int main(int argc, const char *argv[]) {
  int amount_read = 0;
  char *buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));

  int fd = fileno(stdin);
  if ((amount_read = read(fd, buffer, sizeof(buffer))) == -1) {
    perror("Error reading");
    return EXIT_FAILURE;
  }

  if (fwrite(buffer, sizeof(char), amount_read, stdout) == -1) {
    perror("Error writing");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
