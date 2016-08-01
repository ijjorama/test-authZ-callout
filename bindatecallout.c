#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define AUTHZPROG "/usr/bin/xrdacctest"
#define NOHOST "nohost"

#define SHELL "/bin/sh"

int checkaccess(const char* authdbprog, const char* authdbfile, const char* user, const char* operation, const char* path) {
  
  int status;
  pid_t pid;
  
  switch (pid = fork()) {
    
    case -1:
      status = -1;
      break;
      
    case 0:    
//      execl(SHELL, SHELL, "-c", "/bin/date", NULL);   // This works...

      execl("/bin/date", "/bin/date", NULL);   // This works...
      
      
      fprintf(stderr, "Child error: should not get here!\n");

      _exit(EXIT_FAILURE);
      
    default: 
      if (waitpid(pid, &status, 0) != pid) {
        fprintf(stderr, "Parent error: received wrong PID in waitpid() call\n");
        status = -1;
      } else {
        status = 0;
      }
        
  }
  return status;
}

int main(int argc, char *argv) {
  
  char* authdbprog;
  char* authdbfile;
  char* user;
  char* operation;
  char* path;
  
  exit(checkaccess(authdbprog, authdbfile, user, operation, path));
  
}