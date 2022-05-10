//#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

typedef ssize_t (*real_read_t)(int, void *, size_t);

// retrive original symbol from dynamic linker using <dlfcn.h> dlsym
// function
ssize_t real_read(int fd, void *data, size_t size) {

  // want the following call to the actual read:
  // return read(fd, *data, size)

  // to get the "real" read func
  // RTLD_NEXT gets next symbol called "read"
  // RTLD_DEFAULT loads the default symbol in the global scope (which is
  // our
  // malicious read) dlsym(RTLD_NEXT, "read")
  // dlsym returns struct, variable or func as a void *

  real_read_t clib_read = (real_read_t)dlsym(RTLD_NEXT, "read");
  return clib_read(fd, data, size);
}

// define the read function with the exact same signature
ssize_t read(int fd, void *data, size_t size) {
  ssize_t amount_read;

  amount_read = real_read(fd, data, size);

  // our wrapper code (to write what we read to stdout)
  // fwrite(data, sizeof(char), amount_read, stdout);
  printf("MALICIOUS CODE\n");

  return amount_read;
}
