#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <unistd.h> 
#include<pthread.h>
# define N 2 //size of TempRouting
# define rtsize 2 //size of RoutingTable
struct RoutingTable
{
	char ip[100];
	char sys;
}R[2];
R[0]={"192.168.43.186",'B'};
R[1]={"172.16.29.21",'C'};

struct Message
{
  char msg[100];
  char destip[100];
  //char srcip[100];
};
struct TempRouting
{
	int sockno;
	char ip[100];
};


void * socketThread(void *arg)
{
  struct Message *m=arg;
  struct TempRouting r[N];
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
    int sid;
    int i=0;
    //int i = 0,pos;
    while(1)
    {
        //Accept call creates a new socket for the incoming connection
        addr_size = sizeof other;
        newSocket = accept(serverSocket, (struct sockaddr *) &other, &addr_size);
        //for each client request creates a thread and assign the client request to it to process
       //so the main thread can entertain next request
        r[i].sockno=newSocket;
        strcpy(r[i].ip,inet_ntoa(other.sin_addr));
        i++;
		fprintf(stdout,"%d",newSocket);
   		fflush(stdout);

        if(i==N)
        	break;
   		
    }
    int j=0;
    int k=0,sent=0;
    while(j<rtsize)
    {

    
    if(strcmp(R[j].ip,m->destip)==0)
   			{
   				for(int k=0;k<i;k++)
   				{
   					if(strcmp(r[k].ip,m->destip)==0)
   					{
   						sid=r[k].sockno;
		   				send(sid,m->msg,1024,0);
		                send(sid,m->destip,1024,0);
		                sent=1;
		                pthread_exit(0);
		   				break;

   					}
   				}

   				
   			}
    j++;
    }

  if(sent==0)
    {
    int j=0;
    while(j<rtsize)
    {

    
 
   			
   				for(int k=0;k<i;k++)
   				{
   					if(strcmp(r[k].ip,R[j].ip)==0 )//&& strcmp(r[k].ip,m.srcip)!=0)
   					{
   						//strcpy(m.srcip,"192.168.43.92");
   						sid=r[k].sockno;
		   				send(sid,m->msg,1024,0);
		                send(sid,m->destip,1024,0);
		   

   					}
   				}

   				
   			
    j++;
    }

    }
         
pthread_exit(0);
}


void * cientThread(void *arg)
{
  printf("In thread\n");
  
  //int sckno;
  char buffer[1024];
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
  serverAddr.sin_addr.s_addr = INADDR_ANY;//inet_addr("192.168.43.186");//172.16.29.21");//192.168.43.186");//172.17.17.64");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    //Connect the socket to the server using the address
    addr_size = sizeof serverAddr;
    if(connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size)==-1)
    	{
    	 //printf("Error in connection");
    	 exit(1);	
    	}
    //strcpy(message,"Hello");
  
   //Read the message from the server into the buffer

    	recv(clientSocket, buffer, 1024, 0);//MSG
    	fputs(buffer,stdout);
        fflush(stdout);
        char buffer1[1024];
        recv(clientSocket, buffer1, 1024, 0);//IP
    	fputs(buffer1,stdout);
        fflush(stdout);
        
        if(strcmp(buffer1,"192.168.43.92")==0)
        {
        	fputs(buffer,stdout);
            fflush(stdout);
            pthread_exit(0);
        }
        else
        {
        	struct Message m;
        	strcpy(m.msg,buffer);
        	strcpy(m.destip,buffer1);

        	pthread_t tid;
           if( pthread_create(&tid, NULL, socketThread,&m) != 0 );
          // printf("Failed to create thread\n");
           pthread_join(tid,NULL);
           pthread_exit(0);        	
        }

    	
      
}


int main()
{
  char ch[100];
  printf("\nEnter SEND or QUIT");
  scanf("%s",ch);
 pthread_t tid;
  if(strcmp(ch,"QUIT"))
  {

  //int i = 0;
    

    if( pthread_create(&tid, NULL, cientThread, NULL) != 0 );
          // printf("Failed to create thread\n");
     pthread_join(tid,NULL);
  }
  else
  {
  	struct Message m;
  	printf("\nEnter the message:");
  	scanf("%s",m.msg);
  	printf("\nEnter the destination ip:");
  	scanf("%s",m.destip);
  	//strcpy(m.srcip,"192.168.43.92");
    if( pthread_create(&tid, NULL, socketThread, &m) != 0 )
          // printf("Failed to create thread\n");
     pthread_join(tid,NULL);
  }
     //printf("%d:\n",i); 
  return 0;
}
