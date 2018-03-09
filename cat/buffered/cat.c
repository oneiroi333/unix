#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
	int c;

	while ((c = getc(stdin)) != EOF) {
		if (putc(c, stdout) == EOF) {
			fprintf(stderr, "Error: write\n");
			exit(EXIT_FAILURE);
		}
	}

	if (ferror(stdin)) {
		fprintf(stderr, "Error: read\n");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
