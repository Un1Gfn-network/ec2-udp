// #include <sys/socket.h>
// #include <netinet/in.h>

#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "./secret.h"
#include "./socket2.h"

struct sockaddr_in router={};

// Similar to recvfrom_socks5() in erinnern.c
void recvfrom_direct(){
  unsigned char recvbuf[SZ]={};
  socklen_t addrlen=sizeof(struct sockaddr_in);
  const ssize_t r=recvfrom(sockfd,recvbuf,SZ,MSG_WAITALL,(struct sockaddr*)(&router),&addrlen);
  assert(1<=r&&r<=SZ-1);
  assert(addrlen==sizeof(struct sockaddr_in));
  // printf("received \"%s\"\n",recvbuf);
  printf("received \"%s\" ",recvbuf);
  printf("from %s:%u\n",inet_ntoa(router.sin_addr),ntohs(router.sin_port));
}

// Similar to sendto_socks5() in erinnern.c
static void sendto_direct(const char *const msg){
  const size_t l=strlen(msg);
  assert((long long)l==(long long)sendto(
    sockfd,
    msg,
    l,
    MSG_CONFIRM,
    (const struct sockaddr*)(&router),
    sizeof(struct sockaddr_in)
  ));
  printf("sent \"%s\"\n",msg);
}

int main(const int argc,const char **argv){

  bind2(UDPORT);

  // Alpha
  recvfrom_direct();
  
  // Beta
  sendto_direct("\xce\xb2");

  // Gamma
  recvfrom_direct();

  unsigned int sec=0;
  assert(argc==2);
  assert(1==sscanf(argv[1],"%u",&sec));
  assert(1<=sec&&sec<=90);
  printf("sleeping for %u seconds ...",sec);fflush(stdout);
  sleep(sec);
  puts("");

  // Delta (fail)
  sendto_direct("\xce\xb4");

  close(sockfd);

}
