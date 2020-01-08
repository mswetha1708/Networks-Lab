// 172.16.15.159/16 IP Address
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
int main()
{
    int c_socket;
    char buf[100] = "hello server";
    int n,n1,n2;
    c_socket = socket(AF_INET, SOCK_STREAM,0);
    struct sockaddr_in client;
    memset(&client,0,sizeof(client));
    client.sin_family = AF_INET;  
    client.sin_port = htons(9009);// Will divide into fragments 
    client.sin_addr.s_addr = inet_addr("172.16.29.21");// Any ip address connecting to this will be accepted
    if(connect(c_socket,(struct sockaddr*)&client,sizeof(client))== -1) //IP Address and Port Number. Structure contains info
    {
        printf("Connection issue");
        return 0;
    }
    while(1)
    {
        recv(c_socket,buf,sizeof(buf),0);
        printf("Message from server : %s\n", buf);
        scanf("%d",&n);
        send(c_socket,&n,sizeof(n),0);
        if(n==5)
         break;

        recv(c_socket,buf,sizeof(buf),0);
        printf(" %s\n",buf);
        scanf("%d",&n1);
        send(c_socket,&n1,sizeof(n1),0);
        scanf("%d",&n2);
        send(c_socket,&n2,sizeof(n2),0);
        int r;
        recv(c_socket,buf,sizeof(buf),0);
        printf(" %s\n",buf);
        recv(c_socket,&r,sizeof(r),0);
        printf(" %d\n", r);
    }
    //scanf("%d",&n);
    //  scanf("%s",buf);
    // send(c_socket,buf,sizeof(buf),0);
    // recv(c_socket,buf,sizeof(buf),0);
    // printf("Message from server : %s", buf);
    close(c_socket);
    return 0;
}

//make socket

//nc 127.0.0.1 -l 9009

//./socket
