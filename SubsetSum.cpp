#include <iostream>
using namespace std;

bool isSubsetSum(int A[], int n, int sum)
{
    bool subset[n+1][sum+1];

    for (int i = 0; i <= n; i++)
      subset[i][0] = true;

    for (int i = 1; i <= sum; i++)
      subset[0][i] = false;

     for (int i = 1; i <= n; i++)
     {
       for (int j = 1; j <= sum; j++)
       {
         if(j<A[i-1])
         subset[i][j] = subset[i-1][j];
         if (j >= A[i-1])
           subset[i][j] = subset[i-1][j] ||
                                 subset[i - 1][j-A[i-1]];
       }
     }

     return subset[n][sum];
}
int main(){

int n,sum;
cout<<"\nEnter the no. of elements in the set: ";
cin>>n;
int ar[n];
cout<<"\nEnter the values::\n";
for(int i=0;i<n;i++)cin>>ar[i];

cout<<"\nEnter the value of sum: ";
cin>>sum;

bool check=isSubsetSum(ar,n,sum);

if(check)
    cout<<"\nThere is a subset with sum equal to "<<sum<<endl;
else
    cout<<"\nNo subset with sum equal to "<<sum<<endl;

return 0;

}
