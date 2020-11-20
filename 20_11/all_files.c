#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char** argv) {

        

                DIR* target = opendir(argv[1]);
                if (target == NULL) {

                        fprintf(stderr, "%s", strerror(errno));
               
                }


                struct dirent* files;
                while ((files = readdir(target)) != NULL )
                        printf("%s\n", files -> d_name);
                closedir(target);
        //}

        return 0;

}
