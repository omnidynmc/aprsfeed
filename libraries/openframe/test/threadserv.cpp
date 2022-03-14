#include <cassert>
#include <exception>
#include <iostream>
#include <new>
#include <string>

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <readline/readline.h>

#include <openframe/openframe.h>

int main(int argc, char **argv) {
  openframe::Thread::Socket::Server *serv = new openframe::Thread::Socket::Server(10152, 1024, 3);

  serv->start();

  char *input = readline("wait> ");
  if (input) free(input);

  serv->stop();

  delete serv;
  return 0;
} // main
