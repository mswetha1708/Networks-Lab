//Variable length Hufman code
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<math.h>
void encode(int socket)
{
	
	int n;int size,i,j,k,c=0,l;
 	printf("Enter number of distinct characters in language");
 	scanf("%d",&n);
 	char freq[n];
 	printf("Enter the characters in the Array");
 	//for(i=0;i<n;i++)
 		scanf("%s",freq);
 	//printf("%s",freq);

	//Size has the number of bits for encoding.
	char encode[100];int len;
	char buf[100]="works";
	for(len=0;buf[len];len++);
	size=ceil(log(n)*1.0/log(2));
	//printf("%d",size);
	char A[size];
	for(i=0;buf[i];i++)
		{
		 for(j=0;j<n;j++)
		 	if(freq[j]==buf[i])
		 		break;
		 //printf("%d ",j);
		 //convert j to binary
		 if(j==1 || j==0)
		 	k=0;
		 else
		 	{for(k=0;;k++)
		 		{
		 		 int x=j/(int)pow(2,k); 
		 		if(x==0)
		 			{break;}
		 		}
		 	}
		 //printf("%d\n",k);
		 for(l=size-1;l>=k;l--)
		 	A[l]='0';
		 if(j==1)
		 	A[0]='1';
		 for(l=k-1;l>=0;l--)
		 	{
		 	 	if(j/(int)pow(2,l)!=0)
		 	 		{A[l]='1';j-=(int)pow(2,l);}
		 	 	else
		 	 		A[l]='0';
		 	 	
		 	 	//printf("j:%d ",j);	
		 	}
		 //printf("%s\n ",A);
		 for(k=size-1;k>=0;k--)
		 	{encode[c]=A[k];c++;}
		 encode[c]='\0';
			
		}
	//write encode to a file.
	FILE *fp;
	fp=fopen("enc.txt","w");
 	fprintf(fp,"%s",encode);
 	printf("File received successfully");
 	fclose(fp);	
 	write(socket,encode,sizeof(encode));
 	write(socket,freq,sizeof(freq));
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
 /*FILE *fp;
 fp=fopen("text.txt","r");
 fscanf(fp,"%s",buf);
 write(c_sock,buf,sizeof(buf));
 printf("File sent successfully");
 fclose(fp);
 */
 encode(c_sock);
 close(c_sock);
 return 0;
}
