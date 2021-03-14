#include "my_server.h"

#define DUMMY_STR "London is the capital of Great Britain\n"

int main(int argc, char** argv) {
        if (argc < 2) {
            perror("Too few arguments\n");
            exit(1);
        }

        int sk = socket (AF_INET , SOCK_DGRAM , 0);

        char* adress = NULL;
        if (strcmp(argv[1], "self") == 0) {
            adress = MY_ADDRESS;
        }
        else
            adress = argv[1];

        const struct in_addr in_ad = { inet_addr (adress )};
        const struct sockaddr_in name = { AF_INET, PORT, in_ad };
        struct sockaddr* name_ = (struct sockaddr*)&name;
        socklen_t sock_len = sizeof (struct sockaddr_in);
        int ret = 0;


        char buffer[BUFSZ] = {};

        while (strcmp (buffer , "CLOSE_SERVER") != 0)
        {


            if (fgets(buffer, BUFSZ, stdin)== NULL) {
                perror("Ne chitayetsya stroka \n");
                exit(228);
            }

            size_t len = strlen (buffer) - 1;
            buffer[len] = '\0'; //delete last '\n' after fgets

            if (strcmp (buffer , "EXIT") == 0)
                break;


            ret = sendto(sk, buffer, len, 0, name_, sock_len);
            if (ret == -1) {
                perror("Ne mogy pisat'\n");
                exit(228);

            }

        }

        close (sk);
        return 0;
    }
