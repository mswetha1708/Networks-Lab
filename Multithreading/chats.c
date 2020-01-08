#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include<pthread.h>
struct Sockdet{int sid;char ip[100];}S[50];
int size=0;
void * socketThread(void *arg)
{
  int newSocket = *((int *)arg);
	fprintf(stdout,"%d",newSocket);
   fflush(stdout);
    time_t t;  
   //FILE *fp;
   char line[1024],line2[1024],line3[1024];;
    int i=0;int sum=0;
      while(1)
      {
       char ch[1024]="Enter SEND or QUIT";
       send(newSocket,ch,1024,0);
       char buf[1024];
       recv(newSocket,buf,1024,0);
       	fprintf(stdout,"%s",buf);
   		fflush(stdout);
       if(strcmp(buf,"SEND\n")==0)
       	{
       	 fprintf(stdout,"%d",size);
   		 fflush(stdout);
       	 int i=0;char buf1[1024];buf1[0]='\0';
       	 for(i=0;i<size;i++)
       	 	{
       	 	 char buf2[100];
       	 	 //itoa(S[i].sid,buf2,1024);
       	 	 buf2[0]=S[i].sid+48;
       	 	 buf2[1]='\0';
       	 	 strcat(buf1,buf2);
       	 	 strcat(buf1," ");
       	 	 strcat(buf1,S[i].ip);
       	 	 strcat(buf1,",");
       	 	}
       	 	strcat(buf1,"\nEnter Socket\n");
       	 char sock[1024];
       	 send(newSocket,buf1,1024,0);
       	 recv(newSocket,sock,1024,0);
       	 fprintf(stdout,"%s",sock);
   		 fflush(stdout);
       	 char buf2[1024]="Enter message";
       	 char message[1024];
       	 send(newSocket,buf2,1024,0);
       	 recv(newSocket,message,1024,0);
       	 fprintf(stdout,"%s",message);
   		 fflush(stdout);
       	 int Socket=atoi(sock);
       	 send(Socket,message,1024,0);
       	}
		else if(strcmp(buf,"QUIT\n")==0)
			{
			 sleep(10);
			 //pthread_exit(NULL);
  			 //close(newSocket);
  			 //break;
			}
      }
  /*pthread_exit(NULL);
  close(newSocket);*/
}

int main(){
  int serverSocket, newSocket;
  struct sockaddr_in serverAddr,other;
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
    int i = 0,pos;
    while(1)
    {
        //Accept call creates a new socket for the incoming connection
        addr_size = sizeof other;
        newSocket = accept(serverSocket, (struct sockaddr *) &other, &addr_size);
        //for each client request creates a thread and assign the client request to it to process
       //so the main thread can entertain next request

			fprintf(stdout,"%d",newSocket);
   		fflush(stdout);
   		S[i].sid=newSocket;
   		strcpy(S[i].ip,inet_ntoa(other.sin_addr));
   		size++;
  		   if( pthread_create(&tid[i], NULL, socketThread, &newSocket) != 0 )
           printf("Failed to create thread\n");
        fputs("[+] conection accepted from",stdout);
        fputs(inet_ntoa(other.sin_addr),stdout);
        fflush(stdout);
        i++;
        if(i==2)
        	{sleep(40);break;}
    }
          while(i < 2)
          {
            pthread_join(tid[i++],NULL);
          }
  return 0;
}
