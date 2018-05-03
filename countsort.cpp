#include<iostream>
using namespace std;

int *count_sort(int *a,int n,int k) {
    int *b = new int[n];
    int c[k+1] = {0};
    for (int i=0;i<n;i++) {
        ++c[a[i]];
    }
    for (int i=1;i<n;i++) {
        c[i] += c[i-1];
    }
    for (int i=n-1;i>=0;i--) {
        b[--c[a[i]]] = a[i];
    }
    return b;
}

int main() {
    int n,k;
    cout<<"Enter size of n and k in order"<<endl;
    cin>>n>>k;
    int a[n];
    cout<<"Enter elements to be sorted"<<endl;
    for (int i=0;i<n;i++) {
        cin>>a[i];
    }
    cout<<"The sorted array is : "<<endl;
    int *x = count_sort(a,n,k);
    for (int i=0;i<n;i++) {
        cout<<x[i]<<" ";
    }
    cout<<endl;
    return 0;
}
