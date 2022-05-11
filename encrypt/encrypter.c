/*
 * Accepts a file and a key. Outputs to file.enc
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int my_encrypt(char *i_buf, struct stat *sb, char* o_buff, uint8_t key) {
    int rot = 1;
    char enc;

    for (int i = 0; i < sb->st_size; i++) {
      *o_buff = *i_buf ^ key;
      i_buf++; o_buff++;
    }

//  __asm__ (
//      "MOV %0, #1\n"
//      : "=r" (key)
//      );
//
  return 0;
}
//  __asm__( 
//  int joe=1234, fred;
//"  mov %1,%%eax\n"
//"  add $2,%%eax\n"
//"  mov %%eax,%0\n"
//:"=r" (fred) /* %0: Output variable list */
//:"r" (joe) /* %1: Input variable list */
//:"%eax" /* Overwritten registers ("Clobber list") */
//  );
//  return fred;


int main (int argc, char *argv[]) {
  int i_fd, o_fd, res;
  char *ifile, *ofile, *ofile_name;
  struct stat sb;
  uint8_t key;
  
  if (argc != 3) {
    printf("Usage: ./%s <filename> <8bit-key>\n", __FILE__);
    exit(1);
  }

  key = atoi(argv[2]);
  i_fd = open(argv[1], O_RDONLY);
  if (i_fd == -1) {
    printf("Could not open %s\n", argv[1]);
    exit(1);
  }
  ofile_name = malloc(strlen(argv[1]) + strlen(".encrypted")); // NOTE: null termination?
  sprintf(ofile_name, "%s.encrypted", argv[1]);
  o_fd = open(ofile_name,O_CREAT | O_RDWR | O_TRUNC, 0666);
  if (o_fd == -1) {
    printf("Could not open encrypted\n");
    exit(1);
  }

  if (fstat(i_fd, &sb) == -1) {
    printf("fstat failed\n");
    exit(1);
  }
  // TODO this looks like a dirty hack, (expanding the new file so that writing to the mapped file works)
  lseek(o_fd, sb.st_size-1 , SEEK_SET);
  write(o_fd, "", 1);

  ifile = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, i_fd, 0);
  if (ifile == MAP_FAILED) {
    printf("mmap() failed\n");
    exit(1);
  }
  ofile = mmap(NULL, sb.st_size, PROT_WRITE, MAP_SHARED, o_fd, 0);
  if (ofile == MAP_FAILED) {
    printf("mmap() failed\n");
    exit(1);
  }

  res = my_encrypt(ifile, &sb, ofile, key);
  if (res) {
    printf("my_encrypt() failed\n");
    return res;
  }

cleanup:
  if (munmap(ifile, sb.st_size)== -1) {
    printf("munmap() failed\n");
    exit(1);
  }
  if (munmap(ofile, sb.st_size)== -1) {
    printf("munmap() failed\n");
    exit(1);
  }

  
  return 0;
}
