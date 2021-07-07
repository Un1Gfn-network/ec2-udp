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
#include "./sock.h"

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

static void buf_wrap(const char *const message){

  assert(sendbuflen==0);
  for(int i=0;i<SZ;++i)
    assert(sendbuf[i]=='\0');

  #define i sendbuflen

  // RSV
  assert(i==0);
  sendbuf[i]=0x00;
  sendbuf[i+1]=0x00;
  i+=2;

  // FRAG
  // X'00' ... standalone
  assert(i==2);
  sendbuf[i]=0x00;
  i+=1;

  // ATYP
  assert(i==3);
  sendbuf[i]=0x01;
  i+=1;

  // DST.ADDR
  // ATYP ... X'01' ... version-4 IP ... length of 4 octets (4 8-bit) (4 bytes) (32bit)
  assert(i==4);
  assert(1==inet_aton(IP,(struct in_addr*)&(sendbuf[i])));
  static_assert(sizeof(struct in_addr)==4);
  static_assert(sizeof(in_addr_t)==4);
  static_assert(sizeof(uint32_t)==4);
  i+=4;

  // DST.PORT
  // uint16_t htons(uint16_t hostshort);
  assert(i==8);
  *((uint16_t*)(&(sendbuf[i])))=htons(UDPORT);
  static_assert(sizeof(uint16_t)==2);
  i+=2;

  // DATA
  assert(i==10);
  strcpy((char*)(&(sendbuf[i])),message);

  i+=strlen(message);

  #undef i

}

// Similar to sendto_direct() in udp_server.c
static void sendto_socks5(const char *const message){  
  bzero(sendbuf,SZ);
  sendbuflen=0;
  buf_wrap(message);
  assert((long long)sendbuflen==(long long)sendto(
    sockfd,
    sendbuf,
    sendbuflen,
    MSG_CONFIRM,
    (const struct sockaddr*)(&local_server_addr),
    sizeof(local_server_addr)
  ));
  printf("sent: %s\n",message);
}

int main(){

  // 0 is ephemeral
  // https://stackoverflow.com/q/1075399#comment12066805_1077305
  bind2(0);
  lsa();

  // Alpha
  // printf "..." | hexdump
  // sendto_direct("\xce\xb1");
  sendto_socks5("\xce\xb1");

  // Beta
  // struct sockaddr_in unk={};
  // recvfrom2(&unk);
  // printf("from %s:%u\n",inet_ntoa(unk.sin_addr),ntohs(unk.sin_port));

  // Gamma
  // sendto_socks5("\xce\xb3");

  // Delta (fail)
  // recvfrom2();

  close(sockfd);

  return 0;

}
