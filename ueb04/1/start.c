#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdint.h>

#define NICESEST_PRIO 19

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    perror("No executable command was passed");
    return -1;
  }

  // Creating child process;
  pid_t ch_pid = fork();

  if (ch_pid == 0)
  {
    setpriority(PRIO_PROCESS, ch_pid, NICESEST_PRIO);
    // execvp allows array of arguments compared to exec family library;
    int returnCode = execvp(argv[1], &argv[1]);
    sleep(1);
    exit(returnCode);
  }

  int status = 0;
  waitpid(ch_pid, &status, 0);
  printf("CHILD PROCESS ID = %d\n", ch_pid);
  printf("CHILD PROCESS RETURN CODE = %d\n", WEXITSTATUS(status));

  if (WIFEXITED(status))
  {
    printf("EXIT STATUS = %d\n", WEXITSTATUS(status));
  }
  else if (WIFSIGNALED(status))
  {
    printf("SIGNAL KILL = %d\n", WTERMSIG(status));
  }
  else if (WIFSTOPPED(status))
  {
    printf("SIGNAL STOP = %d\n", WSTOPSIG(status));
  }
  else if (WIFCONTINUED(status))
  {
    printf("CONTINUE\n");
  }
}