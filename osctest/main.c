#include <stdio.h> //printf
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <time.h>


// -------------------------------------- //
// --- ATTENTION! USE THIS TO LISTEN! --- //
// ---      netcat -lu -p 8888        --- //
// -------------------------------------- //


#define BUFLEN 512  //Max length of buffer
#define PORT 51111   //The port on which to listen for incoming data

void die(char* s, int e)
{
  printf(s,e);
  perror(s);
  exit(1);
}

char* buildOscMessage(char* address, int32_t number) {
  
  return NULL;
}

int main(void)
{
  const char* hostname="127.0.0.1"; /* localhost */
  const char* portname="8888";
  struct addrinfo hints;
  memset(&hints,0,sizeof(hints));
  hints.ai_family=AF_UNSPEC;
  hints.ai_socktype=SOCK_DGRAM;
  hints.ai_protocol=0;
  hints.ai_flags=AI_ADDRCONFIG;
  struct addrinfo* res=0;
  int err=getaddrinfo(hostname,portname,&hints,&res);
  if (err!=0) {
    die("failed to resolve remote socket address (err=%d)",err);
  }
  int fd=socket(res->ai_family,res->ai_socktype,res->ai_protocol);
  if (fd==-1) {
    die("%s",err);
  }
  char* content = "sending udp packet\n";
  //keep listening for data
  while(1)
  {
    if (sendto(fd,content,strlen(content),0,
          res->ai_addr,res->ai_addrlen)==-1) {
      die("%s",err);
    }
    usleep(1000000);
  }
  close(fd);
  return 0;
}

