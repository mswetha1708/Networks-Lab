
//192.168.43.92/24-this sys
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<math.h>
int main()
{
    int c_socket;
    char msg[100],encoded[100];
    int m,y=1,z,j=0,arr[100][100],n,l,k,i,x;
    char buf[100] = "hello server";
    c_socket = socket(AF_INET, SOCK_STREAM,0);
    struct sockaddr_in client;
    memset(&client,0,sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(9009);// Will divide into fragments 
    client.sin_addr.s_addr = inet_addr("192.168.43.186");//"192.168.43.186");// Any ip address connecting to this will be accepted
    if(connect(c_socket,(struct sockaddr*)&client,sizeof(client))== -1) //IP Address and Port Number. Structure contains info
    {
        printf("Connection issue");
        return 0;
    }
    //send(c_socket,buf,sizeof(buf),0);
    recv(c_socket,buf,sizeof(buf),0);
    printf("Message from server : %s", buf);
    
    printf("\nEnter the msg:");
    scanf("%s",msg);
    ////////////////////////////////////////////////////////////////////////////////////
    m=strlen(msg);
    // while(1)
    // {
    //  z=pow(2,y);
    //  if(z>=(m+y))
    //      break;
    //  y++;
    // }
    // printf("%d\n",y);
    j=1;y=0;
    int c=m-1;
    while(c>=0)
    {
    	if(ceil(log2(j))==floor(log2(j)))
    	{
    		//printf("%d",j);
    		encoded[j]='$';
    		y++;
    		j++;
    		continue;
    	}
    	else
    	{
    		encoded[j]=msg[c];
    		c--;
    		j++;
    	}
    	
    }
    //j is the strlen of message after calculating redundant bits
    for(int k=1;k<j;k++)
    	printf("%c",encoded[k]);
    	printf("\n");
    for(int k=0;k<y;k++)
    {
     	z=(int)pow(2,k);encoded[z]='0';
     	for(int i=1;i<j;i++)
     		{
     		 if((i>>k & 1)==1)
     		 	if(z!=i)
     		 		encoded[z]=((int)encoded[z]-48 ^(int)encoded[i]-48) +48;
     		}
    }
   int xor=encoded[1]-48;
   for(int k=2;k<j;k++)
    	{
    	 xor=xor^(encoded[k]-48);
   	}
    encoded[j]=xor+48;
    //printf("Xor:j:%d%c\n",j,encoded[j]);
    j++;
    encoded[j]='\0';
    /*for(int k=j-1;k>0;k--)
    	{
    	 printf("%c",encoded[k]);
   	}*/
    for(int k=j-1;k>0;k--)
    	{
    	 printf("%c",encoded[k]);
    	}
    send(c_socket,encoded,sizeof(encoded),0);
    //recv(c_socket,buf,sizeof(buf),0);
    //printf("Message from server : %s", buf);
    close(c_socket);
    return 0;
}

//make socket

//nc 127.0.0.1 -l 9009

//./socket
