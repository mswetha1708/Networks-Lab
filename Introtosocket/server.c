#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
int main()
{
    int s_socket, s_server;
     char buf[100] = "hello client";
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
    for(int i=0;i<2;i++)
    {
     scanf("%s",buf);
     send(s_server,buf,sizeof(buf),0);
     recv(s_server,buf,sizeof(buf),0);
     printf("Message from client : %s\n", buf);
    }
    
    close(s_server);
    return 0;
}
