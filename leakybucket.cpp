#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#define bucketSize 512
using namespace std;

void bktInput(int a,int b)
{
    if(a>bucketSize)
        cout<<"\n\t\t Bucket overflow !!!";
    else
    {
        usleep(500);
        while (a>b)
        {
            cout<<"\n\t\t"<<b<<"bytes outputted";
            a-=b;
            usleep(500);
        }
        if(a>0)
            cout<<"\n\t\t Last"<<a<<"bytes sent\t";
        cout<<"\n\t\t Bucket output successful";
    }
}

int main()
{
    int op,pktSize;
    cout<<"Enter output rate: ";
    cin>>op;
    for(int i=1;i<=5;i++)
    {
        usleep(rand()%1000);
        pktSize=rand()%1000;
        cout<<"\n Packet no"<<i<<"\t Packet size="<<pktSize;
        bktInput(pktSize,op);
    }
    return 0;
}


/************************output*********************************

Enter output rate: 100

 Packet no1	 Packet size=886
		 Bucket overflow !!!
 Packet no2	 Packet size=915
		 Bucket overflow !!!
 Packet no3	 Packet size=335
		100bytes outputted
		100bytes outputted
		100bytes outputted
		 Last35bytes sent	
		 Bucket output successful
 Packet no4	 Packet size=492
		100bytes outputted
		100bytes outputted
		100bytes outputted
		100bytes outputted
		 Last92bytes sent	
		 Bucket output successful
 Packet no5	 Packet size=421
		100bytes outputted
		100bytes outputted
		100bytes outputted
		100bytes outputted
		 Last21bytes sent	
*/
