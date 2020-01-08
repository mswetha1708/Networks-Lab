#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
void receive_image(int socket)
{ 
int buffersize = 0, recv_size = 0,size = 0, read_size, write_size, packet_index =1,stat;

char imagearray[10241];
FILE *image;
do{
stat = read(socket, &size, sizeof(int));
}while(stat<0);//reading size of the image file.
image = fopen("capture4.bmp", "w");
while(recv_size < size) 
	{
        do
        		{
               read_size = read(socket,imagearray, 10241);//read from socket and write into array
            }while(read_size <0);
         write_size = fwrite(imagearray,1,read_size, image);//write from array to the file
             recv_size += read_size;
             packet_index++;
             printf("Total received image size: %i\n",recv_size);
	}
  fclose(image);
  printf("Image successfully Received!\n");
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
 receive_image(cli);
 close(s_sock);
 return 0;
}
