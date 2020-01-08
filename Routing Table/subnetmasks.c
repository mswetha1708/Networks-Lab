#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
int main()
{
    int s_socket, s_server;
     char subnet[100],ip[100]="192.168.43.92";
    s_socket = socket(AF_INET, SOCK_STREAM,0);
    struct sockaddr_in server,other;
    memset(&server,0,sizeof(server));
    memset(&other,0,sizeof(other));
    server.sin_family = AF_INET;
    server.sin_port = htons(9009);
    server.sin_addr.s_addr = INADDR_ANY;
    bind(s_socket,(struct sockaddr*)&server,sizeof(server));
    listen(s_socket,5);
    socklen_t add;
    add = sizeof(other);
    s_server = accept(s_socket,(struct sockaddr*)&other,&add );
    strcpy(ip,inet_ntoa(other.sin_addr));
    scanf("%s",ip);
    recv(s_server,subnet,sizeof(subnet),0);
    printf("IP:%s\n",ip);
    printf("Subnet%s\n",subnet);
     int i;char s[100],il[100],res[100],fres[100];int num2[4],num1[4],num3[4],k=0,j=0;
 for(i=0;;i++)
 {
 	if(ip[i]=='.' || ip[i]=='\0')
  	{
  	  il[j]='\0';
  	 num2[k]=atoi(il);
  	 k++;
  	 j=0;
  	}
  else
  	{
  	 	il[j]=ip[i];
  	 j++;
  	}
  	if(ip[i]=='\0')
  		break;
}
j=0;k=0;
 for(i=0;;i++)
 {
 	if(subnet[i]=='.' || subnet[i]=='\0')
  	{
  	 s[j]='\0';
  	 num1[k]=atoi(s);
  	 k++;
  	 j=0;
  	}
  else
  	{
  	 if(subnet[i]!='\0')
  	 	s[j]=subnet[i];
  	 j++;
  	}
  if(subnet[i]=='\0')
  	break;
}
for(i=0;i<4;i++)
{
 	num3[i]=num1[i] & num2[i];
 	sprintf(res,"%d",num3[i]);
  	strcat(res,".");
  	strcat(fres,res);
}
	 strcpy(fres,"HelloDestn");
    printf("Subnet Addr: %s\n", fres);
    send(s_server,fres,sizeof(fres),0);
    close(s_server);
    return 0;
}
