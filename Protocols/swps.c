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
    int i=0,size=5;int c=-1;
    char buf[100]="12345"; 
    printf("Enter size of data: ");scanf("%d",&size);
    printf("Enter data: ");scanf("%s",buf);
    while (1)
    {
     char x[100],y[100];
     x[0]=buf[i];
     x[1]='\0';
     time_t t ;
     t = time(NULL);
     if(i==3 && c==-1)
     	{sleep(5);c+=2;}
     if(c!=0)
     	{send(s_server,x,sizeof(x),0);
     	}
     recv(s_server,y,sizeof(y),0);
     printf("%s\n",y);
     time_t t2;
     t2=time(NULL);
     if(t2-t>10)
     		i--;
     i++;
     if(i>=size)
     	{
     	 char msg[100]="END";
     	 send(s_server,msg,sizeof(msg),0);
     	 break;
     	}
	}
	close(s_socket);
    return 0;
}
