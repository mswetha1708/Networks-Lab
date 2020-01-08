#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include<pthread.h>
char client_message[1000];
char buffer[1024];
struct Paper{char Question[1000],Answer;}P[10];
struct Score{int sid,time;char ip[100];}S[50];
int size=0;
void * socketThread(void *arg)
{
  int newSocket = *((int *)arg);
	fprintf(stdout,"%d",newSocket);
   fflush(stdout);
  //recv(newSocket , client_message , 2000 , 0);
  // Send message to the client socket 
  //pthread_mutex_lock(&lock);
  //char *message = malloc(sizeof(client_message)+20);
    time_t t;  
   //FILE *fp;
   char line[1024],line2[1024],line3[1024];
    //fp=fopen("KBKCN.txt","r");
	//fseek (fp, 0, SEEK_SET);
    //sleep(5);
    int i=0;int sum=0;
    //while ( fgets ( line, sizeof line, fp ) != NULL ) /* read a line */
      while(i<8)
      {
        // fputs ( line, stdout ); /* write the line */
       strcpy(line,P[i].Question);
       line3[0]=P[i].Answer;
       line3[1]='\0';
 // strcpy(message,"Question : Why is life like this da dei?\nA.idk\tB.who knows\tC.Therlaye\tD.Thala ezhuthu dhaan\n ");
        //printf("%s",message);
        /*strcpy(line,"Hello");
        strcpy(line2,"hi");
        strcpy(line3,"D");*/
        time_t t ;
        t = time(NULL);
        //double time_taken = ((double)t)/CLOCKS_PER_SEC;
        //printf("%ld initial time",t);
        send(newSocket,line,1024,0);
        //fputs("GM",stdout);
        fprintf(stdout,"%d",i);
        fflush(stdout);
        if (recv(newSocket,client_message,1000,0)==0)
        	{fputs("Error",stdout);}
        fputs(client_message,stdout);
        fflush(stdout);
        //printf("Message from client id : %s",client_message);
        time_t t2;
        //int t2=0,t1=0;
        t2 = time(NULL);
        //strcat(line,line2);
        //strcat(line,client_message);
        //time_taken = ((double)t)/CLOCKS_PER_SEC;
        //printf("%ld later time ",t2-t); 
        ///printf("Time taken for answering is : %ld\n",t2-t);
        sum+=t2-t;
        if(t2-t>15)
        {
        char msg[1024]="You're out of the game!!";
        send(newSocket,msg,1024,0);
        //fputs("Heloo",stdout);
        //fflush(stdout);
        //printf("Exit socketThread \n");
        close(newSocket);
        //fclose(fp);
        pthread_exit(NULL);
        }
        else if(line3[0]==client_message[0])
        {   
        	if(i!=7)
        		{char mesg[1024]="Congrats! You've made it!!\n";
            	 send(newSocket,mesg,1024,0);
            	// fputs("Heloo",stdout);
            	// fflush(stdout);
            }
         else
         	{
         		char mesg[1024]="Game Over";
            	 send(newSocket,mesg,1024,0);
            	// fputs("Heloo",stdout);
            	// fflush(stdout);
            	int x; 
					for( x=0;x<size;x++)
						{
						 if(S[x].sid==newSocket)
						 	{S[x].time=sum;
						 	break;}
						}
             	 fprintf(stdout,"%d",S[x].sid);
            	 fflush(stdout);
            	 fprintf(stdout,"%d",S[x].time);
   				 fflush(stdout);
            	 //close(newSocket);
            	 pthread_exit(NULL);
         	}
            	
        }
        else
        {
            char msg[1024]="You're out of the game!!";
            send(newSocket,msg,1024,0);
            //printf("Exit socketThread \n");
            //fputs("Heloo",stdout);
           	//fflush(stdout);
            close(newSocket);
            //fclose(fp);
            pthread_exit(NULL);                
        }
        /*strcat(line,"\n");
        strcpy(buffer,line);
        printf("%s",buffer);
        //printf("[+] conection accepted from %s,%d",inet_ntoa(serverStorage.sin_addr),ntohs(serverStorage.sin_port)); // print the address and port umber of client connections
        //free(line);*/
        bzero(line,sizeof(line));
        bzero(line2,sizeof(line2));
        bzero(line3,sizeof(line3));
        bzero(client_message,sizeof(client_message));
        i++;
        // fgets ( line, sizeof line, fp );
        // printf("%s",line);
      }
  //pthread_mutex_unlock(&lock);
 // printf("%s",buffer);
  //sleep(1);
  //printf("%s",buffer);
  //printf("[+] conection accepted from %s,%d",inet_ntoa(serverStorage.sin_addr),ntohs(serverStorage.sin_port)); // print the address and port umber of client connections
  //send(newSocket,buffer,13,0);

  //printf("Exit socketThread \n");
  //strcpy(buffer,"U are the Winner!!");
  //send(newSocket,buffer,strlen(buffer),0);
  //fclose(fp);
  /*pthread_exit(NULL);
  close(newSocket);*/
}

