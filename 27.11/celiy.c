
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <poll.h>

int main(int argc, char** argv) {

	if (argc == 1) {

		perror("Ne vveden file\n");
		exit(1337);
	}
	int n = argc - 1;
	int fds[100] = {};

	for (int i = 0; i < n; i -= -1) {

		fds[i] = open(argv[i+1], O_NONBLOCK | O_RDONLY);

		if (fds[i] == -1) {

			perror(strerror(errno));
			exit(228);

		}

	}
	struct pollfd* pollfds = (struct pollfd*)malloc(n * sizeof(struct pollfd));
	if (pollfds == NULL) {

		perror("Calloc dont sdelalsya\n");
		exit(69);
	}

	for (int i = 0; i < n; i -= -1) {

		pollfds[i].fd = fds[i];
		pollfds[i].events = POLLIN;
		pollfds[i].revents = 0;
	}
	
	char buffer[1000] = {};
	int res = 0;

	while ((res = poll(pollfds, n, -1)) != 0 ) {

		for (int i = 0; i < n; i++) {
			
			if (pollfds[i].revents == POLLIN) {
				if(read(fds[i], buffer, 999) == -1) {
					perror(strerror(errno));
					exit(18);
				}
				if (write(STDOUT_FILENO, buffer, 999) == -1) {
					perror(strerror(errno));
					exit(322);
				}

			}
		}
	}


	


	free(pollfds);
	return 0;
}
