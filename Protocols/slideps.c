#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
int main()
{
	 /*int size;int i=0;
    char buf[100];
    printf("Enter size of data: ");scanf("%d",&size);
    printf("Enter data: ");scanf("%s",buf);
    i=0;*/ 
    int s_socket, s_server;
    s_socket = socket(AF_INET, SOCK_STREAM,0);
    struct sockaddr_in server,other;
    memset(&server,0,sizeof(server));
    memset(&other,0,sizeof(other));
    server.sin_family = AF_INET;
    server.sin_port = htons(9009);
    server.sin_addr.s_addr = INADDR_ANY;
    //defines a relationship between the socket you created and the addresses that are available on your host. 
    //For example you can bind a socket on all addresses or on a specific IP which has been configured on a network adapter by the host's operating system
    /*if(connect(s_socket,(struct sockaddr*)&server,sizeof((server)))==-1)
    {
     printf("Connection Issue");
     return 0;
    }*/
    bind(s_socket,(struct sockaddr*)&server,sizeof(server));
    listen(s_socket,5);
    socklen_t add;
    add = sizeof(other);
    s_server = accept(s_socket,(struct sockaddr*)&other,&add ); 
    int i=0,size=5,w,data;int c=-1;
    char buf[100]="12345"; 
    printf("Enter size of data: ");scanf("%d",&size);
    printf("Enter data: ");scanf("%s",buf);
    printf("Enter Window Size: ");scanf("%d",&w);
    //printf("Enter every data packet number that is lost");scanf("%d",&data);
    char x[100];
    for(i=0;i<w;i++)
    {
	  x[i]=buf[i];
    }
    x[i]='\0';
    send(s_server,x,sizeof(x),0); 
    int packnum=4;
    int rack=0;int flag=0,flag2=0;
    while(1)
    {
     char y[100];
     recv(s_server,y,sizeof(y),0);
     if(y[0]=='O')
     	{//if(flag2==0)
     		{printf("Acknowledgement: %s\n",y);break;}
     	 /*else
     	 	{flag2--;}*/
     	}
     if(rack!=packnum-1)
     	{rack++;printf("Acknowledgement: %s\n",y);}
     else
     	{/*if(i>=size-1)
     		{flag2++;flag=0;}*/
     	 i-=w;rack=0;flag=0;}
      x[0]=buf[i];
      x[1]='\0';
      if(flag==0)
      	send(s_server,x,sizeof(x),0);
      else
      	{
      	 char buf1[100]="O";
      	 send(s_server,buf1,sizeof(buf1),0);
      	} 
      i++;
      if(i==size)
      	{
      	 flag=1;
      	}  	
	}
	char msg[100]="END";
   send(s_server,msg,sizeof(msg),0);
	close(s_socket);
    return 0;
}
