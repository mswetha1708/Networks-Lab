/*
a            5
    b           9
    c           12
    d           13
    e           16
    f           45
 */
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<iostream>
#include<algorithm>

using namespace std;
class Huffman
{
  private:
  struct node
  {
     int data;
     char d;
     struct node *nptr;
     struct node *pptr;
     struct node *addr;
  };
  struct node *top=NULL;
  struct node *rptr=NULL;
  int k;
  
  char ff[100][100];
  public:
    int n,freq[100];
    char d[100];
  void push(int x,char y);
  int pop();
  void bsort();
  void postorder(struct node *ptr);
  void print();
  void construct();
  void encode(struct node *ptr,char arr[],int m);
  int findfreq(char x);
  void decode(char s[100]);
};

void Huffman::push(int x,char y)
{
  node *Ttemp=new node();
  Ttemp->data=x;
  Ttemp->d=y;
  Ttemp->nptr=NULL;
  Ttemp->pptr=NULL;
  
  node *temp=new node();
  temp->data=x;
  temp->nptr=top;
  temp->addr=Ttemp;
  if(top!=NULL)
   top->pptr=temp;
  top=temp;
  temp->pptr=NULL;
}

int Huffman::pop()
{
  int x;
  if(top!=NULL)
  {
    x=top->data;
    top=top->nptr;
     
  }
  return x;
}
void Huffman::print()
{
  struct node *thptr=top;
  while(thptr!=NULL)
  {
    cout<<(thptr->addr)->data<<" ";
    thptr=thptr->nptr; 
  }
  cout<<endl;
}

void Huffman::bsort()
{
  int i,j,temp;
  char t;
  for(i=0;i<n;i++)
  {
     for(j=0;j<n-i-1;j++)
     {
       if(freq[j]>freq[j+1])
       {
         temp=freq[j];
         freq[j]=freq[j+1];
         freq[j+1]=temp;
         
         t=d[j];
         d[j]=d[j+1];
         d[j+1]=t;         
       }
     }
  }
}
void Huffman::construct()
{
  int i,s=0,j;
  for(i=0;i<100;i++)
   for(j=0;j<100;j++)
     ff[i][j]='*';
  char arr[100];
  /*cout<<"\nEnter the size of the array:";
  cin>>n;
  cout<<"\nEnter the letter and its frequencies:\n";
  for(i=0;i<n;i++)
  {
    cin>>d[i];
    cin>>freq[i];
  }*/
  bsort();
  for(i=n-1;i>=0;i--)
   push(freq[i],d[i]);
  cout<<"\nThe stack is:";
  print();
  struct node *thptr=top;
  struct node *tptr=thptr;
  int q=0;
  while(1)
  {
    s=(top->data)+((top->nptr)->data);
    //cout<<"S="<<s<<endl;
    node *temp=new node();
    temp->data=s;
    temp->pptr=top->addr;
    pop();
    temp->nptr=top->addr;
    pop();
    //cout<<temp->data<<endl;**********************************************************
    rptr=temp;
    cout<<temp->pptr->data<<" ";
    cout<<temp->nptr->data<<endl;
    if(top==NULL)
      break;
    
    thptr=top;
    tptr=thptr;
    while(thptr!=NULL && s>(thptr->data))
    {
      tptr=thptr;
      thptr=thptr->nptr;      
    }    
    
    
        if(thptr==top)
         {
          
          //push(s,'*');
          //**************************************************************************
           node *tmp=new node();
           tmp->data=s;
           tmp->addr=temp;
           tmp->nptr=top;

           if(top!=NULL)
              top->pptr=tmp;
            top=tmp;
            tmp->pptr=NULL;
           
         }
        else
        {
           //cout<<"Hello!"<<endl;
           node *tmp=new node();
           tmp->data=s;
           tmp->addr=temp;
           tmp->nptr=thptr;
           tmp->pptr=tptr;
           if(tptr!=NULL)
           tptr->nptr=tmp;
           
           if(thptr!=NULL)
           (tmp->nptr)->pptr=tmp;
           
        }

    
    //print();
     
   /* else
    {      node *tmp=new node();
           tmp->data=s;
           tmp->addr=temp;
           tmp->nptr=thptr;
           tmp->pptr=tptr;
           tptr->nptr=tmp;       
    
    }*/
    
  }
  cout<<"\nThe tree is:"<<endl;
  postorder(rptr);
  int m=0,r,c;
  encode(rptr,arr,m);
  cout<<endl;
  cout<<"\nLook-up table:\n";
  for(r=0;r<n;r++)
   { 
     cout<<d[r]<<":";
     for(c=0;c<100;c++)
     {
     if(ff[r][c]=='*')
      break;
      cout<<ff[r][c];
     }
     cout<<endl;
   }
   //decode();
  
}

