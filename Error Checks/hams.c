#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<math.h>
void function(char *encoded)
{
   
   int j,z;
   for(j=1;encoded[j];j++);
    int pos=rand()%(j-1)+1;
    if(encoded[pos]=='0')
        encoded[pos]='1';
    else
        encoded[pos]='0';
    /*int pos2=2;
    if(encoded[pos2]=='0')
        encoded[pos2]='1';
    else
        encoded[pos2]='0';*/
    for(int k=strlen(encoded);k>0;k--)
        printf("%c",encoded[k]);
   int y=floor(log(j-1)/log(2));
   int error[y],num=0;
   for(int i=0;i<y;i++)
   	error[i]=0;
   printf("Error in position");
   for(int k=0;k<y;k++)
    {
     	z=(int)pow(2,k);
     	for(int i=1;i<j-1;i++)
     		{
     		 if((i>>k & 1)==1)
     		 		error[k]=(error[k] ^((int)encoded[i]-48));
     		}
     	num+=pow(2,k)*error[k];
    }
    int xor=encoded[1]-48;
    for(int k=2;k<j;k++)
    	{
    	 xor=xor^(encoded[k]-48);
   	}
    if(num==0 && xor==0)
     	printf("No error");
     else if(num==0 && xor!=0)
     	printf("Error in parity bit");
     else if(num!=0 && xor!=0)
     	printf("Error @ pos:%d",num);
     else if(num!=0 && xor==0)
     	printf("2bit error");
}
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
    //for(int i=0;i<2;i++)
    //{
     send(s_server,buf,sizeof(buf),0);
     recv(s_server,buf,sizeof(buf),0);
     printf("Message from client :");
     function(buf);

    
    // printf("%d",strlen(buf));
    /*for(int k=strlen(buf);k>0;k--)
        printf("%c",buf[k]);*/
    close(s_server);
    return 0;
}
