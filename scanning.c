#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

int main(void){
  char buffer[4096];	//message from Server
  char message[1024];	//message to send to Server
  int sock;
  int port;
  struct sockaddr_in temp; 
  struct hostent *h;

  temp.sin_family=AF_INET;
  h=gethostbyname("192.168.1.1");
  if(h==0){
    printf("Gethostbyname failed\n");
    exit(1);
  }
  bcopy(h->h_addr,&temp.sin_addr,h->h_length);
  for(port=1;port<8500;port++){
     sock=socket(AF_INET,SOCK_STREAM,0);
     temp.sin_port=htons(port);
     if(connect(sock, (struct sockaddr*) &temp, sizeof(temp)) < 0){
	// connection refused, then the cycle continues for try new connection with the next port
        close(sock);
	continue;
     }
     else{
        memset(buffer, '\0', sizeof(buffer));	// "clear" the buffer, setting it to null
        strcpy(message,"");			// "clear" the message
        if(write(sock,message,strlen(message))<0){	
           printf("Impossible to send the message\n");
           close(sock);
           continue;
        }  
        printf("Message sent successfully to Port --> %d\n",port);
  
        /*if(read(sock,buffer,sizeof(buffer)) < 0) {
           printf("Impossible to read the message.\n");
           close(sock);
           continue;
        }
        printf("Message received to Port %d --> %s\n",port, buffer);*/
     }
     close(sock);
  }
  return 0;
}
