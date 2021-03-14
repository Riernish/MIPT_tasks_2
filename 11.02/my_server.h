#ifndef _myserver_h
#define _myserver_h

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#define PATH "/tmp/mysock"
#define BUFSZ 256
#define MY_ADDRESS "127.0.0.1"

#endif
