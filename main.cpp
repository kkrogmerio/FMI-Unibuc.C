#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_set>
using namespace std;
unordered_set<string>chei;
vector<int> v;
int val=0,i,x;
int main()
{
    int n;
    cin>>n;
    for(i=0;i<n;++i)
    {
        cin>>x;
        v.push_back(x);
    }
    string s;
    sort(v.begin(),v.end());
    for(i=0;i<n-2&&v[i]<0;++i)
    {
        int st=i+1;
        int dr=n-1;
        while(st<dr)
        {
            if(v[i]+v[st]+v[dr]>0)
                dr--;
            else
                if(v[i]+v[st]+v[dr]<0)
                st++;
            else
            {

                s=s+to_string(v[i])+" "+to_string(v[st])+" "+to_string(v[dr]);
                if(chei.find(s) == chei.end()) {
                    cout << s << endl;
                    chei.insert(s);
                }
                s.clear();
                dr--;
                st++;
            }

        }
    }
}
