//192.168.43.92/24-this sys
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
int main()
{
    int c_socket;
    char data[100]="0110";
    char buf[100];
    char div[100]="1101";
    c_socket = socket(AF_INET, SOCK_STREAM,0);
    struct sockaddr_in client;
    memset(&client,0,sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(9009);// Will divide into fragments 
    client.sin_addr.s_addr = inet_addr("192.168.43.186");// Any ip address connecting to this will be accepted
    if(connect(c_socket,(struct sockaddr*)&client,sizeof(client))== -1) //IP Address and Port Number. Structure contains info
    {
        printf("Connection issue");
        return 0;
    }
    //send(c_socket,buf,sizeof(buf),0);
    recv(c_socket,buf,sizeof(buf),0);
    //printf("Message from server : %s", buf);
    //scanf(:%s")
     int flag=0,l=0,j,i,n1,n2,n,k;char temp[100],flag2=0;
     n2=strlen(data);
     n=n2;
     n1=strlen(div);
     j=n;
     for(int i=1;i<n1;i++)
        {
            data[j]='0';
            j++;
        }
     n=j;
     for(i=0;i<n;i++)
        {
            if(data[i]==0 && flag==0)
                {flag++;continue;}
            temp[l]=data[i];
            l++;
            if(l==4)
                break;          
        }
     //  for(i=0;i<4;i++)
     //            printf("%c ",temp[i]);
     // printf("\n");
     j=flag+4;
     //printf("n=%d ",n);
     while(1)
     {
      for(i=0;i<4;i++)
        temp[i]=((div[i]-48)^(temp[i]-48))+48;
      // for(i=0;i<4;i++)
      //           printf("%c ",temp[i]);
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
        //printf("intermediate temp%s ",temp);    
     }
  /*for(i=0;i<4;i++)
      temp[i]=((div[i]-48)^(temp[i]-48))+48 ;*/  
    
    for(i=1;i<4;i++)
        data[n2++]=temp[i];  
    send(c_socket,data,sizeof(data),0);
    recv(c_socket,buf,sizeof(buf),0);
    //printf("Message from server : %s", buf);
    send(c_socket,div,sizeof(div),0);
    recv(c_socket,buf,sizeof(buf),0);
    printf("Message from server : %s", buf);
    recv(c_socket,buf,sizeof(buf),0);
    printf("\nRemainder : %s", buf);
    close(c_socket);
    return 0;
}

//make socket

//nc 127.0.0.1 -l 9009

//./socket
