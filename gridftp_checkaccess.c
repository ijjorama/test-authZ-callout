#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include "gridftp_checkaccess.h"

#define NOHOST "nohost"

int checkaccess(const char* authdbprog, const char* authdbfile, const char* user, const char* operation, const char* path) {
  
  int status;
  pid_t pid;
  
  switch (pid = fork()) {
    
    case -1:
      status = -1;
      break;
      
    case 0:
      /*
       * We don't want any output from the execl'ed program, so close stdout and stderr fds
       */
      
      close(1); close(2);

      execl(authdbprog, authdbprog, "-s", "-c", authdbfile /* "/dev/null" */, user, NOHOST, operation, path, NULL);
      _exit(EXIT_FAILURE);
      
    default: 
      if (waitpid(pid, &status, 0) != pid) {
        status = -1;
      }
      if (WIFEXITED(status)) {
        status = WEXITSTATUS(status);
      } else {
        status = -1;
      }
        
  }
  return status;
}

#ifdef GRIDFTP_CHECKACCESS_MAIN
int main(int argc, char **argv) {
  
  char* authdbprog;
  char* authdbfile;
  char* user;
  char* operation;
  char* path;
  
  if (argc != 6) {
    
    fprintf(stderr, "Usage: %s %s %s user operation path\n", argv[0], 
      "/usr/bin/xrdacctest", "/etc/grid-security/authdb");                                                    
    exit(-1);

  }
  
  authdbprog = argv[1];
  authdbfile = argv[2];
  
  user = argv[3];
  operation = argv[4];
  path = argv[5];
  
  exit(checkaccess(authdbprog, authdbfile, user, operation, path));
  
}
#endif