// #include <sys/socket.h>
// #include <netinet/in.h>

#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "./secret.h"
#include "./sock.h"

struct sockaddr_in router_addr={};

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
  recvfrom2(&router_addr);
  printf("from %s:%u\n",inet_ntoa(router_addr.sin_addr),ntohs(router_addr.sin_port));

  // Beta
  // sendto_direct("\xce\xb2");

  // Gamma
  // recvfrom2();

  // sleep(1);

  // Delta (fail)
  // sendto_direct("\xce\xb4");

  close(sockfd);

}
