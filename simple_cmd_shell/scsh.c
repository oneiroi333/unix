#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFSIZE 256

int
main(void)
{
	int pid, status;
	char buf[BUFFSIZE];

	printf("%% ");
	while (fgets(buf, sizeof(buf), stdin) != NULL) {
		if (buf[strlen(buf) - 1] == '\n') {
			buf[strlen(buf) - 1] = '\0';
		}

		if ((pid = fork()) < 0) {
			fprintf(stderr, "Error: fork: %s\n", strerror(errno));
		} else if (pid == 0) { /* In child process */
			execlp(buf, buf, (char *)0);
			/* The next lines only get executed if execlp fails */
			fprintf(stderr, "Error: execlp: %s\n", strerror(errno));
			_exit(EXIT_FAILURE);
		}
		/* In parent process */
		if ((pid = waitpid(pid, &status, 0)) < 0) {
			fprintf(stderr, "Error: execlp: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		printf("%% ");
	}

	exit(EXIT_SUCCESS);
}
