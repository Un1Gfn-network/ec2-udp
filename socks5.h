// Ipv4 only

#pragma once

#include <stdint.h> // uintN_t
#include <netinet/in.h> // struct in_addr

static_assert(4==sizeof(struct in_addr));

// UDP request header fields
// https://datatracker.ietf.org/doc/html/rfc1928#section-7
#define RSV(A)          (*((uint16_t*)((uint8_t*)(A))))          // assert(RSV(A)==0x0000);
#define FRAG(A)                     (*((uint8_t*)(A)+2))         // assert(FRAG(A)==0);
#define ATYP(A)                     (*((uint8_t*)(A)+2+1))       // assert(ATYP(A)==0x01);
#define DST_ADDR(A) ((struct in_addr*)((uint8_t*)(A)+2+1+1))     // inet_ntoa(*DST_ADDR(A)); // assert(1==inet_aton(s,DST_ADDR(A)));
#define DST_PORT(A)     (*((uint16_t*)((uint8_t*)(A)+2+1+1+4)))  // ntohs(DST_PORT(A));
#define DATA(A)                         (((char*)(A)+2+1+1+4+2)) // puts(DST_DATA(A));
#define SOCKS5_UDP_REQ_HEADER_LEN (2+1+1+4+2)

size_t socks5_udp_wrap(char *const,const size_t,const char *const,const char *const,const uint16_t);