int main(){
  strcpy(P[0].Question,"1.What is the capital of Tamil Nadu?A.Delhi	B.Calcutta	C.Chennai	D.Ahmedabad");
  P[0].Answer='C';
  strcpy(P[1].Question,"2.What is the new name of Ahmedabad?A.Prayagraj	B.Allahabad	C.RamBhoomi	D.Delhi");
  P[1].Answer='A';
  strcpy(P[2].Question,"3.Which Company is merging with Andra Bank?A.City Bank	B.ICICI	C.Union Bank	D.BOB");
  P[2].Answer='C';
  strcpy(P[3].Question,"4.The first NetworkA.CNNET B.NSFNET C.ASAPNET D.ARPANET");
  P[3].Answer='D';
   strcpy(P[4].Question,"5.The protocol data unit(PDU) for the application layer in the Internet stack is A.Segment  B.Datagram C. Message D.Frame");
  P[4].Answer='C';
  strcpy(P[5].Question,"6.Which of the following transport layer protocolss is used to support electronic mail?A. SMTP B. IP C. TCP D. UDP");
  P[5].Answer='C';
  strcpy(P[6].Question,"7. In the IPv4 addressing format, the number of networks allowed under Class C addresses is A. 2^14 B. 2^7 C. 2^21 D. 2^24");
  P[6].Answer='C';
  strcpy(P[7].Question,"8. Packets of the same session may be routed through different paths in:A. TCP, but not UDP  B. TCP and UDP  C. UDP, but not TCP  D. Neither TCP nor UDP");
  P[7].Answer='B';
  int serverSocket, newSocket;
  struct sockaddr_in serverAddr,other;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;
  //Create the socket. 
  serverSocket = socket(PF_INET, SOCK_STREAM, 0);
  // Configure settings of the server address struct
  // Address family = Internet 
  serverAddr.sin_family = AF_INET;
  //Set port number, using htons function to use proper byte order 
  serverAddr.sin_port = htons(7799);
  //Set IP address to localhost 
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  //Set all bits of the padding field to 0 
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
  //Bind the address struct to the socket 
  bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  //Listen on the socket, with 40 max connection requests queued 
  if(listen(serverSocket,50)==0)
    printf("Listening\n");
  else
    printf("Error\n");
    pthread_t tid[60];
    int i = 0,pos;
    while(1)
    {
        //Accept call creates a new socket for the incoming connection
        addr_size = sizeof other;
        newSocket = accept(serverSocket, (struct sockaddr *) &other, &addr_size);
        //for each client request creates a thread and assign the client request to it to process
       //so the main thread can entertain next request
        if( pthread_create(&tid[i], NULL, socketThread, &newSocket) != 0 );
           //printf("Failed to create thread\n");
			fprintf(stdout,"%d",newSocket);
   		fflush(stdout);
   		S[i].sid=newSocket;
   		S[i].time=10000;
   		strcpy(S[i].ip,inet_ntoa(other.sin_addr));
   		size++;
        fputs("[+] conection accepted from",stdout);
        fputs(inet_ntoa(other.sin_addr),stdout);
        //fputs(char*(ntohs(other.sin_port)),stdout);
        fflush(stdout);
        i++;
        if(i==2)
        	{sleep(30);
        	 int min=10000;pos=size;
			for(int i=0;i<size;i++)
				if(S[i].time<min)
					{min=S[i].time;pos=i;}
			//fprintf(stdout,"The winner is%d",S[pos].sid);
        	break;}
    }
    		char mesg[1024]="The Winner is:\n";
			strcat(mesg,S[pos].ip);
         send(newSocket,mesg,1024,0);
         fputs(mesg,stdout);
         fflush(stdout);
          while(i < 2)
          {
            pthread_join(tid[i++],NULL);
          }
  return 0;
}
