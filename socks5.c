#include <assert.h>
#include <string.h>

#include <arpa/inet.h> // inet_aton

#include "./socks5.h"

size_t socks5_udp_wrap(char *const dest,const size_t maxlen,const char *const s,const char *const ip,const uint16_t port){

  assert(dest[0]=='\0');
  assert(maxlen>=1);
  assert(0==memcmp(dest,dest+1,maxlen-1));

  RSV(dest)=0x0000;
  FRAG(dest)=0;
  ATYP(dest)=0x01;
  assert(1==inet_aton(ip,DST_ADDR(dest)));
  DST_PORT(dest)=htons(port);

  // Safety
  const size_t l=strnlen(s,maxlen); // excluding the terminating null byte
  const size_t r=SOCKS5_UDP_REQ_HEADER_LEN+l+1;
  assert( 1<=l && l<=r && r<=maxlen );
  strcpy(DATA(dest),s);
  return r;

}
