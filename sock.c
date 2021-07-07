#include <assert.h>
#include <stdio.h>
#include <sys/socket.h>

#include "./sock.h"

int sockfd=-1;

// char sendbuf[SZ]={};
// size_t sendbuflen=0;

static void getsockname2(){
  struct sockaddr_in sin={};
  socklen_t len=sizeof(struct sockaddr_in);
  assert(0==getsockname(sockfd,(struct sockaddr*)&sin,&len));
  assert(len==sizeof(struct sockaddr_in));
  printf("udp.srcport %d\n",ntohs(sin.sin_port));
}

void bind2(const uint16_t hostshort){
  static_assert(IPPROTO_UDP==17);
  sockfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP/*ip(7)*/);
  // sockfd=socket(AF_INET,SOCK_DGRAM,0/*ip(7)*/);
  assert(sockfd>=3);
  assert(0==bind(sockfd,(const struct sockaddr*)(&((struct sockaddr_in){
    .sin_family=AF_INET,
    .sin_port=htons(hostshort),
    .sin_addr.s_addr=htonl(INADDR_ANY)
  })),sizeof(struct sockaddr_in)));
  getsockname2();
}

// Similar to ? in ?
void recvfrom2(struct sockaddr_in *const sin){
  unsigned char recvbuf[SZ]={};
  socklen_t addrlen=sizeof(struct sockaddr_in);
  const ssize_t r=recvfrom(sockfd,recvbuf,SZ,MSG_WAITALL,(struct sockaddr*)sin,&addrlen);
  assert(1<=r&&r<=SZ-1);
  assert(addrlen==sizeof(struct sockaddr_in));
  printf("received: %s\n",recvbuf);
}
