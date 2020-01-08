#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
int main()
{
    int s_socket, s_server;
     char buf[100] = "\nCALCULATOR MENU\n1.Add\n2.Subt\n3.Mul\n4.Division\n5.Exit\nEnter your choice";
     char input[100]="Enter the two operands";int ch,n1,n2,result;
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
    while(1)
    {
     //scanf("%s",buf);
     send(s_server,buf,sizeof(buf),0);
     recv(s_server,&ch,sizeof(ch),0);
     
     printf("Message from client (the choice) : %d\n", ch);
     if(ch==5)
     	goto end;
     send(s_server,input,sizeof(input),0); 
     recv(s_server,&n1,sizeof(n1),0); 
     recv(s_server,&n2,sizeof(n2),0);
     printf("The numbers from client %d %d\n",n1,n2); 
     switch(ch)
     {
      case 1:result=n1+n2;break; 
      case 2:result=n1-n2;break;
      case 3:result=n1*n2;break;
      case 4:if(n2!=0)
      			result=n1/n2;
             else
             	result=-666;break;
      case 5:goto end;
     }
     if(result==-666)
     {char buf1[100]="Invalid Entry";
      send(s_server,buf1,sizeof(buf1),0);
      send(s_server,&result,sizeof(result),0);
     } 
     else
     {
      char buf1[100]="Result is: ";
      send(s_server,buf1,sizeof(buf1),0);
      send(s_server,&result,sizeof(result),0);
     }
    }
    end :
    	close(s_server);
    return 0;
}
