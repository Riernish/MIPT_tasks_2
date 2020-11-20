
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char** argv) {

        for (int i = 1; i < argc; i++) {

                DIR* target = opendir(argv[i]);
                if (target == NULL) {

                        fprintf(stderr, "%s", strerror(errno));
                        continue;
                }


                struct dirent* files;
                while ((files = readdir(target)) != NULL )
                        printf("%s\n", files -> d_name);
        }

        return 0;

}
