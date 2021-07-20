// Ipv4 only

#pragma once

#include <stdint.h> // uintN_t
#include <netinet/in.h> // struct in_addr

static_assert(4==sizeof(struct in_addr));

// http://c-faq.com/struct/align.esr.html
// As a very drastic measure, you can declare all members as bit-fields
struct socks5udphdr{
  uint16_t rsv;            // 2-byte
  uint8_t frag;            // 1-byte
  uint8_t atyp;            // 1-byte
  struct in_addr dst_addr; // 4-byte
  uint16_t dst_port;       // 2-byte
  char data[];             // https://en.wikipedia.org/wiki/Flexible_array_member
} __attribute__((__packed__));
static_assert(2+1+1+4+2==sizeof(struct socks5udphdr));
size_t socksudphdr_write(struct socks5udphdr *const, const char *const, const uint16_t, const char *const);
void socksudphdr_verify(const struct socks5udphdr *const);
