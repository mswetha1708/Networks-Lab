#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <unistd.h> 
#include<pthread.h>
void * cientThread(void *arg)
{
  printf("In thread\n");
  char message[1024];
  //int sckno;
  char buffer[1024],buffer3[1024];
  int clientSocket;
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
  // Create the socket. 
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  //Configure settings of the server address
 // Address family is Internet 
  serverAddr.sin_family = AF_INET;
  //Set port number, using htons function 
  serverAddr.sin_port = htons(7799);
 //Set IP address to localhost
  serverAddr.sin_addr.s_addr = inet_addr("192.168.43.186");//172.16.29.21");//192.168.43.186");//172.17.17.64");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    //Connect the socket to the server using the address
    addr_size = sizeof serverAddr;
    if(connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size)==-1)
    	{
    	 //printf("Error in connection");
    	 exit(1);	
    	};
    //strcpy(message,"Hello");
   while(1)
   {//Read the message from the server into the buffer

    	recv(clientSocket, buffer, 1024, 0);//Send or Quit
    	fputs(buffer,stdout);
      fflush(stdout);
    	
      fgets(message,sizeof(message),stdin);
      fflush(stdin);
		  send(clientSocket , message ,1024, 0);
      char msg[100];
      if(strcmp(message,"SEND\n")==0)
      {

        recv(clientSocket, buffer, 1024, 0); //List of ip addr 
        fputs(buffer,stdout);
        fflush(stdout); 

        //bzero(message,sizeof(message));
        fgets(msg,sizeof(msg),stdin);
        fflush(stdin);
        //strcpy(message,"4");
        fputs(msg,stdout);
        fflush(stdout); 
        send(clientSocket , msg ,1024, 0); //socket no

        recv(clientSocket, buffer, 1024, 0);//Enter the data
        fputs(buffer,stdout);
        fflush(stdout); 

        fgets(message,sizeof(message),stdin);
        fflush(stdin);
        send(clientSocket , message ,1024, 0); //send data

      } 

      else
      {

        recv(clientSocket, buffer, 1024, 0);//mssg
        fputs(buffer,stdout);
        fflush(stdout); 

      }  
    		 
		
    	bzero(message,sizeof(message));
      bzero(buffer,sizeof(buffer));
      
      bzero(buffer3,sizeof(buffer3));
   }
   
   // recv(clientSocket,buffer3,1024,0);
      
   //    fputs(buffer3,stdout);
   //    fflush(stdout);
    
}

int main(){

  int i = 0;
  pthread_t tid;

    if( pthread_create(&tid, NULL, cientThread, NULL) != 0 );
          // printf("Failed to create thread\n");
     pthread_join(tid,NULL);
     //printf("%d:\n",i); 
  //return 0;
}
