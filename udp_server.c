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

int main(const int argc,const char *const *const argv){

  assert(argc==1);
  assert(argv[1]==NULL);

  bind2(UDPORT);

  // Alpha
  recvfrom_direct();
  
  // Beta
  sendto_direct("\xce\xb2");

  // Gamma
  recvfrom_direct();

  // Delta (loop)
  for(unsigned int u=1;;u*=2){
    printf("sleeping for %u seconds ...",u);fflush(stdout);
    sleep(u);
    puts("");
    char s[SZ]={};
    sprintf(s,"%s%u","\xce\xb4",u);
    sendto_direct(s);
    // puts(s);
  }

  close(sockfd);

}
