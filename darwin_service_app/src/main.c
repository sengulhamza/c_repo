#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

static pid_t pid, sid;

void daemonize()
{

    /* Fork off the parent process */
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    /* If we got a good PID, then we can exit the parent process. */
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    /* Change the file mode mask */
    umask(0);

    /* Open any logs here */
    openlog("mydaemon", LOG_PID | LOG_CONS, LOG_DAEMON);

    /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0) {
        syslog(LOG_ERR, "Failed to create new SID");
        exit(EXIT_FAILURE);
    }

    /* Change the current working directory */
    if ((chdir("/")) < 0) {
        syslog(LOG_ERR, "Failed to change working directory to /");
        exit(EXIT_FAILURE);
    }

    /* Close out the standard file descriptors */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

int main(int argc, char *argv[])
{
    daemonize();
    /* Your daemon code goes here */
    while (1) {
        syslog(LOG_INFO, "Daemon running");
        sleep(30);
    }

    closelog();
    exit(EXIT_SUCCESS);
}
