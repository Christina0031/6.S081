#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
  int p[2], temp[2];
  pipe(p);
  int hasNeighbor = 1;
  if (argc != 1) {
    fprintf(2, "usage: primes\n");
    exit(1);
  }

  if (fork() == 0) {
    while (hasNeighbor) {
      pipe(temp);
      hasNeighbor = 0;
      int first = 0, n = 0;
      read(p[0], (char*)&first, 4);  // need to check return value
      printf("prime %d\n", first);
      close(p[1]);
      while (read(p[0], (char*)&n, 4)) {
        if (n % first != 0) {
          hasNeighbor = 1;
          write(temp[1], (char*)&n, 4);
        }
      }
      close(p[0]);
      p[0] = temp[0];
      p[1] = temp[1];
    }
    close(p[0]);
    close(p[1]);
  } else {
    for (int i = 2; i <= 35; i++) {
      write(p[1], (char*)&i, 4);
    }
    close(p[0]);
    close(p[1]);
    wait(0);
  }
  exit(0);
}
