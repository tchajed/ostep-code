#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  pid_t rc = fork();
  if (rc < 0) {
    exit(1); // fork failed
  }
  if (rc == 0) {
    // child: redirect standard output to a file
    int out_fd = open("./p4.output", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    dup2(out_fd, STDOUT_FILENO);

    // now exec "wc"...
    char *myargs[3];
    myargs[0] = strdup("wc");   // program: "wc" (word count)
    myargs[1] = strdup("p4.c"); // argument: file to count
    myargs[2] = NULL;           // marks end of array
    execvp(myargs[0], myargs);  // runs word count
  } else {
    // parent goes down this path (original process)
    pid_t wc = wait(NULL);
    assert(wc >= 0);
  }
  return 0;
}
