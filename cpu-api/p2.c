#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  printf("hello world (pid:%d)\n", (int)getpid());
  pid_t rc = fork();
  if (rc < 0) {
    exit(1); // fork failed
  }
  if (rc == 0) {
    // child (new process)
    printf("hello, I am child (pid:%d)\n", (int)getpid());
    sleep(1);
  } else {
    // parent goes down this path (original process)
    pid_t wc = wait(NULL);
    printf("hello, I am parent of %d (wc:%d) (pid:%d)\n", rc, wc,
           (int)getpid());
  }
  return 0;
}
