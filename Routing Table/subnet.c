#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
int main()
{
    int c_socket;
    char buf[100] = "255.255.255.0",buf1[100];
    c_socket = socket(AF_INET, SOCK_STREAM,0);
    struct sockaddr_in client;
    memset(&client,0,sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(9009);// Will divide into fragments 
    client.sin_addr.s_addr = inet_addr("192.168.43.186");//INADDR_ANY;// Any ip address connecting to this will be accepted
    if(connect(c_socket,(struct sockaddr*)&client,sizeof(client))== -1) //IP Address and Port Number. Structure contains info
    {
        printf("Connection issue");
        return 0;
    }
    send(c_socket,buf,sizeof(buf),0);
    recv(c_socket,buf1,sizeof(buf1),0);
    printf("Message from server : %s", buf1);
    close(c_socket);
    return 0;
}

//make socket

//nc 127.0.0.1 -l 9009

//./socket