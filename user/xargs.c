#include "kernel/types.h"
#include "kernel/param.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
  char ch;
  char buf[512];
  char* args[MAXARG];
  int index = 0, i = 0;
  if (argc <= 1) {
    fprintf(2, "usage: xargs [command [initial-arguments]]\n");
    exit(1);
  }

  for (i = 0; i < argc - 1; i++) {
    args[i] = argv[i + 1];
  }

  index = 0;
  while (read(0, &ch, 1) > 0) {
    if (ch != '\n') {
      buf[index] = ch;
      index++;
    } else {
      buf[index] = 0;
      args[i] = buf;
      args[i + 1] = 0;
      if (fork() == 0) {
        exec(args[0], args);
      }
      wait(0);
      index = 0;
    }
  }
  exit(0);
}
