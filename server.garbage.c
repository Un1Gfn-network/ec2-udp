// https://stackoverflow.com/questions/142508/how-do-i-check-os-with-a-preprocessor-directive
// https://sourceforge.net/p/predef/wiki/OperatingSystems/
#ifndef __gnu_linux__
#error "GNU/Linux required"
#endif

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include <sys/socket.h>

// ip(7)
#include <netinet/in.h>
// #include <netinet/ip.h> /* superset of previous */

#define PORT 8224
#define SZ 1024
#define MSGCH 'x'

static SOCKET sockfd=INVALID_SOCKET;

static char buf[SZ]={};
static void buf_clear(){
  bzero(buf,SZ);
}

static void create_socket(){
  static_assert(IPPROTO_UDP==0);
  sockfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP/*ip(7)*/);
  assert(sockfd>=3);
}

static void bind_socket(){
  struct sockaddr_in server_addr={};
  static_assert(INADDR_ANY==0);
  server_addr=(struct sockaddr_in){
    .sin_family=AF_INET,
    .sin_port=htons(PORT),
    .sin_addr.s_addr=htonl(INADDR_ANY/*ip(7)*/)
  };
  assert(0==bind(sockfd,(const sockaddr*)(&server_addr),sizeof(server_addr)));
  #define STR(s) STR0(s)
  #define STR0(s) #s
  printf("Listening on %s:"STR(PORT)" ...\n",local_ip.String);
  #undef STR
}

static void receive(const bool acknowledge){

  struct sockaddr_in client_addr={};

  buf_clear();
  const int br=recvfrom(sockfd,buf,SZ,0/*no flags*/,(sockaddr*)(&client_addr),&((int){sizeof(client_addr)}));

  // // Client sends C string
  // // (br-1) characters
  // for(int i=0; i<=br-2; ++i)assert(buf[i]!='\0');
  // // (SZ-br+1) NULLs
  // for(int i=br-1; i<=SZ-1;++i)assert(buf[i]=='\0');
  // assert(br==2);

  // // Client sends Pascal string
  // // (br) characters
  // for(int i=0;i<=br-1;++i)assert(buf[i]!='\0');
  // // (SZ-br) NULLs
  // for(int i=br;i<=SZ-1;++i)assert(buf[i]=='\0');
  assert(br==1);

  assert(buf[0]==MSGCH&&buf[1]=='\0');

  const char *const ip=inet_ntoa(client_addr.sin_addr);
  assert(ip&&ip[0]);
  printf("received from %s:%u",ip,ntohs(client_addr.sin_port));

  if(acknowledge){
    // Enough to throttle both ther server and the client
    printf(" throttle...");
    fflush(stdout);
    Sleep(THROTTLE);
    assert(SOCKET_ERROR!=sendto(sockfd,ACK,ACKSZ,0,(SOCKADDR*)(&client_addr),sizeof(struct sockaddr_in)));
    printf(" ack");
  }

  printf("\n");

}

static void loop(){
  for(;;){
    receive(TRUE); // (1/2) Send acknowledgement even if ntexec.out doesn't require it
    if(0==strcmp(CMD_QUIT,buf))
      break;
    openlnk();
  }
}

static void cleanup(){
  printf("quit ...\n");
  assert(0==closesocket(sockfd));
  assert(0==WSACleanup());
  Sleep(500UL); // Wait for 500ms before making the window disappear
}

int main(){

  printf("\n");
  printf( "Build " __TIME__ " " __DATE__ "\n" );
  printf("\n");

  initialize_winsock();

  get_local_ip();

  create_socket();
  bind_socket();

  // receive(FALSE); // (2/2) Test purpose
  loop();

  cleanup();
  return EXIT_SUCCESS;

}
