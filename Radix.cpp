#include<iostream>
using namespace std;

void countSort(int ar[], int n, int d)
{
    int B[n];
    int i, count[10] = {0};

    for (i = 0; i < n; i++)
        count[ (ar[i]/d)%10 ]++;


    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--)
    {
        B[count[ (ar[i]/d)%10 ] - 1] = ar[i];
        count[ (ar[i]/d)%10 ]--;
    }


    for (i = 0; i < n; i++)
        ar[i] = B[i];
}

void radixsort(int ar[], int n)
{

    int max = ar[0];
    for (int i = 1; i < n; i++)
        if (ar[i] > max)
            max = ar[i];

    for (int d = 1; max/d > 0; d *= 10)
        countSort(ar, n, d);
}

int main()
{
    int i,n,sum;
    cout<<"\nEnter the no. of elements in the set: ";
    cin>>n;
    int ar[n];
    cout<<"\nEnter the values::\n";
    for(i=0;i<n;i++)cin>>ar[i];

    //calculating max
    int max = ar[0];
    for (i = 1; i < n; i++)
        if (ar[i] > max)
            max = ar[i];
    radixsort(ar, n);

    cout<<"\nSorted array: ";
    for(i=0;i<n;i++)cout<<ar[i]<<" ";
    return 0;
}
