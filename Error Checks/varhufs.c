#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<math.h>
void decode(int socket)
{
	char decode[100],freq[100],word[100];int n,i,j=0,k=0,size;
 	read(socket,decode,100);
 	read(socket,freq,100);
	for(n=0;freq[n];n++);
	size=ceil(log(n)*1.0/log(2));
	//printf("%d",size);
	int c=size-1;k=0;
	//convert binary to decimal
	for(i=0;decode[i];i++)
	{
	 	if(i%size==0 && i!=0)
	 		{
	 		 c=size-1;
	 		 //printf("j:%d c:%d\n",j,c);
	 		 //find position in array
	 		 word[k]=freq[j];
	 		 k++;
	 		 j=0;
	 		}
	 		{
	 		 if(decode[i]=='1')
	 		 	{j+=(int)pow(2,c);}
	 		 c--;
	 		}
	}
	word[k]=freq[j];k++;
	word[k]='\0';
	printf("Word:%s ",word);
}
int main()
{
 int s_sock,cli;
 char buf[100];
 s_sock=socket(AF_INET,SOCK_STREAM,0);
 struct sockaddr_in server,other;
 server.sin_family=AF_INET;
 server.sin_port=htons(9000);
 server.sin_addr.s_addr=INADDR_ANY;
 if(bind(s_sock,(struct sockaddr*)&server,sizeof(server))==-1)
 {
  printf("Bind error");
  exit (1);
 }
 listen(s_sock,5);
 socklen_t len;
 len=sizeof(other);
 cli=accept(s_sock,(struct sockaddr*)&other,&len);
 decode(cli);
 close(s_sock);
 return 0;
}
