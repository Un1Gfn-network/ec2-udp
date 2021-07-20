#include <assert.h>
#include <stdalign.h> // alignof()
#include <stddef.h>
#include <string.h>

#include <arpa/inet.h> // inet_aton

#include "./socks5.h"

size_t socksudphdr_write(struct socks5udphdr *const h, const char *const ip, const uint16_t port, const char *const data){

  h->rsv=0x0000;
  h->frag=0;
  h->atyp=0x01;

  // https://stackoverflow.com/q/8568432/is-gccs-attribute-packed-pragma-pack-unsafe
  // https://en.wikipedia.org/wiki/Bus_error#Unaligned_access
  #ifdef __x86_64__
    static_assert(offsetof(struct socks5udphdr,dst_addr)%alignof(struct in_addr)==0);
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Waddress-of-packed-member"
    assert(1==inet_aton(ip,&(h->dst_addr)));
    #pragma GCC diagnostic pop
  #else
    #error ""
  #endif

  h->dst_port=htons(port);
  strcpy(h->data,data);

  return (sizeof(struct socks5udphdr)+strlen(data));

}

void socksudphdr_verify(const struct socks5udphdr *const h){
  assert(0x0000==h->rsv);
  assert(0==h->frag);
  assert(0x01==h->atyp);
}
