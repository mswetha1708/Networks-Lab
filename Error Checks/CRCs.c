#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
int main()
{
    int s_socket, s_server;
     char buf[100] = "Send the data";
     char buf1[100]="Send the divisor";
     char buf2[100]="Error";
     char buf3[100]="No Error";
     char data[100],div[100];
     int i;
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
     //scanf("%s",buf);
     send(s_server,buf,sizeof(buf),0);
     recv(s_server,data,sizeof(data),0);
	  printf("Data Sent: %s",data);
	  send(s_server,buf1,sizeof(buf1),0);
     recv(s_server,div,sizeof(div),0);
     printf("Divisor Sent: %s",div); 
     
     int flag=0,l=0,j,n,k;char temp[100];int flag2=0;
     n=strlen(data);
     int x=2;
     if(data[x]=='0')
     	data[x]='1';
     else
     	data[x]='0';
     
     for(i=0;i<n;i++)
     	{
     		if(data[i]==0 && flag==0)
     			{flag++;continue;}
     		temp[l]=data[i];
     		l++;
     		if(l==4)
     			break;			
     	}
     j=flag+4;
     while(1)
     {
      for(i=0;i<4;i++)
      	temp[i]=((div[i]-48)^(temp[i]-48))+48;
      //for(i=0;i<4;i++)
  		//		printf("%c ",temp[i]);
      for(int x=j;;x++)
      {i=0;
      if(j==n)
      	{flag2=1;break;}
      if(temp[i]=='0')
      	{
      	 for(k=0;k<3;k++)
      	 	temp[k]=temp[k+1];
      	 temp[k]=data[j];
      	 j++;
      	}
      if(temp[i]=='1')
      	break;
      }	
      if(flag2==1)
      	break;	
     }
  for(i=0;i<4;i++)
     	if(temp[i]!='0')
     		break;
  //printf("\n");
  if(i==4)
     	//printf("No error\n");
     	{send(s_server,buf3,sizeof(buf3),0);
     	send(s_server,temp,sizeof(temp),0);}
  else
  		{send(s_server,buf2,sizeof(buf2),0);
  		 send(s_server,temp,sizeof(temp),0);
  		}
  	//printf("Error\n");
    //}
    
    close(s_server);
    return 0;
}
