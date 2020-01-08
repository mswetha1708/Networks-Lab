#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
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
  char d[100];
  int n,freq[100];
  char freq1[100][100];
  void push(int x,char y);
  int pop();
  void bsort();
  void postorder(struct node *ptr);
  void print();
  void construct();
  void encode(struct node *ptr,char arr[],int m);
  int findfreq(char x);
  void decode();
  void encodeConv(char s[100]);
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
  
  cout<<"\nEnter the size of the array:";
  cin>>n;
  cout<<"\nEnter the letter and its frequencies:\n";
  for(i=0;i<n;i++)
  {
    cin>>d[i];
    cin>>freq1[i];
    if(strlen(freq1[i])==2)
     freq[i]=(10*(freq1[i][0]-48))+(freq1[i][1]-48);
    else if(strlen(freq1[i])==1)
     freq[i]=(freq1[i][0]-48);
  // cout<<freq[i]<<endl;

  }
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

   //encode(rptr,"aabbccaadd",0);
   //decode();
   char st[100];
   cout<<"\nEnter the string to be encoded:";
   cin>>st;
   //"aabbccaadd"
   encodeConv(st);
  
}

void Huffman::encodeConv(char s[100])
{
    char code[100];
    int j;
    FILE *fp;
    fp=fopen("text5.txt","w");
    for(int i=0;i<strlen(s);i++)
    {
        for( j=0;j<n;j++)
        {
            if(s[i]==d[j])
                break;
        }
        int c;
        for(c=0;c<100;c++)
         {
         if(ff[j][c]=='*')
          break;
          code[c]=ff[j][c];
         }
         code[c]='\0';
         cout<<code<<endl;
        //strcpy(code,ff[j]);
        fprintf(fp,"%s",code);
        
    }
    fclose(fp);

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
void Huffman::decode()
{
  string s;
  struct node *thptr=rptr;
  cout<<"\nEnter the number to be decoded:";
  cin>>s;
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
    int c_sock;
    Huffman h;
    h.construct();
    char buf[100],buf1[100];
    c_sock=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in client;
    memset(&client,0,sizeof(client));
    client.sin_family=AF_INET;
    client.sin_port=htons(9000);
    client.sin_addr.s_addr = /*INADDR_ANY;*/inet_addr("192.168.43.123");
    if(connect(c_sock,(struct sockaddr*)&client,sizeof(client))==-1)
    {
        printf("Connection error");
        exit(1);
    }
    FILE *fp4;
    fp4=fopen("text1.txt","w");
    fprintf(fp4,"%s",h.d);
    fclose(fp4);

    FILE *fp1;
    fp1=fopen("text1.txt","r");
    fscanf(fp1,"%s",buf);
    write(c_sock,buf,sizeof(buf));
    printf("File1 sent successfully");
    fclose(fp1);
    
    char ffreq[100]=" ";
    //strcpy(ffreq,NULL);
    for(int i=0;i<h.n;i++)
    {
      strcat(ffreq,(h.freq1[i]));
      strcat(ffreq,"*");
    }
    cout<<"ffreq="<<ffreq<<endl;
    FILE *fp2;
    fp2=fopen("text2.txt","w");
    fprintf(fp2,"%s",ffreq);
    fclose(fp2);
    
    FILE *fp3;
    fp3=fopen("text2.txt","r");
    fscanf(fp3,"%s",buf);
    write(c_sock,buf,sizeof(buf));
    printf("File2 sent successfully");
    fclose(fp3);

   /* FILE *fp;
    fp=fopen("text2.txt","w");
    fprintf(fp,"%s",h.n);
    close(fp)

    FILE *fp1;
    fp=fopen("text2.txt","r");
    fscanf(fp,"%s",buf);
    write(c_sock,buf,sizeof(buf));
    printf("File2 sent successfully");
    fclose(fp1);
*/
    //cout<<"\n n="<<h.n;
    // char f[100];
    // *((int*)f)=34543;
    // send(c_sock,f,100,0);
    // cout<<"d="<<h.d;
    // char da[100];
    // strcpy(da,h.d);
    //send(c_sock,da,sizeof(da),0);//char array
    //send(c_sock,&(h.freq),sizeof(h.freq),0);//freq of each letter
    FILE *fp;
    fp=fopen("text5.txt","r");
    fscanf(fp,"%s",buf);
    write(c_sock,buf,sizeof(buf));
    printf("File sent successfully");
    fclose(fp);

    close(c_sock);
    return 0;
}
