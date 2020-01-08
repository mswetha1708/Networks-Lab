#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

 void send_image(int socket)
{

   FILE *picture;
   int size, read_size, stat, packet_index;
   char send_buffer[10240];
   packet_index = 1;
   picture = fopen("minion.bmp", "r");
   fseek(picture, 0, SEEK_END);
   size = ftell(picture);//size is the size of the entire image
   fseek(picture, 0, SEEK_SET);
   printf("Total Picture size: %i\n",size);
   write(socket, (void *)&size, sizeof(int));
   while(!feof(picture)) 
   	{
      read_size = fread(send_buffer, 1, sizeof(send_buffer)-1, picture);//reading data from the file to send_buffer.
      do
      {
        stat = write(socket, send_buffer, read_size);  
      }while (stat < 0);//writing the read data to the socket
      //printf("Packet Number: %i\n",packet_index);
      printf("Packet Size Sent: %i\n",read_size);     
      packet_index++;  
      bzero(send_buffer, sizeof(send_buffer));//clearing data in send buffer for next read.
     }
}

int main()
{
 int c_sock;
 char buf[100];
 c_sock=socket(AF_INET,SOCK_STREAM,0);
 struct sockaddr_in client;
 client.sin_family=AF_INET;
 client.sin_port=htons(9000);
 client.sin_addr.s_addr=INADDR_ANY;
 if(connect(c_sock,(struct sockaddr*)&client,sizeof(client))==-1)
 {
  printf("Connection error");
  exit (1);
 }
  send_image(c_sock);
    fflush(stdout);
 close(c_sock);
 return 0;
}
