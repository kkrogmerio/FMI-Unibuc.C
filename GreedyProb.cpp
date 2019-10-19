#include <iostream>
#include <queue>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
vector<pair<int,int> >v[22];
priority_queue<tuple<int,int,int> >q;
ofstream g("output.out");
int i,j;
int main()
{int n;
cin>>n;
int index=0;
for(i=0;i<n;++i)
{
    int x,y;
    cin>>x>>y;
    ++index;
    q.push(make_tuple(-y,x,index));

}
int num=0,gasit=0,nr=0;

while(q.empty()==0)
{
    int d1=-get<0>(q.top());
    int d2=get<1>(q.top());
    int dr=get<2>(q.top());
    for(i=0;i<nr;++i)
        if(d2>v[i].back().second)
        {
           //cout<<dr<<" ";
           //cout<<v[i].back().second<<" ";
            ++num;
            gasit=1;
            v[i].push_back({dr,d1});
           // cout<<v[i].back().second<<" ";
        }//cout<<d1<<" "<<d2<<endl;
        if(gasit==0)
{
        v[nr++].push_back({dr,d1});
       // cout<<endl<<dr<<" ";}

        gasit=0;
}
       // cout<<d1<<" "<<d2<<endl;
    q.pop();



}
cout<<nr<<endl;
for(i=0;i<nr;++i)
{   sort(v[i].begin(),v[i].end(),[](const pair<int,int>&a,const pair<int,int>&b){if(a.first>b.first)return true;
else
    return false;
});
    while(v[i].empty()==0)
    {
        cout<<v[i].back().first<<" ";
       // const
        v[i].pop_back();
    }
    cout<<endl;
}
    return 0;
}
