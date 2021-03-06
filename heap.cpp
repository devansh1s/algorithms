#include<iostream>

using namespace std;

void max_heapify(int heap[],int i,int n){

int l=2*i+1;
int r=2*i+2;
int largest;
if(l<n && heap[l]>heap[i])largest=l;
else largest=i;

if(r<n && heap[r]>heap[largest])largest=r;

if(largest!=i){
int temp=heap[i];
heap[i]=heap[largest];
heap[largest]=temp;

max_heapify(heap,largest,n);
}

}

void build_max_heap(int heap[],int n){

for(int i=n/2-1;i>=0;i--) max_heapify(heap,i,n);

}

int main(){

int n,i;
cout<<"\nEnter the size of the max heap: ";
cin>>n;
int heap[n];
cout<<"\nInput elements of the max heap::\n";
for(i=0;i<n;i++)cin>>heap[i];

build_max_heap(heap,n);
cout<<"\nHeap: ";
for(i=0;i<n;i++)cout<<heap[i]<<"  ";
cout<<endl;
}
