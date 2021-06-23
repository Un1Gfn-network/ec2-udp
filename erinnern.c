/*

source ip.bashrc
gcc -std=gnu11 -Wall -Wextra -DIP=\"$IP\" -DPORT=$PORT -o erinnern.out erinnern.c

*/

#include <assert.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// ip(7)
#include <netinet/in.h>
// #include <netinet/ip.h> /* superset of previous */

#include <arpa/inet.h> // inet_aton()

#define SZ 1024

static int sockfd=-1;

struct sockaddr_in local_server_addr={};

static unsigned char buf[SZ]={};
static size_t buflen=0;

static void socket2(){
  static_assert(IPPROTO_UDP==17);
  sockfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP/*ip(7)*/);
  // sockfd=socket(AF_INET,SOCK_DGRAM,0/*ip(7)*/);
  assert(sockfd>=3);
}

// local_server_addr <- 127.0.0.1:1080
void lsa(){
  local_server_addr=(struct sockaddr_in){
    .sin_family=AF_INET,
    .sin_port=htons(1080),
    .sin_addr.s_addr=INADDR_LOOPBACK
  };
  assert(1==inet_aton("127.0.0.1",&(local_server_addr.sin_addr)));
  assert(local_server_addr.sin_addr.s_addr==htonl(INADDR_LOOPBACK)/*ip(7)*/);
}

static void buf_clear(){
  bzero(buf,SZ);
  buflen=0;
}

static void buf_wrap(const char *message){

  assert(buflen==0);
  for(int i=0;i<SZ;++i)
    assert(buf[i]=='\0');

  #define i buflen

  // RSV
  assert(i==0);
  buf[i]=0x00;
  buf[i+1]=0x00;
  i+=2;

  // FRAG
  // X'00' ... standalone
  assert(i==2);
  buf[i]=0x00;
  i+=1;

  // ATYP
  assert(i==3);
  buf[i]=0x01;
  i+=1;

  // DST.ADDR
  // ATYP ... X'01' ... version-4 IP ... length of 4 octets (4 8-bit) (4 bytes) (32bit)
  assert(i==4);
  assert(1==inet_aton(IP,(struct in_addr*)&(buf[i])));
  static_assert(sizeof(struct in_addr)==4);
  static_assert(sizeof(in_addr_t)==4);
  static_assert(sizeof(uint32_t)==4);
  i+=4;

  // DST.PORT
  // uint16_t htons(uint16_t hostshort);
  assert(i==8);
  *((uint16_t*)(&(buf[i])))=htons(PORT);
  static_assert(sizeof(uint16_t)==2);
  i+=2;

  // DATA
  assert(i==10);
  strcpy((char*)(&(buf[i])),message);

  i+=strlen(message);

  #undef i

}

static void sendto2(){
  assert((long long)buflen==(long long)sendto(
    sockfd,
    buf,
    buflen,
    MSG_CONFIRM,
    (const struct sockaddr*)(&local_server_addr),
    sizeof(local_server_addr)
  ));
}

int main(){

  buf_clear();
  buf_wrap("apple tree\n");

  socket2();

  lsa();

  sendto2();

  close(sockfd);

  return 0;

}
