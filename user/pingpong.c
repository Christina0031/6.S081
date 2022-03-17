#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char* argv[])
{
  int p[2];
  char* byte;
  byte = " ";
  int pid;
  pipe(p);

  if (argc != 1) {
    fprintf(2, "usage: pingpong\n");
    exit(1);
  }

  if (fork() == 0) {
    read(p[0], byte, 1);
    pid = getpid();
    printf("%d: received ping\n", pid);
    write(p[1], byte, 1);
    close(p[0]);
    close(p[1]);
  }
  else {
    write(p[1], byte, 1);
    wait(0);
    read(p[0], byte, 1);
    pid = getpid();
    printf("%d: received pong\n", pid);
    close(p[0]);
    close(p[1]);
  }

  exit(0);
}
