// #include <sys/socket.h>
// #include <netinet/in.h>

#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "./secret.h"
#include "./socket2.h"

struct sockaddr_in router_addr={};

// Similar to recvfrom_socks5() in erinnern.c
void recvfrom_direct(struct sockaddr_in *const sin){
  unsigned char recvbuf[SZ]={};
  socklen_t addrlen=sizeof(struct sockaddr_in);
  const ssize_t r=recvfrom(sockfd,recvbuf,SZ,MSG_WAITALL,(struct sockaddr*)sin,&addrlen);
  assert(1<=r&&r<=SZ-1);
  assert(addrlen==sizeof(struct sockaddr_in));
  printf("received: %s\n",recvbuf);
}

// Similar to sendto_socks5() in erinnern.c
static void sendto_direct(const char *const msg){
  const size_t l=strlen(msg);
  assert((long long)l==(long long)sendto(
    sockfd,
    msg,
    l,
    MSG_CONFIRM,
    (const struct sockaddr*)(&router_addr),
    sizeof(struct sockaddr_in)
  ));
  printf("sent: %s\n",msg);
}

int main(){

  bind2(UDPORT);

  // Alpha
  recvfrom_direct(&router_addr);
  printf("from %s:%u\n",inet_ntoa(router_addr.sin_addr),ntohs(router_addr.sin_port));

  // Beta
  sendto_direct("\xce\xb2");

  // Gamma
  // recvfrom_direct();

  // sleep(1);

  // Delta (fail)
  // sendto_direct("\xce\xb4");

  close(sockfd);

}
