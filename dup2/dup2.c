#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <limits.h>

#define FILE_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)
#define BUFF_SIZE 4096

int my_dup2(int fd1, int fd2);

int
main(void)
{
	int fd1, fd2, i;
	ssize_t cnt;
	char *file_name = "test.txt";
	char buff[BUFF_SIZE];

	fd1 = open(file_name, O_RDWR | O_CREAT, FILE_PERMS);
	if (fd1 == -1) {
		fprintf(stderr, "Error: open file: %s: ", file_name);
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("File descriptor: fd1 = %d\n", fd1);
	printf("Writing \"Unix is awesome!\" to file: %s\n", file_name);

	dprintf(fd1, "Unix is awesome!\n");

#if 0
	/* Force sync */
	if (fsync(fd1) == -1) {
		fprintf(stderr, "Error: sync file: %s: ", file_name);
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
#endif

	printf("Read file with fd1:\n");
	lseek(fd1, 0, SEEK_SET);
	while ((cnt = read(fd1, buff, BUFF_SIZE)) > 0) {
		i = 0;
		while (cnt--) {
			fputc(buff[i++], stdout);
		}
	}
	if (cnt == -1) {
		fprintf(stderr, "Error: read file: %s: ", file_name);
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("my_dup2(fd1, 9)\n");
	fd2 = my_dup2(fd1, 9);
	printf("File descriptor: fd2 = %d\n", fd2);
	printf("Read file with fd2:\n");
	lseek(fd1, 0, SEEK_SET);
	while ((cnt = read(fd2, buff, BUFF_SIZE)) > 0) {
		i = 0;
		while (cnt--) {
			fputc(buff[i++], stdout);
		}
	}
	if (cnt == -1) {
		fprintf(stderr, "Error: read file: %s: ", file_name);
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}

int
my_dup2(int fd1, int fd2)
{
	int fd_tab[fd2];
	int fd, i;

	for (i = 0; i < fd2; ++i) {
		fd_tab[i] = 0;
	}
	/* dup as long as we get the requested fd */
	while ((fd = dup(fd1)) != fd2) {
		fd_tab[fd] = 1;
	}
	/* Close the unused fd */
	for (i = 0; i < fd2; ++i) {
		if (fd_tab[i]) {
			close(i);
		}
	}

	return fd;
}
