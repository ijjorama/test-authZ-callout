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
      fprintf(stderr, "Parent error: PID is -1.\n");
      status = -1;
      break;
      
    case 0:
//      execl(AUTHZPROG, AUTHZPROG, "-s", "-c", "/dev/null", user, NOHOST, operation, path, NULL);
//      fprintf(stdout, "In child now...\n");
      
//      execl(SHELL, SHELL, "-c", "/bin/date", NULL);   // This works...

      execl("/bin/date", "/bin/date", NULL);   // This works...
      
      
      fprintf(stderr, "Child error: should not get here!\n");

      _exit(EXIT_FAILURE);
      
    default: 
//      fprintf(stdout, "Child PID = %d\n", pid);
      if (waitpid(pid, &status, 0) != pid) {
        fprintf(stderr, "Parent error: received wrong PID in waitpid() call\n");
        status = -1;
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
  
  exit(!checkaccess(authdbprog, authdbfile, user, operation, path));
  
}