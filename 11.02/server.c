#include "my_server.h"

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


        printf("%s\n", buffer);
        buffer[0] = '\0';


    }
    close(sk);


    return 0;
}
