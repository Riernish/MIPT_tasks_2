#include "my_server.h"

#define DUMMY_STR "London is the capital of Great Britain\n"

int main() {

        int sk, ret;
        struct sockaddr_un name = {0};

        sk = socket(AF_UNIX, SOCK_STREAM, 0);
        if (sk < 0) {
                perror("Unable to create socket");
                exit(1);
        }

        name.sun_family = AF_UNIX;
        strncpy(name.sun_path, PATH, sizeof(PATH));

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
        if (strcmp(buffer, "PRINT") == 0) {
                ret = read (STDIN_FILENO, buffer, BUFSZ - 1);
                buffer[ret - 1] = '\0';

                if (ret < 0 || ret >= BUFSZ) {
                        printf("Unexpected red error or overflow %d\n", ret);
                        exit(1);

                }
                ret = write(sk, buffer, BUFSZ - 1);
                if (ret < 0) {
                        perror("Unable to write");
                }


        }

        return 0;
}
