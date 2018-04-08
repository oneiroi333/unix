#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

int
main(int argc, char *argv[])
{
	struct stat sbuf;

	if (argc != 2) {
		printf("Usage: %s <pathname>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (stat(argv[1], &sbuf) == -1) {
		perror("stat");
		exit(EXIT_FAILURE);
	}

	switch(sbuf.st_mode & S_IFMT) {
	case S_IFBLK:
		printf("block device\n");
		break;
	case S_IFCHR:
		printf("character device\n");
		break;
	case S_IFDIR:
		printf("directory\n");
		break;
	case S_IFIFO:
		printf("FIFO/pipe\n");
		break;
	case S_IFLNK:
		printf("symlink\n");
		break;
	case S_IFREG:
		printf("regular file\n");
		break;
	case S_IFSOCK:
		printf("socket\n");
		break;
	default:
		printf("unknown\n");
	}

	exit(EXIT_SUCCESS);
}
