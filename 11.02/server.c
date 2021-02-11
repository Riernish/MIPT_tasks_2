int main() {
        int sk, ret, ret_2;
        struct sockaddr_un name = {0};

        sk = socket(AF_UNIX, SOCK_STREAM, 0);
        if (sk < 0) {
                perror("Unable to create socket");
                return 1;
        }

        name.sun_family = AF_UNIX;
        strncpy(name.sun_path, PATH, sizeof(PATH));

        ret = bind(sk, (struct sockaddr*)&name, sizeof(name));
        if (ret < 0) {
                perror("Unable to create socket");
                close(sk);
                return 1;
        }

        ret = listen(sk, 20);
        if (ret){
                perror("Unable to listen");
                close(sk);
                return 1;
        }

        while(1) {
                int client_sk;
                char buffer[BUFSZ] = {0};

                client_sk = accept (sk, NULL, NULL);
                if (client_sk < 0) {
                        perror("Unable to accept");
                                               exit(1);
                }

                ret = read(client_sk, buffer, BUFSZ);
                buffer[ret - 1] = '\0';

                if (ret < 0 || ret >= BUFSZ) {
                        printf("Unexpected red error or overflow %d\n", ret);
                        break;

                }
                if (strcmp(buffer, "EXIT") == 0) {

                        close(client_sk);
                        break;
                } else if (strcmp(buffer, "PRINT") == 0) {

                        ret_2 = ret + read(client_sk, buffer, BUFSZ);
                        buffer[ret_2 - 1] = '\0';
                        if (ret_2 < 0 || ret_2 >= BUFSZ) {
                                printf("Unexpected red error or overflow %d\n", ret);
                                buffer[0] = '\0';

                                break;

                        }
                        printf("%s", buffer);
                        buffer[0] = '\0';
                        close(client_sk);
                } else {

                        printf("Unknown command: %s", buffer);
                        buffer[0] = '\0';
                        close(client_sk);

                }
                

                printf("%s\n", buffer);
                buffer[0] = '\0';

                close(client_sk);
        }

        unlink (PATH);
        return 0;
}


