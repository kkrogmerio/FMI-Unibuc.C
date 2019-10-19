#include<bits/stdc++.h>
using namespace std;
string s;
unordered_set<string> a;
unordered_set<string>::iterator it;
vector<pair<string,int> >v;
int i,n,j;
float raza,rmax=0;
int main()
{  cin>>n;
for(i=0;i<n;++i)
{
    int L,l,h;
    cin>>L>>l>>h;
    L=min(L,l);
    raza=min(L,h);
    raza/=2;
    if(raza>rmax)
        rmax=raza;

    string cc;
    cc=to_string(L)+to_string(l);
    sort(cc.begin(),cc.end());
    v.push_back({cc,h});
    cc.clear();
    cc=to_string(L)+to_string(h);
    sort(cc.begin(),cc.end());
    v.push_back({cc,l});
    cc.clear();
    cc=to_string(h)+to_string(l);
    sort(cc.begin(),cc.end());
    v.push_back({cc,L});
    cc.clear();
}
for(i=0;i<v.size();++i)
    for(j=i+1;j<v.size();++j)
{
    if(v[i].first==v[j].first)
    {
        stringstream cit(v[i].first);
        int val;
        cit>>val;
        int num1=val%10;
        int num2=(val/10)%10;

        int sumx=v[i].second+v[j].second;
        cout<<num1<<endl<<num2<<endl<<sumx<<endl;
        num1=min(num1,num2);
        raza=min(num2,sumx);
        raza/=2;
        if(raza>rmax)
            rmax=raza;

    }
}
cout<<raza<<endl;
}
