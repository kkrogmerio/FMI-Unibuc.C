#include <iostream>

using namespace std;
int lin=1,col=1,ok=1,a[100][199],m,n,i,j;
struct nod1
{
    int col;
    int val;
    nod1* next;
}*p;
void push(int x)
{
    nod1 *p=new nod1;
}
void matrice(int i,int j,int ok,int numerotare)
{   numerotare=2;
    if(a[i][j]==1&&a[i+1][j]==1)
    {
        a[i][j]=numerotare;
        matrice(i+1,j,0,numerotare);
    }
    else
        if(a[i][j]==1&&a[i][j+1]==1)
    {
        a[i][j]=numerotare;
        matrice(i,j+1,0,numerotare);
    }
    if(a[i][j]==1&&a[i-1][j]==1)
    {
        a[i-1][j]=numerotare;
        matrice(i-1,j,0,numerotare);
    }
    if(a[i][j]==1&&a[i-1][j-1]==1)
    {
        a[i-1][j]=numerotare;
        matrice(i-1,j-1,0,numerotare);
    }
    if(ok==1)
    {
    col++;
    if(col>m)
    {
        lin++;
        col=1;
    }
    numerotare++;
    matrice(lin,col,1,numerotare);
    }

}
int main()
{
    cin>>m>>n;
    for(i=1;i<=m;++i)
        for(j=1;j<=n;++j)
        cin>>a[i][j];
    matrice(1,1,1,1);
     for(i=1;i<=m;++i)
        for(j=1;j<=n;++j)
        {
            cout<<a[i][j]<<" ";
            cout<<
            '/n';
        }

    return 0;
}