void Huffman::postorder(struct node *ptr)
{
   if(ptr!=NULL)
   {
     postorder(ptr->pptr);
     postorder(ptr->nptr);
     cout<<ptr->data<<" ";
   }
}
int Huffman::findfreq(char x)
{
  int i=0;
  for(i=0;i<n;i++)
    if(d[i]==x)
      break;
  return i;
}
void Huffman::encode(struct node *ptr,char arr[],int m)
{
   if(ptr!=NULL)
   {
     if(ptr->pptr)
     {
     arr[m++]=48;
     encode(ptr->pptr,arr,m);
     }
     if(ptr->nptr)
     {
     arr[m-1]=49;
     
     encode(ptr->nptr,arr,m);
     
     }
     if(ptr->pptr==NULL && ptr->nptr==NULL)
     {
     
      //cout<<ptr->data<<" ";
     int i=0;
     char x;
     x=ptr->d;
     x=findfreq(x);
     for(i=0;i<m;i++)
     {
      ff[x][i]=arr[i];
      //cout<<arr[i]<<" ";
     }
     
      }
       
     
     }
   }
void Huffman::decode(char s[100])
{
  //string s;
  struct node *thptr=rptr;
  //cout<<"\nEnter the number to be decoded:";
  //cin>>s;
  for(int i=0;s[i]!='\0';i++)
  {
    if(s[i]==48)
    { thptr=thptr->pptr;
      if(thptr->pptr==NULL && thptr->nptr==NULL)
       {
       cout<<thptr->d;
       thptr=rptr;
       }
      
    } 
    else
    {
      thptr=thptr->nptr;
      if(thptr->pptr==NULL && thptr->nptr==NULL)
       {
       cout<<thptr->d;
       thptr=rptr;
       }
    }
       
  }
  
}


int main()
{
  Huffman h;
  //h.construct();
  int s_sock,cli;
  char buf[100];
  s_sock=socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in server,other;
  server.sin_family=AF_INET;
  server.sin_port=htons(9000);
  server.sin_addr.s_addr=INADDR_ANY;
  if(bind(s_sock,(struct sockaddr*)&server,sizeof(server))==-1)
  {
  	printf("Bind Error!");
  	exit(1);
  } 
  h.n=6;
  h.d[0]='a';
  h.d[1]='b';
  h.d[2]='c';
  h.d[3]='d';
  h.d[4]='e';
  h.d[5]='f';
  
  h.freq[0]=5;
  h.freq[1]=9;
  h.freq[2]=12;
  h.freq[3]=13;
  h.freq[4]=16;
  h.freq[5]=45;
  h.construct();
  //int n1;
  // char f[100];
  // recv(s_sock,f,100,0);
  //recv(s_sock,buf,sizeof(buf),0);
  //printf("MSG:%s",buf);
  //cout<<"Message from server :"<<buf;
  listen(s_sock,5);
  socklen_t len;
  len=sizeof(other);
  cli=accept(s_sock,(struct sockaddr*)&other,&len);
  read(cli,buf,sizeof(buf));
  FILE *fp;
  fp=fopen("add.txt","w");
  fprintf(fp,"%s",buf);
  printf("file received successfully");
  printf("data copied in add.txt file");
  fclose(fp);
  h.decode(buf);

  FILE *fp1;
  fp=fopen("add1.txt","w");
  fprintf(fp,"%s",buf);
  printf("file received successfully");
  printf("data copied in add.txt file");
  fclose(fp1);

  h.decode(buf);
  close(s_sock);
  return 0; 
}
