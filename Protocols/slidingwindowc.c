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
    char buf[100];// = "hello server";
    int n,n1,n2;
    c_socket = socket(AF_INET, SOCK_STREAM,0);
    struct sockaddr_in client;
    memset(&client,0,sizeof(client));
    client.sin_family = AF_INET;  
    client.sin_port = htons(9009);// Will divide into fragments 
    client.sin_addr.s_addr = inet_addr("192.168.43.186");//172.16.29.21");// Any ip address connecting to this will be accepted
    if(connect(c_socket,(struct sockaddr*)&client,sizeof(client))== -1) //IP Address and Port Number. Structure contains info
    {
        printf("Connection issue");
        return 0;
    }
    int i=0;
    char data[100],buff[100];
    recv(c_socket,buf,sizeof(buf),0);
    int len=strlen(buf);
    printf("Received data from server : %s\n", buf);
    i=0;
    int size=strlen(buf);
    int pno=size;
    while(1)
    {
        //char ack[100]="Acknowledgment: ";
        data[0]=buf[i];
        data[1]='\0';
        //strcat(ack,data);
        //printf("ack : %s\n", data);   
        send(c_socket,data,sizeof(data),0);
        i++;
        recv(c_socket,buff,sizeof(buff),0);
        if(strcmp(buff,"O")!=0)
        {
           pno++;
          // printf("\npno : %d\n", pno);
          //if(pno!=4)
        
        
            if(pno!=4)
                printf("Received data from server : %s\n", buff);
            else if(pno==4)
            {
               // printf("Lost packet from server : %s\n", buff);
                pno=0;
            }
        }
        
        //    pno=0;

        if(strcmp(buff,"END")==0)
            break;
        strcat(buf,buff);


    }
    // for(int i=0;i<strlen(buf);i++)
    // {
    //     char ack[100]="Acknowledgment: ";
    //     data[0]=buf[i];
    //     data[1]='\0';
    //     strcat(ack,data);
    //     printf("ack : %s\n", ack);   
    //     send(c_socket,ack,sizeof(ack),0); 
    //     if(i<len-1)
    //     {
    //     recv(c_socket,buff,sizeof(buff),0);
    //     printf("Received data from server : %s\n", buff);
    //     if(strcmp(buff,"END")==0)
    //         break;
    //     strcat(buf,buff);
    //     printf("buf: %s\n", buf);
    //     }
    //     //printf("Received data from server : %s\n", buf);        
    // }     
    
    // while(1)
    // {  

    //     char ack[100]="Acknowledgment: ";
    //     recv(c_socket,buf,sizeof(buf),0);
    //     printf("Received data from server : %s\n", buf);
    //     if(strcmp(buf,"END")==0)
    //         break;
        
    //     //if(i==2)
    //     //sleep(13);
    //     send(c_socket,ack,sizeof(ack),0);
        
    //     i++;
    //     //bzero(ack,sizeof());
        

    //     // recv(c_socket,buf,sizeof(buf),0);
    //     // printf(" %s\n",buf);
    //     // scanf("%d",&n1);
    //     // send(c_socket,&n1,sizeof(n1),0);
    //     // scanf("%d",&n2);
    //     // send(c_socket,&n2,sizeof(n2),0);
    //     // int r;
    //     // recv(c_socket,buf,sizeof(buf),0);
    //     // printf(" %s\n",buf);
    //     // recv(c_socket,&r,sizeof(r),0);
    //     // printf(" %d\n", r);
    // }
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
