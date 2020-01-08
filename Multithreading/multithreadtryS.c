#include<stdio.h>

#include<stdlib.h>

#include<sys/socket.h>

#include<netinet/in.h>
#include<signal.h>
#include<string.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include<pthread.h>
char client_message[2000];
char buffer[1024];
void * socketThread(void *arg)
{
  int newSocket = *((int *)arg);
  
  // Send message to the client socket 
  char message[100];
  strcpy(message,"Hello Client");
  while(1)
  {    
  send(newSocket,message,strlen(message)+1,0);
  if(recv(newSocket , client_message , 2000 , 0)<0)
  	printf("Recieve Failed");
  //printf("Hello this is me");
  //fflush(stdout);
  fputs(client_message,stdout);
  fflush(stdout);
  //printf("%s ",client_message);
  //bzero(message,sizeof(message));
  if(strcmp(client_message,"end")==0)
    break;
  bzero(client_message,sizeof(client_message));
  if(strcmp(client_message,"end")==0)
  	break;
  //printf("Enter Data to chat with ");
  //scanf("%s",message);
  }
  printf("Exit socketThread \n");
  close(newSocket);
  pthread_exit(NULL);
}
int main(){
  int serverSocket, newSocket;
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;
  //Create the socket. 
  serverSocket = socket(PF_INET, SOCK_STREAM, 0);
  // Configure settings of the server address struct
  // Address family = Internet 
  serverAddr.sin_family = AF_INET;
  //Set port number, using htons function to use proper byte order 
  serverAddr.sin_port = htons(7799);
  //Set IP address to localhost 
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  //Set all bits of the padding field to 0 
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
  //Bind the address struct to the socket 
  bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  //Listen on the socket, with 40 max connection requests queued 
  if(listen(serverSocket,50)==0)
    printf("Listening\n");
  else
    printf("Error\n");
    pthread_t tid[60];
    int i = 0;
    while(1)
    {
        //Accept call creates a new socket for the incoming connection
        addr_size = sizeof serverStorage;
        newSocket = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size);
        //for each client request creates a thread and assign the client request to it to process
       //so the main thread can entertain next request
        if( pthread_create(&tid[i], NULL, socketThread, &newSocket) != 0 )
           printf("Failed to create thread\n");
        if( i >= 50)
        {
          i = 0;
          while(i < 50)
          {
            pthread_join(tid[i++],NULL);
          }
          i = 0;
        }
    }
  return 0;
}
