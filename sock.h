#pragma once

#include <stdbool.h>
#include <arpa/inet.h> // uint16_t

#define SZ 1024

extern int sockfd;

// extern char sendbuf[SZ];
// extern size_t sendbuflen;

void bind2(const uint16_t hostshort);

void recvfrom2(struct sockaddr_in *const);
