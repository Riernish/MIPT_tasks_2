#include "my_server.h"

int check_buffer(const char* buffer);

int main() {
    int sk, ret;

    sk = socket(AF_INET, SOCK_DGRAM, 0);
    if (sk < 0) {
        perror("Unable to create socket");
        return 1;
    }
    struct in_addr in_ad = { inet_addr (MY_IP )};
    struct sockaddr_in name = { AF_INET, PORT, in_ad };

    struct sockaddr* name_ = (struct sockaddr*)&name;
    socklen_t sock_len = sizeof (struct sockaddr_in);




    ret = bind(sk, name_,  sock_len);
    if (ret < 0) {
        perror("Unable to bind socket");
        close(sk);
        return 1;
    }

    while(1) {

        char buffer[BUFSZ] = {0};

        ret = recvfrom(sk , buffer , BUFSZ , 0 , name_ , &sock_len);
        if (ret == -1) {
            perror("Unable to read client\n");
            break;
        }

        if (strcmp(buffer, "CLOSE_SERVER") == 0) {

            break;
        }
       if (check_buffer(buffer) == -1)
           break;

    }
    close(sk);


    return 0;
}
int check_buffer(const char* buffer) {
    int err = 0;
    if (strcmp (buffer , "ls") == 0) {
        pid_t pd = fork();
        if (pd == 0) {
            execlp("ls", "ls", NULL);
            fflush(stdout);
        }
    } else if (buffer[0] == 'c' && buffer[1] == 'd') {

        if (buffer[2] == ' ')
            err = chdir(buffer + 3);
        else if (buffer[2] == '\0')
            err = chdir("/");
        else
            err = -1;


        if (err == -1) {
            printf("Can't do this with directories!\n");
        }
    } else
        printf ("There is no such command: %s\n", buffer);

    return 0;
}
