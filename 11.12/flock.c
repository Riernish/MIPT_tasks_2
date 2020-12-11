#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

void print_lock(struct flock* f, char* name) {
    printf("NAME %s\n", name);
    printf("TYPE %d\n", f->l_type);
    printf("WHENCE %d\n", f->l_whence);
    printf("START %ld\n", f->l_start);
    printf("LEN %ld\n", f->l_len);
    printf("PID %d\n", f->l_pid);
}

int main(int argc, char** argv) {
    if (argc != 2 ) {

        fprintf(stderr, "Nekorrektnoe kalichestvo argumentav\n");
        exit(228);

    }
    struct flock f = {0};
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "%s", strerror(errno));
        exit(322);
    }  
    int ret = 1;
    f.l_type = F_RDLCK;
    f.l_whence = SEEK_CUR;
    while( ret >= 0 ) {
        ret = fcntl(fd, F_GETLK, &f);
        if (ret < 0) {
            fprintf(stderr, "%s", strerror(errno));
            exit(1448);
        }
        print_lock(&f, argv[1]);
    }
    close(fd);
    return 0;
}
