#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

int main(int argc,char* argv[]){
  int sock;
  int port;
  int lenght=0;
  struct sockaddr_in temp; 
  struct hostent *h;
  
  if(argc != 2){
     printf("Usage: ./scanning <ipv4 address>\n");
     return 0; 
  }
  lenght = strlen(argv[1]);
  if(lenght < 7 || lenght > 15){
     printf("Wrong IP Address\n");
     return 0; 
  } 
  temp.sin_family=AF_INET;
  h=gethostbyname(argv[1]);
  if(h==0){
    printf("Gethostbyname failed\n");
    exit(1);
  }
  bcopy(h->h_addr,&temp.sin_addr,h->h_length);
  for(port=0;port<65536;port++){
     sock=socket(AF_INET,SOCK_STREAM,0);
     temp.sin_port=htons(port);
     if(connect(sock, (struct sockaddr*) &temp, sizeof(temp)) < 0){
	// connection refused, then the cycle continues for try new connection with the next port
        close(sock);
	continue;
     }
     else{
        printf("Active Port --> %d\n",port);
     }
     close(sock);
  }
  return 0;
}
