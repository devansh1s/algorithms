#include<iostream>
using namespace std;
void swap(int &a,int &b) {
	a = a+b;
	b = a-b;
	a = a-b;
}
void heapify(int *a,int i,int n) {
	int largest = i;
	int left = (2*i) + 1;
	int right = (2*i) + 2;
	if ( (left < n) && (a[left] > a[largest]) )
		largest = left;
	if ( (right < n) && (a[right] > a[largest]) )
		largest = right;
	if (largest != i) {
		swap(a[i],a[largest]);
		heapify(a,largest,n);
	}
}
void print(int *a,int n) {
	for (int i=0;i<n;i++) {
		cout<<a[i]<<" ";
	}
	cout<<endl;
}
void heapsort(int *a,int n) {
	for (int i=(n/2)-1;i>=0;i--)
		heapify(a,i,n);
	for (int i=n-1;i>0;i--) {
		swap(a[0],a[i]);
		heapify(a,0,i);
	}
}
int main() {
	int n;
	// int x;
	cout<<"Enter size of tree"<<endl;
	cin>>n;
	int a[n];
	cout<<"Enter elements level wise"<<endl;
	for (int i=0;i<n;i++)
		cin>>a[i];
	/*
	cout<<"Enter problem element index"<<endl;
	cin>>x;
	heapify(a,x-1,n);
	//different
	for (int i=(n/2)-1;i>=0;i--)
		heapify(a,i,n);
	*/
	heapsort(a,n);
	cout<<"The sorted tree is"<<endl;
	print(a,n);
	return 0;
}
