#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// ip(7)
// #include <netinet/ip.h>
#include <netinet/in.h> // subset of <netinet/ip.h>

#include <arpa/inet.h> // inet_aton()

#include "./secret.h"
#include "./socket2.h"
#include "./socks5.h"

static struct sockaddr_in local_server_addr={};

static char sendbuf[SZ]={};
static size_t sendbuflen=0;

// udp.dstport <- local_server_addr <- 127.0.0.1:1080
static void lsa(){
  local_server_addr=(struct sockaddr_in){
    .sin_family=AF_INET,
    .sin_port=htons(1080),
    .sin_addr.s_addr=INADDR_LOOPBACK
  };
  assert(1==inet_aton("127.0.0.1",&(local_server_addr.sin_addr)));
  assert(local_server_addr.sin_addr.s_addr==htonl(INADDR_LOOPBACK)/*ip(7)*/);
}

// Only a tiny bit similar to sendto_direct() in udp_server.c
static void sendto_socks5(const char *const message){  
  bzero(sendbuf,SZ);
  sendbuflen=0;
  sendbuflen=socks5_udp_wrap(sendbuf,SZ,message,IP,UDPORT);
  assert((long long)sendbuflen==(long long)sendto(
    sockfd,
    sendbuf,
    sendbuflen,
    MSG_CONFIRM,
    (const struct sockaddr*)(&local_server_addr),
    sizeof(local_server_addr)
  ));
  printf("sent wrapped \"%s\"\n",message);
}

static void recvfrom_socks5(){

  socklen_t addrlen=sizeof(struct sockaddr_in);
  struct sockaddr_in t={};
  unsigned char recvbuf[SZ]={};

  const ssize_t r=recvfrom(sockfd,recvbuf,SZ,MSG_WAITALL,(struct sockaddr*)&t,&addrlen);
  assert(1<=r&&r<=SZ-1);

  assert(addrlen==sizeof(struct sockaddr_in));
  assert(0==memcmp(&t,&local_server_addr,sizeof(struct sockaddr_in)));

  assert(RSV(recvbuf)==0x0000);
  assert(FRAG(recvbuf)==0);
  assert(ATYP(recvbuf)==0x01);
  assert((long long)r==(long long)strlen(DATA(recvbuf))+SOCKS5_UDP_REQ_HEADER_LEN);
  // printf("received \"%s\"\n",DATA(recvbuf));
  printf("received wrapped \"%s\" ",DATA(recvbuf));
  printf("from %s:%u\n",inet_ntoa(*DST_ADDR(recvbuf)),ntohs(DST_PORT(recvbuf)));

}

int main(const int argc,const char *const *const argv){

  assert(argc==1);
  assert(argv[1]==NULL);

  // 0 is ephemeral
  // https://stackoverflow.com/q/1075399#comment12066805_1077305
  bind2(0);
  lsa();

  // Alpha
  // printf "..." | hexdump
  // sendto_direct("\xce\xb1");
  sendto_socks5("\xce\xb1");

  // Beta
  recvfrom_socks5();

  // Gamma
  sendto_socks5("\xce\xb3");

  // Delta (loop)
  for(;;)
    recvfrom_socks5();

  close(sockfd);

  return 0;

}
