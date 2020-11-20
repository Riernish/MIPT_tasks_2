
#include <stdio.h>
#include <sys/inotify.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv) {

	if (argc != 2) {

		perror("Paramtrov ne 1\n");
		exit(228);
        }
	
	int notify = inotify_init();
	if (notify < 0) {

		perror(strerror(errno));
		exit(322);

	}
	int mask = IN_CREATE | IN_DELETE | IN_MOVE_SELF;
	int watcher = inotify_add_watch(notify, argv[1], mask);

	if (watcher < 0) {

		perror(strerror(errno));
		exit(69);

	}

	char buf[4096] = {};
	while(1) {

		int check_rd = read(notify, buf, 4096);
		if (check_rd) {
			struct inotify_event* event = (struct inotify_event*) buf;
			printf("Dir: %s ", event -> name);
			if (event -> mask & IN_CREATE)
				printf("EVENT CREATED \n");
			else if (event -> mask & IN_DELETE)
				printf("EVENT DELETED\n");
			else if (event -> mask & IN_MOVE_SELF)
				printf("EVENT MOVIN\n");
		}
		else {
			perror(strerror(errno));
			exit(1337);

		}

	}
	close(notify);


	return 0;
}
