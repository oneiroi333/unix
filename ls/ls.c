#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>

int
main(int argc, char *argv[])
{
	DIR *dir;
	struct dirent *dirent;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <directory_name>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if ((dir = opendir(argv[1])) == NULL) {
		fprintf(stderr, "Error: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	while ((dirent = readdir(dir)) != NULL) {
		printf("%s\n", dirent->d_name);
	}

	return EXIT_SUCCESS;
}
