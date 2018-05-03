#include <bits/stdc++.h>

using namespace std;
int comp=0;

int partition(int *a, int l, int h)
{
    int pivot = a[h];
    int i = (l - 1);

    for (int j = l; j <= h - 1; j++)
    {
        comp++;
        if (a[j] <= pivot)
        {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[h]);
    return (i + 1);
}
int partition_r(int *a, int l, int h)
{
    srand(time(NULL));
    int random = l + rand() % (h - l);
    swap(a[random], a[h]);
    return partition(a, l, h);
}
void quickSort(int *a, int l, int h)
{
    if (l < h) {
        int pi = partition_r(a, l, h);
        quickSort(a, l, pi - 1);
        quickSort(a, pi + 1, h);
    }
}
void printArray(int *a, int n)
{
    int i;
    for (i = 0; i < n; i++)
        cout<<a[i]<<" ";
    cout<<endl;
}
int main()
{
    int a[] = { 10, 7, 8, 9, 1, 5 };
    int n = sizeof(a) / sizeof(a[0]);
    quickSort(a, 0, n - 1);
    cout<<"Sorted array:"<<endl;
    printArray(a, n);
    cout<<"Number of comparisons :\t"<<comp<<endl;
    return 0;
}
