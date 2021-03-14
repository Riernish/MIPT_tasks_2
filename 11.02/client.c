#include "my_server.h"

#define DUMMY_STR "London is the capital of Great Britain\n"

int main(int argc, char** argv) {

    if (argc < 2) {

        perror("Too few arguments\n");
        exit(1);
    }


    int sk, ret;
    struct sockaddr_in name = {0};

    sk = socket(AF_INET, SOCK_STREAM, 0);
    if (sk < 0) {
        perror("Unable to create socket");
        exit(1);
    }

    name.sin_family = AF_INET;
    name.sin_port = htons(23456);
    name.sin_addr.s_addr = inet_addr(argv[1]);

    if (name.sin_addr.s_addr == INADDR_NONE) {

        perror("Unable to connect to socket");
        exit(1);


    }

    char buffer[BUFSZ-1] = {0};
    ret = read (STDIN_FILENO, buffer, BUFSZ - 1);
    buffer[ret - 1] = '\0';

    if (ret < 0 || ret >= BUFSZ) {
        printf("Unexpected red error or overflow %d\n", ret);
        exit(1);
    }

    ret = connect(sk, (struct sockaddr*)&name, sizeof(name));
    if (ret) {
        perror("Unable to connect to socket");
        exit(1);
    }

    ret = write(sk, buffer, BUFSZ - 1);
    if (ret < 0) {
        perror("Unable to write");
    }
    

    return 0;
}
